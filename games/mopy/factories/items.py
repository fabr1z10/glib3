from mopy.entity import Entity
from mopy.components import Gfx
import mopy.monkey as monkey
from mopy.util import tiles_to_world




def model3d(**kwargs):
    def f(*args):
        e = Entity(pos=(args[0], args[1], args[2]))
        renderer = Gfx(image=kwargs.get('image'))
        renderer.cls = 5
        e.add_component(renderer)
        return e
    return f


def rect_platform(ciao):
    e = Entity()
    tile_size = monkey.engine.room_vars.get('tile_size', [1, 1])
    size = tiles_to_world(ciao.get('size'), tile_size)
    e.components.append({
        'type': 'components.collider',
        'shape': {
            'type': 'rect',
            'width': size[0],
            'height': size[1],
        },
        'tag': 0,
        'flag': 2,
        'mask': 0,
        'debug': True
    })
    return e


def poly_platform(ciao):
    e = Entity()
    tile_size = monkey.engine.room_vars.get('tile_size', [1, 1])
    px = ciao.get('points')
    points = [px[i]*tile_size[i%2] for i in range(0, len(px))]
    e.components.append({
        'type': 'components.collider',
        'shape': {
            'type': 'convex_polygon',
            'points': points,
        },
        'tag': 0,
        'flag': 2,
        'mask': 0,
        'debug': True
    })
    return e


def line_platform(ciao):
    e = Entity()
    tile_size = monkey.engine.room_vars.get('tile_size', [1, 1])
    pass_thru = ciao.get('pass_thru', False)
    moving = ciao.get('moving', False)
    pos = tiles_to_world(ciao.get('size'), tile_size)
    e.components.append({
        'type': 'components.collider',
        'shape': {
            'type': 'line',
            'A': (0, 0),
            'B': pos
        },
        'tag': 0,
        'flag': 32 if pass_thru else 2,
        'mask': 0,
        'debug': True
    })
    mp = ciao.get('move', None)
    if mp:
        e.components.append({'type': 'components.platform'})
        path = mp['path']
        e.components.append({
            'type': 'components.polymover',
            'points': [path[i]*tile_size[i%2] for i in range(0, len(path))],
            'speed': mp['speed'],
            'mode': mp['mode']
        })
    return e



def player2D(ciao):
    e = Entity()
    e.model = ciao.get('model', None)
    tile_size = monkey.engine.room_vars.get('tile_size', [1, 1])
    size = tiles_to_world(ciao.get('size'), tile_size)
    max_speed = ciao.get('max_speed')
    time_acc = ciao.get('time_acc')
    jump_height = ciao.get('jump_height')
    time_to_jump_apex = ciao.get('time_to_jump_apex')
    gravity = (2.0 * jump_height) / (time_to_jump_apex * time_to_jump_apex)
    jump_speed = abs(gravity) * time_to_jump_apex
    e.tag = ciao.get('tag', None)
    e.components.append({
        'type': 'components.controller2D',
        'size': [size[0], size[1], 0],
        'offset': [0, size[1] * 0.5, 0],
        'mask_up': 2,
        'mask_down': 2 | 32,
        'debug': True
    })
    e.components.append({'type': 'components.dynamics'})
    e.components.append({'type': 'components.keyinput'})
    e.components.append({
        'type': 'components.follow',
        'cam': 'maincam',
        'relativepos': [0, 0, 5],
        'up': [0, 1, 0]
    })
    e.components.append({
        'type': 'components.state_machine',
        'initial_state': 'jump',
        'states': [{
            'id': 'jump',
            'type': 'state.player_jump',
            'max_speed': max_speed,
            'time_acc': time_acc,
            'gravity': gravity,
            'walk_state': 'walk',
        }, {
            'id': 'walk',
            'type': 'state.player_walk',
            'max_speed': max_speed,
            'time_acc': time_acc,
            'gravity': gravity,
            'jump_state': 'jump',
            'jump_speed': jump_speed
        }]
    })
    return e


def entity(ciao):
    e = Entity()
    e.model = ciao.get('model', None)
    e.components = ciao.get('components', [])
    e.tag = ciao.get('tag', None)
    return e
