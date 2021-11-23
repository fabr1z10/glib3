from mopy.entity import Entity
import mopy.monkey as monkey
import data
import mopy.util as utils
import mopy.factories.items as items

def mario(args):
    p = items.player2D(args)
    return p


def goomba(args):
    e = Entity()
    e.model = args.get('model')
    size = args.get('size')
    max_speed = args.get('max_speed')
    time_acc = args.get('time_acc')
    gravity, jump_speed = utils.compute_gravity(monkey.engine.data.globals.jump_height,
                                                monkey.engine.data.globals.time_to_jump_apex)
    flip_on_edge = args.get('flip_on_edge', False)
    e.add_component({
        'type': 'components.smart_collider',
        'tag': data.CollisionTags.goomba,
        'flag': data.CollisionFlags.foe,
        'mask': data.CollisionFlags.player,
        'debug': True
    })
    e.components.append({
        'type': 'components.controller2D',
        'size': [size[0], size[1], 0],
        'offset': [0, size[1] * 0.5, 0],
        'mask_up': 2,
        'mask_down': 2 | 32,
        'debug': True
    })
    e.components.append({'type': 'components.dynamics'})

    e.components.append({
        'type': 'components.state_machine',
        'initial_state': 'walk',
        'states': [{
            'id': 'walk',
            'type': 'state.npc_walk',
            'max_speed': max_speed,
            'jump_speed': jump_speed,
            'gravity': gravity,
            'jump_up_anim': 'walk',
            'jump_down_anim': 'walk',
            'flip_on_edge': flip_on_edge
        }, {
            'id': 'dead',
            'type': 'state.npc_walk',
            'max_speed': 0,
            'jump_speed': jump_speed,
            'gravity': gravity,
            'walk': 'dead',
            'walk_anim': 'dead',
            'jump_up_anim': 'dead',
            'jump_down_anim': 'dead'
        }]
    })
        #
        # pos = makePos2(*args)
        # foe_id = kwargs.get('id')
        # foe_info = vars.foes[foe_id]
        # model = foe_info['model']
        # p = entity.Sprite(model=model, pos=pos)
        # p.add_component(comp.SmartCollider(flag=vars.flags.foe, mask=vars.flags.player, tag=foe_info['tag']))
        # p.add_component(comp.Controller2D(mask_up=vars.flags.platform, mask_down=vars.flags.platform | vars.flags.platform_passthrough,
        #                                   max_climb_angle=80, max_descend_angle=80, size=foe_info['size'], debug=True))
        # p.add_component(comp.Dynamics2D(gravity=vars.gravity))
        # sm = comp.StateMachine(initial_state='walk')
        # sm.states.append(states.SimpleState(uid='dead', anim='dead'))
        # sm.states.append(platformer.states.FoeWalk(uid='walk', anim='walk', speed=foe_info['speed'], acceleration=0,
        #                                            flip_horizontal=foe_info['flip_h'], flip_when_platform_ends=foe_info['flip_when_platform_ends'],
        #                                            left=1))
        # p.add_component(sm)
        # return p
    return e


def brick(ciao):
    e = Entity()
    tile_size = getattr(monkey.engine.data.globals, 'tile_size', [1, 1])
    e.components.append({
        'type': 'components.collider',
        'shape': {
            'type': 'rect',
            'width': tile_size[0],
            'height': tile_size[1],
        },
        'tag': 0,
        'flag': 2,
        'mask': 0,
        'debug': True
    })
    # add brick sensor
    sensor = Entity()
    sensor.pos = [0.1 * tile_size[0], -0.1 *tile_size[1], 0]
    sensor.components.append({
        'type': 'components.collider',
        'shape': {
            'type': 'shape3d.aabb',
            'size': [0.8 * tile_size[0], 0.2*tile_size[1], 0]
        },
        'tag': data.CollisionTags.brick_sensor,
        'mask': data.CollisionFlags.player,
        'flag': data.CollisionFlags.foe,
        'debug': True
    })
    e.add(sensor)
    return e