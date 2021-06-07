import vars
import entity
import components as comp
import shapes as sh
import shapes3d as sh3d
import states
import func
import platformer.states
import monkey
import example
import script
import actions as act


def makePos(*args):
    return args[0] * vars.tile_size, args[1] * vars.tile_size, args[2]

def makePos2(*args):
    return args[0] * vars.tile_size, args[1] * vars.tile_size, args[2] if len(args) > 2 else 0


def wall(**kwargs):
    def f(*args):
        pos = makePos2(*args)
        a = entity.Entity(pos=pos)
        print('DDD')
        a.add_component(comp.Collider(flag=vars.flags.platform, mask=vars.flags.player, tag=1,
                                      shape=sh.Rect(width=1, height=16 * vars.tile_size)))
        print('DDE')
        return a
    return f

# creates a rectangular platform
def platform(**kwargs):
    def f(*args):
        pos = makePos(*args)
        w = args[3]
        h = args[4]
        a = entity.Entity(pos=pos)
        img = kwargs.get('image', None)
        if img:
            a.add_component(comp.Gfx(image=img, repeat=[w, h]))
        a.add_component(comp.Info(bounds=[0, 0, w * vars.tile_size, h * vars.tile_size]))
        a.add_component(comp.Collider(flag=vars.flags.platform, mask=vars.flags.player, tag=1,
                                      shape=sh.Rect(width=w * vars.tile_size, height=h * vars.tile_size)))
        return a
    return f


def plant(**kwargs):
    def f(*args):
        pos = makePos2(*args)
        model = kwargs.get('model')
        pct = kwargs.get('pct', 0)
        s = entity.Sprite(model=model, pos=pos)
        s.add_component(comp.SmartCollider(flag=vars.flags.foe, mask=vars.flags.player, tag=vars.tags.plant, debug=True))
        s.add_component(comp.PolygonalMover(origin=pos, pct=pct, loop=True, moves=[ {'delta': (0,-64), 'speed': 100, 'hold': 1},
                                                    {'delta': (0, 64), 'speed': 100, 'hold': 1}]))
        return s
    return f



def foe(**kwargs):
    def f(*args):
        pos = makePos2(*args)
        foe_id = kwargs.get('id')
        foe_info = vars.foes[foe_id]
        model = foe_info['model']
        p = entity.Sprite(model=model, pos=pos)
        p.add_component(comp.SmartCollider(flag=vars.flags.foe, mask=vars.flags.player, tag=foe_info['tag']))
        p.add_component(comp.Controller2D(mask_up=vars.flags.platform, mask_down=vars.flags.platform | vars.flags.platform_passthrough,
                                          max_climb_angle=80, max_descend_angle=80, size=foe_info['size'], debug=True))
        p.add_component(comp.Dynamics2D(gravity=vars.gravity))
        sm = comp.StateMachine(initial_state='walk')
        sm.states.append(states.SimpleState(uid='dead', anim='dead'))
        sm.states.append(platformer.states.FoeWalk(uid='walk', anim='walk', speed=foe_info['speed'], acceleration=0,
                                                   flip_horizontal=foe_info['flip_h'], flip_when_platform_ends=foe_info['flip_when_platform_ends'],
                                                   left=1))
        p.add_component(sm)
        return p
    return f


def koopa(**kwargs):
    def f(*args):
        pos = makePos2(*args)
        foe_id = kwargs.get('id')
        foe_info = vars.foes[foe_id]
        model = foe_info['model']
        p = entity.Sprite(model=model, pos=pos)
        p.add_component(comp.SmartCollider(flag=vars.flags.foe, mask=vars.flags.player, tag=foe_info['tag']))
        p.add_component(comp.Controller2D(mask_up=vars.flags.platform, mask_down=vars.flags.platform | vars.flags.platform_passthrough,
                                          max_climb_angle=80, max_descend_angle=80, size=foe_info['size'], debug=True))
        p.add_component(comp.Dynamics2D(gravity=vars.gravity))
        sm = comp.StateMachine(initial_state='walk')
        sm.states.append(states.SimpleState(uid='hide', anim='hide'))
        sm.states.append(platformer.states.FoeWalk(uid='walk', anim='walk', speed=foe_info['speed'], acceleration=0,
                                                   flip_horizontal=foe_info['flip_h'], flip_when_platform_ends=foe_info['flip_when_platform_ends'],
                                                   left=1))
        sm.states.append(platformer.states.FoeWalk(uid='walk2', anim='hide', speed=foe_info['fast_speed'], acceleration=0,
                                                   flip_horizontal=foe_info['flip_h'], flip_when_platform_ends=foe_info['flip_when_platform_ends'],
                                                   left=1))
        p.add_component(sm)
        p.add_component(comp.ScriptPlayer())
        return p
    return f

