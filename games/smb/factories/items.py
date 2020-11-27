import vars
import entity
import components as comp
import shapes as sh
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


# #def player(model: str, x: float, y: float):
def player(**kwargs):
    def f(*args):
        pos = makePos(*args)
        model = kwargs.get('model')
        speed = kwargs.get('speed')
        p = entity.Sprite(model=model, pos=pos, tag='player')
        p.add_component(comp.SmartCollider(flag=vars.flags.player, mask=vars.flags.foe | vars.flags.foe_attack, tag=vars.tags.player))
        p.add_component(comp.Controller2D(mask_up=vars.flags.platform, mask_down=vars.flags.platform | vars.flags.platform_passthrough,
                                          max_climb_angle=80, max_descend_angle=80))
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
            shape=sh.Rect(width=vars.tile_size-4, height=1.0)
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
        shape=sh.Rect(width=vars.tile_size - 4, height=1.0)
    ))
    a.add(b)
    return a


def mushroom_brick(**kwargs):
    def f(*args):
        return _brick(args[0], args[1], 'bonusbrick', 1, m1)
    return f


def coin_brick(**kwargs):
    def f(*args):
        return _brick(args[0], args[1], 'bonusbrick', 1, m2)
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
        a = monkey.engine.get_item_factory('moving_bonus')(model='mushroom', tag=vars.tags.mushroom, speed=30)(x, y, -1)
    else:
        a = monkey.engine.get_item_factory('moving_bonus')(model='flower', tag=vars.tags.mushroom, speed=0)(x, y, -1)
    main = example.get('main')
    id = main.add(a)
    s = script.Script()
    s.add_action(act.Move(entity_id=id, speed=10, by=[0, 16]))
    s.add_action(act.SetState(entity_id=id, state='walk'))
    example.play(s)


def m2(x: float, y: float):
    def score():
        m3(x, y+1)
    a = entity.Sprite(model='flyingcoin', pos=(x * vars.tile_size, (y+1)*vars.tile_size, 0))
    main = example.get('main')
    id = main.add(a)
    s = script.Script()
    s.add_action(act.MoveAccelerated(v0=[0, 100], a=[0, -100], yStop=(y*vars.tile_size) + 16, entity_id=id))
    s.add_action(act.RemoveEntity(id))
    s.add_action(act.CallFunc(score))
    example.play(s)


def m3(x: float, y: float):
    a = entity.Sprite(model='score100', pos=(x * vars.tile_size, (y+1)*vars.tile_size, 0))
    main = example.get('main')
    id = main.add(a)
    s = script.Script()
    s.add_action(act.Move(speed=100, by=[0, 64], entity_id=id))
    s.add_action(act.RemoveEntity(id))
    example.play(s)


# a bonus that behave like mushroom: just walk
def moving_bonus(**kwargs):
    def f(*args):
        model = kwargs.get('model')
        collision_tag = kwargs.get('tag')
        speed = kwargs.get('speed')
        print (args)
        pos = makePos(args)
        a = entity.Sprite(model=model, pos=pos)
        a.add_component(comp.SmartCollider(
            flag=vars.flags.foe,
            mask=vars.flags.player,
            tag=collision_tag))
        a.add_component(comp.Controller2D(
            mask_up=vars.flags.platform,
            mask_down=vars.flags.platform | vars.flags.platform_passthrough,
            max_climb_angle=80,
            max_descend_angle=80))
        a.add_component(comp.Dynamics2D(gravity=vars.gravity))
        sm = comp.StateMachine(initial_state='idle')
        sm.states.append(states.SimpleState(uid='idle', anim='walk'))
        sm.states.append(platformer.states.FoeWalk(uid='walk', anim='walk', speed=speed, acceleration=0, flip_horizontal=False,
                                                   flip_when_platform_ends=False, left=1))
        a.add_component(sm)
        return a
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