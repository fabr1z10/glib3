import vars
import entity
import components as comp
import shapes as sh
import states
import func
import platformer.states


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