# #def player(model: str, x: float, y: float):
def player(**kwargs):
    def f(*args):
        pos = makePos(*args)
        current_state = vars.states[vars.state]
        model = current_state['model']
        speed = current_state['speed']
        p = entity.Sprite(model=model, pos=pos, tag='player')
        p.add_component(comp.SmartCollider(flag=vars.flags.player, mask=vars.flags.foe | vars.flags.foe_attack, tag=vars.tags.player))
        p.add_component(comp.Controller2D(mask_up=vars.flags.platform, mask_down=vars.flags.platform | vars.flags.platform_passthrough,
                                          max_climb_angle=80, max_descend_angle=80, size=current_state['size'], debug=True))
        p.add_component(comp.Dynamics2D(gravity=vars.gravity))
        sm = comp.StateMachine(initial_state='walk')
        sm.states.append(states.SimpleState(uid='dead', anim='dead'))
        sm.states.append(platformer.states.WalkSide(uid='walk', speed=speed, acceleration=0.05, jump_speed=vars.jump_velocity, flip_horizontal=True,
                                                    keys=[
                                                        [90,  states.StateCallback(func.fire)],
                                                        [264, states.StateCallback(func.enter_pipe)],
                                                    ]))
        sm.states.append(platformer.states.Jump(uid='jump', speed=speed, acceleration=0.10, flip_horizontal=True, anim_up='jump', anim_down='jump',
                                                keys=[
                                                    [90, states.StateCallback(func.firej)],
                                                ]))
        sm.states.append(states.Attack(uid='attack1', anim='fire'))
        sm.states.append(states.JumpAttack(uid='attack2', anim='fire', speed=200, acceleration=0.10, flip_horizontal=True))
        sm.states.append(platformer.states.FoeWalk(uid='demo', anim='walk', speed=speed, acceleration=0.05,
                                                   flip_horizontal=True, flip_when_platform_ends=False, left=1,
                                                   flip_on_wall=False))
        sm.states.append(states.SimpleState(uid='pipe', anim='pipe'))
        sm.states.append(states.SimpleState(uid='slide', anim='slide'))

        p.add_component(sm)
        p.add_component(comp.KeyInput())
        p.add_component(comp.Follow())
        return p
    return f


def brick(**kwargs):
    def f(*args):
        model = kwargs.get('model')
        piece = kwargs.get('piece')
        pos = makePos2(*args)
        a = entity.Sprite(model=model, pos=pos)
        a.add_component(comp.Collider(flag=vars.flags.platform, mask=0, tag=0, shape=sh.Rect(width=vars.tile_size, height=vars.tile_size)))
        a.add_component(comp.Info(piece=piece))
        b = entity.Entity()
        b.pos = (2, -0.5, 0)
        b.add_component(comp.Collider(
            flag=vars.flags.foe,
            mask=vars.flags.player,
            tag=vars.tags.brick_sensor,
            shape=sh3d.AABB(size=(vars.tile_size-4, 1, 1))
            #shape=sh.Rect(width=vars.tile_size-4, height=1.0)
        ))
        a.add(b)
        return a
    return f


def _brick(x, y, model, hits, callback):
    pos = makePos2(x, y)
    a = entity.Sprite(model=model, pos=pos)
    a.add_component(comp.Collider(flag=vars.flags.platform, mask=0, tag=0, shape=sh.Rect(width=vars.tile_size, height=vars.tile_size)))
    a.add_component(comp.Info(hitsLeft=hits, callback=callback))
    b = entity.Entity()
    b.pos = (2, -0.5, 0)
    b.add_component(comp.Collider(
        flag=vars.flags.foe,
        mask=vars.flags.player,
        tag=vars.tags.bonus_brick_sensor,
        debug=True,
        shape=sh3d.AABB(size=(vars.tile_size-4, 1, 0))
        #shape=sh.Rect(width=vars.tile_size - 4, height=1.0)
    ))
    a.add(b)
    return a


def mushroom_brick(**kwargs):
    def f(*args):
        return _brick(args[0], args[1], 'sprites/01/bonusbrick', 1, m1)
    return f


def coin_brick(**kwargs):
    def f(*args):
        return _brick(args[0], args[1], 'sprites/01/bonusbrick', 1, m2)
    return f


def multi_coinbrick(**kwargs):
    def f(*args):
        model = kwargs.get('model')
        return _brick(args[0], args[1], model, args[2], m2)
    return f


