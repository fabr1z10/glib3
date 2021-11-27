from mopy.entity import Entity
import mopy.monkey as monkey
import data
import mopy.util as utils
import mopy.factories.items as items
import copy

def mario(args):
    mode = data.globals.player_modes[data.globals.player_mode]
    nargs = {
        'tag': 'player',
        'size': mode['size'],
        'model': mode['model'],
        'max_speed': 100,
        'time_acc': 0.1,
        'jump_height': data.globals.jump_height,
        'time_to_jump_apex': data.globals.time_to_jump_apex
    }
    p = items.player2D(nargs)
    return p


def bg(args):
    e = Entity()
    asset = copy.deepcopy(monkey.engine.get_asset(args.get('model', None)))
    asset['tile_size'] = [16, 16]
    e.model = asset
    return e

def rect(args):
    p = items.rect_platform(args)
    tile_size = getattr(monkey.engine.data.globals, 'tile_size', [1, 1])
    img = args.get('img', None)
    if img:
        size = args.get('size')
        sz = [size[0] * tile_size[0], size[1]* tile_size[1]]
        if img:
            p.model = {
                'type': 'model.rect',
                'size': sz,
                'repeat': [size[0], size[1]],
                'tex': args.get('img')
            }
    else:
        asset = copy.deepcopy(monkey.engine.get_asset(args.get('model', None)))
        asset['tile_size'] = [16,16]
        p.model = asset

    return p


def goomba(args):
    e = Entity()
    e.model = args.get('model')
    size = args.get('size')
    max_speed = args.get('max_speed')
    #time_acc = args.get('time_acc')
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
    return e


def brick(ciao):
    e = Entity()
    e.model = ciao.get('model', None)
    hits_left = ciao.get('hits_left', 1)
    bonus_item = ciao.get('item', None)
    collision_tag = data.CollisionTags.bonus_brick_sensor if bonus_item else data.CollisionTags.basic_brick_sensor
    tile_size = getattr(monkey.engine.data.globals, 'tile_size', [1, 1])
    hidden = ciao.get('hidden', False)
    if hidden:
        collision_tag = data.CollisionTags.hidden_brick_sensor
    e.components.append({
        'type': 'components.collider',
        'shape': {
            'type': 'rect',
            'width': tile_size[0],
            'height': tile_size[1],
        },
        'tag': 0,
        'flag': 0 if hidden else 2,
        'mask': 0,
        'debug': True
    })
    e.components.append({
        'type': 'components.info',
        'stuff': {
            'hits_left': hits_left,
            'item': bonus_item
        }
    })
    e.components.append({'type': 'components.dynamics'})
    e.components.append({'type': 'components.platform'})
    e.components.append({
        'type': 'components.line_dynamic_mover',
        'direction': (0, 1),
        'acceleration': (0, -data.globals.gravity),
        'min': 0
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
        'tag': collision_tag,
        'mask': data.CollisionFlags.player,
        'flag': data.CollisionFlags.foe,
        'debug': True
    })

    e.add(sensor)
    return e