import entity
import components as comp
import platformer.states as pstates
import shapes3d as sh3d
import shapes as sh
import vars
import math

def static_bg(**kwargs):
    def f(*args):
        pos = (args[0], args[2]/math.sqrt(2), args[2])
        e = entity.Entity(pos=pos)
        e.add_component(comp.Gfx(image=args[3]))
        return e
    return f

def character_player(**kwargs):
    def f(*args):
        pos = (args[0], args[1], args[2])
        scale = kwargs.get('scale', vars.player_scale)
        #char_info = vars.characters[vars.player]
        speed = vars.player_speed
        model = vars.player_model
        width = 10
        p = entity.Sprite(model=model, pos=pos, tag='player')
        # TODO shadow
        #shadow = entity.Entity()
        #shadow.add_component(comp.ShadowRenderer(angle=20.0))
        #p.add(shadow)
        #p.layer = 2
        #p.depth = 0x0207
        #p.scale = scale * vars.scale
        p.scale = scale
        p.add_component(comp.Controller3D(
             size = [1, 1, 1],
             shift = [0, 2],
             debug = True,
             mask_up=vars.flags.platform,
             mask_down=vars.flags.platform | vars.flags.platform_passthrough,
             max_climb_angle=80,
             max_descend_angle=80))
        p.add_component(comp.Dynamics2D(gravity=vars.gravity))
        p.add_component(comp.SmartCollider(flag=vars.flags.player, mask=vars.flags.foe_attack,
            tag=vars.tags.player, cast_tag=vars.tags.player_attack, cast_mask=vars.flags.foe, debug=True))
        sm = comp.StateMachine(initial_state='walk')
        sm.states.append(pstates.WalkSide3D(
            uid='walk',
            speed=speed,
            acceleration=0.05,
            jump_speed=vars.jump_velocity,
            keys=[],
            flip_horizontal=True))
        sm.states.append(pstates.Jump3D(
            uid='jump',
            speed=speed,
            acceleration=0.10,
            flip_horizontal=True,
            keys=[],
            anim_up='jump',
            anim_down='jump'))
        p.add_component(sm)
        p.add_component(comp.KeyInput())
        p.add_component(comp.DynamicFollow(world_width=5216, cam_width=384, cam_height=224, bounds=[0, 256, 512, 256, 256, 528]))
        #p.add_component(comp.Follow(relpos=(0, 0, 5), z=1))
        return p
    return f


def prism3d(**kwargs):
    def f(*args):
        pos = (args[0], args[1], args[2])
        color = kwargs.get('color', [1, 1, 1, 1])
        e = entity.Entity(pos=pos)
        shape = sh3d.Prism(shape=sh.Poly(outline=kwargs.get('poly')), height=kwargs.get('height'))
        print(shape)
        e.add_component(comp.ShapeGfxColor(shape=shape, color=color))
        e.add_component(comp.Collider(shape=shape, flag=vars.flags.platform, mask=0, tag=vars.tags.platform))
        return e
    return f

def aabb3d(**kwargs):
    def f(*args):
        pos = (args[0], args[1], args[2])
        width = args[3]
        height = args[4]
        depth = args[5]
        offset = (0, 0, 0)
        if len(args) > 6:
            offset = (args[6], args[7], args[8])
        color = kwargs.get('color', [1, 1, 1, 1])
        e = entity.Entity(pos=pos)
        shape = sh3d.AABB(size=(width, height, depth), offset=offset)
        e.add_component(comp.ShapeGfxColor(shape=shape, color=color))
        e.add_component(comp.Collider(shape=shape, flag=vars.flags.platform, mask=0, tag=vars.tags.platform))

        tx_top = kwargs.get('top', None)
        tx_front = kwargs.get('front', None)
        if tx_top:
            e.add(make_plat(glm.vec3(0, height, depth) + offset, (width, depth), tx_top))
        if tx_front:
            e.add(make_wall(glm.vec3(0, 0, depth) + offset, (width, height), tx_front))
        #e.add(make_wall(offset + glm.vec3(0, 0, depth), (width, height), '2'))
        #e.add(make_wall(offset + glm.vec3(width, 0, depth), (depth, height), '2', 90))
        return e
    return f