# release bonus
def m1(x: float, y: float):
    a = None
    if vars.state == 0:
        a = monkey.engine.get_item_factory('moving_bonus')(model='sprites/01/mushroom', tag=vars.tags.mushroom, speed=30)(x, y, -1)
    else:
        a = monkey.engine.get_item_factory('moving_bonus')(model='sprites/01/flower', tag=vars.tags.mushroom, speed=0)(x, y, -1)
    main = example.get('main')
    id = main.add(a)
    s = script.Script()
    s.add_action(act.Move(entity_id=id, speed=10, by=[0, 16]))
    s.add_action(act.SetState(entity_id=id, state='walk'))
    example.play(s)


def m2(x: float, y: float):
    def score():
        m3(x, y+1)
    a = entity.Sprite(model='sprites/01/flyingcoin', pos=(x * vars.tile_size, (y+1)*vars.tile_size, 0))
    main = example.get('main')
    id = main.add(a)
    s = script.Script()
    s.add_action(act.MoveAccelerated(v0=[0, 100], a=[0, -100], yStop=(y*vars.tile_size) + 16, entity_id=id))
    s.add_action(act.RemoveEntity(id))
    s.add_action(act.CallFunc(score))
    example.play(s)


def m3(x: float, y: float):
    a = entity.Sprite(model='sprites/01/score100', pos=(x * vars.tile_size, (y+1)*vars.tile_size, 0))
    main = example.get('main')
    id = main.add(a)
    s = script.Script()
    s.add_action(act.Move(speed=100, by=[0, 64], entity_id=id))
    s.add_action(act.RemoveEntity(id))
    example.play(s)


def tile_map(**kwargs):
    def f(*args):
        shape = None
        tile_set_id = kwargs['id']
        tile_set = vars.tile_data['tile_sets'][tile_set_id]
        pos = makePos2(*args)
        sheet_id = tile_set['sheet']
        sheet = vars.tile_data['tile_sheets'][sheet_id]
        width = tile_set['size'][0]
        height = tile_set['size'][1]
        solid = tile_set['solid']
        data = tile_set['data']
        e = entity.Entity(pos=pos)
        e.add_component(comp.TiledGfx(
            tile_sheet=sheet['file'],
            sheet_size=sheet['sheet_size'],
            tile_data=data,
            width=width,
            height=height,
            size=vars.tile_size))
        if solid:
            shape = sh.Rect(width=width * vars.tile_size, height=height * vars.tile_size)
            e.add_component(comp.Collider(
                flag=vars.flags.platform,
                mask=1,
                tag=1,
                shape=shape
            ))
        return e
    return f


# a bonus that behave like mushroom: just walk
def moving_bonus(**kwargs):
    def f(*args):
        model = kwargs.get('model')
        collision_tag = kwargs.get('tag')
        speed = kwargs.get('speed')
        pos = makePos(*args)
        a = entity.Sprite(model=model, pos=pos)
        a.add_component(comp.SmartCollider(
            flag=vars.flags.foe,
            mask=vars.flags.player,
            tag=collision_tag))
        a.add_component(comp.Controller2D(
            mask_up=vars.flags.platform,
            mask_down=vars.flags.platform | vars.flags.platform_passthrough,
            size=(14, 16),
            shift=(0, 8),
            max_climb_angle=80,
            max_descend_angle=80,
            debug=True))
        a.add_component(comp.Dynamics2D(gravity=vars.gravity))
        sm = comp.StateMachine(initial_state='idle')
        sm.states.append(states.SimpleState(uid='idle', anim='walk'))
        sm.states.append(platformer.states.FoeWalk(uid='walk', anim='walk', speed=speed, acceleration=0, flip_horizontal=False,
                                                   flip_when_platform_ends=False, left=1))
        a.add_component(sm)
        return a
    return f


def hotspot(**kwargs):
    def f(*args):
        # the first argument is the callback function
        # the second, if present, is the model
        model = kwargs.get('model', None)
        callback = kwargs.get('func')
        info = kwargs.get('info', None)
        pos = makePos2(*args)
        if model is None:
            a = entity.Entity(pos=pos)
            size = [args[2] * vars.tile_size, args[3] * vars.tile_size, 0]
            a.add_component(comp.Collider(debug=True, flag=vars.flags.foe, mask=vars.flags.player, tag=vars.tags.key,
                                          shape=sh3d.AABB(size=size)))
            a.add_component(comp.Info(func=callback, info=info, args=args, bounds=[0, 0, size[0], size[1]]))
        else:
            a = entity.Sprite(model=model, pos=pos)
            a.add_component(comp.SmartCollider(debug=True, flag=vars.flags.foe, mask=vars.flags.player, tag=vars.tags.key))
            a.add_component(comp.Info(func=callback, info=info, args=args))
        return a
    return f


