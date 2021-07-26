import entity
import components as comp
import platformer.states as pstates
import vars

def character_player(**kwargs):
    def f(*args):
        pos = (args[0], args[1], 0)
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
        p.add_component(comp.Follow(relpos=(0, 5, 20)))
        return p
    return f