def bg(**kwargs):
    def f(*args):
        color = kwargs.get('color')
        a = entity.Entity(pos=(args[0], args[1], args[2]))
        a.add_component(comp.ShapeGfxColor(shape=sh.Rect(256, 256), color=color)) #fill=sh.SolidFill(r=color[0], g=color[1], b=color[2])))
        a.add_component(comp.Parallax(cam='maincam', factor=[1, 1], campos0=[128, 128], pos0=[0, 0]))
        return a
    return f


def walkarea(**kwargs):
    def f(*args):
        a = entity.Entity(pos=(args[0], args[1], args[2]))
        a.add_component()
        a.add_component(comp.ShapeGfxColor(shape=sh.Rect(256, 256), fill=sh.SolidFill(r=color[0], g=color[1], b=color[2])))
        a.add_component(comp.Parallax(cam='maincam', factor=[1, 1], campos0=[128, 128], pos0=[0, 0]))
        return a
    return f




def warp(**kwargs):
    def f(*args):
        pos = makePos(*args)
        pin = entity.Entity(pos=pos, tag=kwargs.get('tag', None))
        pin.add_component(
            comp.Collider(debug=True, flag=vars.flags.foe, mask=vars.flags.player, tag=vars.tags.warp,
                          shape=sh3d.AABB(size=(4,2,0), offset=(-2,0,0))))
        pin.add_component(comp.Info(world=args[3], start=args[4], bounds=[0, 0, 4, 2]))
        return pin
    return f


def freeze_plant(plant_id, value):
    def f(p, s):
        example.get(plant_id).enableUpdate(value)
    return f


def plat1(**kwargs):
    def f(*args):
        pos = makePos(*args)
        # coords of the top left tile. if (x, y) is the top left
        # then (x+1, y) is the top right, and (x, y+1) and (x+1, y+1)
        # the left and right walls of the pipe.
        sheet = vars.tile_data['tile_sheets']['main']
        tl = kwargs.get('top_left')
        width = args[3]
        height = args[4]
        data = [tl[0], tl[1]]
        data.extend([tl[0] + 1, tl[1]] * (width - 2))
        data.extend([tl[0] + 2, tl[1]])
        e = entity.Entity(pos=pos)
        e.add_component(comp.TiledGfx(
            tile_sheet=sheet['file'],
            sheet_size=sheet['sheet_size'],
            tile_data=data,
            width=width,
            height=1,
            size=vars.tile_size))
        shape = sh.Line(a=(0, vars.tile_size), b = (width*vars.tile_size, vars.tile_size))
        e.add_component(comp.Collider(
            flag=vars.flags.platform,
            mask=1,
            tag=1,
            shape=shape,
            debug=True
        ))
        return e

    return f




def pipe(**kwargs):
    def f(*args):
        pos = makePos(*args)
        # coords of the top left tile. if (x, y) is the top left
        # then (x+1, y) is the top right, and (x, y+1) and (x+1, y+1)
        # the left and right walls of the pipe.
        sheet = vars.tile_data['tile_sheets']['main']
        tl = kwargs.get('top_left')
        height = args[3]
        data = [tl[0], tl[1] + 1, tl[0] + 1, tl[1] + 1] * (height - 1)
        data.extend([tl[0], tl[1], tl[0]+1, tl[1]])
        e = entity.Entity(pos=pos)
        e.add_component(comp.TiledGfx(
            tile_sheet=sheet['file'],
            sheet_size=sheet['sheet_size'],
            tile_data=data,
            width=2,
            height=height,
            size=vars.tile_size))
        shape = sh.Rect(width=2 * vars.tile_size, height=height * vars.tile_size)
        e.add_component(comp.Collider(
            flag=vars.flags.platform,
            mask=1,
            tag=1,
            shape=shape
        ))
        foe = kwargs.get('foe', None)
        exit = kwargs.get('exit', None)
        if foe:
            foe_tag = monkey.engine.get_next_tag()
            pct = 1
            if exit:
                if exit not in vars.disable_update_on_start:
                    vars.disable_update_on_start[exit] = []
                vars.disable_update_on_start[exit].append(foe_tag)
                pct=0.5
            p = plant(model=foe,pct=pct)(1, height, -0.1)
            p.tag = foe_tag
            plant_id = e.add(p)
            sensor = entity.Entity(pos=(vars.tile_size, height * vars.tile_size))
            size = (8.0, 0.4, 0.0)
            sensor.add_component(comp.Collider(debug=True, flag=vars.flags.foe, mask=vars.flags.player, tag=vars.tags.generic_hotspot,
                                               shape=sh3d.AABB(size=size, offset=(-size[0]*0.5, 0.0, 0.0))))
            sensor.add_component(comp.Info(on_enter=freeze_plant(p.tag, False), on_leave=freeze_plant(p.tag, True)))
            e.add(sensor)
        warp_info = kwargs.get('warp', None)
        if warp_info:
            w = warp()(1, height, 0, warp_info[0], warp_info[1])
            e.add(w)

        return e
    return f

def line(**kwargs):
    def f(*args):
        x = args[0] * vars.tile_size
        y = args[1] * vars.tile_size
        ax = args[2] * vars.tile_size
        ay = args[3] * vars.tile_size
        bx = args[4] * vars.tile_size
        by = args[5] * vars.tile_size
        minx = min(ax, bx)
        maxx = max(ax, bx)
        miny = min(ay, by)
        maxy = max(ay, by)
        a = entity.Entity()
        a.add_component(comp.Collider(flag=vars.flags.platform, mask=vars.flags.player, tag=1, shape=sh.Line(a=[ax, ay, 0], b=[bx, by, 0])))
        a.add_component(comp.Info(bounds=[minx, miny, maxx, maxy]))
        a.pos = (x, y, 0)
        return a
    return f


def moving_platform(**kwargs):
    def f(*args):
        pos = makePos(*args)
        e = entity.Entity(pos=pos)
        e.add_component(comp.TiledGfx(tile_sheet='gfx/smb1.png', sheet_size=[16, 16], tile_data=[15, 5], width=1, height=1,
                                      size=vars.tile_size, repx=args[3], repy=1))
        e.add_component(comp.Collider(flag=vars.flags.platform_passthrough, mask=vars.flags.player, tag=0,
                                      shape=sh.Line(a=[0, vars.tile_size, 0], b=[args[3]*vars.tile_size, vars.tile_size, 0])))
        e.add_component(comp.PolygonalMover(origin=(pos[0],pos[1]), loop=args[6], pct=args[4], moves=[
            {'delta': [0, args[5]*vars.tile_size], 'speed': args[7], 'hold': 0}]))
        e.add_component(comp.Platform())
        return e
    return f


#
#     player = Sprite(model = model, pos = [x * vars.tileSize, y*vars.tileSize], tag='player')
#     player.addComponent (SmartCollider(
#         flag = vars.flags.player,
#         mask = vars.flags.foe | vars.flags.foe_attack,
#         tag = vars.tags.player))
#     player.addComponent (Controller2D(
#         maskUp = vars.flags.platform,
#         maskDown = vars.flags.platform | vars.flags.platform_passthrough,
#         maxClimbAngle = 80,
#         maxDescendAngle = 80))
#     speed = 75
#     player.addComponent (Dynamics2D(gravity= vars.gravity))
#     stateMachine = StateMachine(initialState='walk')
#     stateMachine.states.append (SimpleState (id='dead', anim='dead'))
#     stateMachine.states.append (WalkSide(
#         id = 'walk',
#         speed = 200,
#         acceleration = 0.05,
#         jumpSpeed = vars.jump_velocity,
#         keys = [
#             [90, StateCallback(f=scripts.fire)],
#             [264, StateCallback(f=scripts.enterPipe)],
#         ],
#         flipHorizontal=True))
#     stateMachine.states.append (Jump(id='jump', speed=200, acceleration=0.10,
#         keys = [
#             [90, StateCallback(f=scripts.firej)],
#         ],
#         flipHorizontal=True, animUp='jump', animDown='jump'))
#     stateMachine.states.append (Attack(id='attack1', anim= 'fire'))
#     stateMachine.states.append (JumpAttack(id='attack2', anim= 'fire', speed = 200, acceleration = 0.10, flipHorizontal = True))
#     stateMachine.states.append (FoeWalk(id='demo', anim='walk', speed = 75,
#         acceleration=0.05, flipHorizontal=True, flipWhenPlatformEnds = False, left=1))
#     stateMachine.states.append (SimpleState (id='pipe', anim='idle'))
#     stateMachine.states.append (SimpleState (id='slide', anim='slide'))
#     player.addComponent (stateMachine)
#     player.addComponent (KeyInput())
#     player.addComponent (Follow())
#     return player