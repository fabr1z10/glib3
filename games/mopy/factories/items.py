from mopy.entity import Entity, Text, TextAlignment
from mopy.components import Gfx, Collider
import mopy.monkey as monkey
import mopy.shapes3d as sh3d
import mopy.shapes as sh
from mopy.util import tiles_to_world


def model3d(**kwargs):
    def f(*args):
        e = Entity(pos=(args[0], args[1], args[2]))
        renderer = Gfx(image=kwargs.get('image'))
        renderer.cls = 5
        e.add_component(renderer)
        return e
    return f

def text(ciao):
    font = ciao['font']
    size = ciao['size']
    text = ciao['text']
    format = ciao.get('format')
    if format:
        text = format(text)
    color = ciao.get('color', (1, 1, 1, 1))
    align = TextAlignment[ciao.get('align')]
    txt = Text(font, size, text, color, align)
    txt.tag = ciao.get('tag')
    return txt

def fps_counter(ciao):
    font = ciao['font']
    size = ciao['size']
    fps = Text(font, size, '0', (1, 1, 1, 1), TextAlignment.top_left)
    fps.add_component({'type': 'components.fpscounter'})
    return fps


def rect_platform(ciao):
    e = Entity()
    tile_size = getattr(monkey.engine.data.globals, 'tile_size', [1, 1])
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
    e.model = ciao.get('model')
    return e


def poly_platform(ciao):
    e = Entity()
    tile_size = getattr(monkey.engine.data.globals, 'tile_size', [1, 1])
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
    tile_size = getattr(monkey.engine.data.globals, 'tile_size', [1, 1])
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


def common3D(ciao):
    e = Entity()
    e.tag = ciao.get('tag', None)
    e.scale = ciao.get('scale', 1)
    e.model = ciao.get('model', None)
    size = ciao.get('size')
    show_boxes = getattr(monkey.engine.data.globals, 'show_boxes', False)

    e.components.append({
        'type': 'components.controller3D',
        'maxClimbAngle': 80,
        'maxDescendAngle': 80,
        'size': size,
        'offset': [0, size[1]*0.5, 0],
        'mask_up': 2,
        'mask_down': 2 | 32,
        'debug': show_boxes
    })
    e.add_component({'type': 'components.dynamics3D'})
    return e


def foe3D(ciao):
    e = common3D(ciao)
    max_speed = ciao.get('max_speed')
    time_acc = ciao.get('time_acc')
    jump_height = ciao.get('jump_height')
    time_to_jump_apex = ciao.get('time_to_jump_apex')
    n_attacks = ciao.get('attacks', 0)
    gravity = (2.0 * jump_height) / (time_to_jump_apex * time_to_jump_apex)
    jump_speed = abs(gravity) * time_to_jump_apex
    walk_state = {
        'id': 'walk',
        'type': 'state.foe_chase_3D',
        'max_speed': max_speed,
        'time_acc': time_acc,
        'gravity': gravity,
        'walk_state': 'walk',
        'jump_speed': jump_speed
    }
    state_machine = {
        'type': 'components.state_machine',
        'initial_state': 'walk',
        'states': [walk_state]
    }
    e.components.append(state_machine)

    return e



def player3D(ciao):
    e = common3D(ciao)
    max_speed = ciao.get('max_speed')
    time_acc = ciao.get('time_acc')
    jump_height = ciao.get('jump_height')
    time_to_jump_apex = ciao.get('time_to_jump_apex')
    n_attacks = ciao.get('attacks', 0)
    gravity = (2.0 * jump_height) / (time_to_jump_apex * time_to_jump_apex)
    jump_speed = abs(gravity) * time_to_jump_apex
    e.components.append({'type': 'components.keyinput'})
    e.components.append({
        'type': 'components.follow',
        'cam': 'maincam',
        'relativepos': [0, 5, 20],
        'up': [0, 1, 0]
    })

    walk_state = {
        'id': 'walk',
        'type': 'state.player_walk_3D',
        'max_speed': max_speed,
        'time_acc': time_acc,
        'gravity': gravity,
        'walk_state': 'walk',
        'jump_speed': jump_speed
    }
    state_machine = {
        'type': 'components.state_machine',
        'initial_state': 'walk',
        'states': [walk_state, {
            'id': 'jump',
            'type': 'state.player_jump_3D',
            'max_speed': max_speed,
            'time_acc': time_acc,
            'gravity': gravity,
        }]
    }

    if n_attacks > 0:
        walk_state['keys'] = []
        for i in range(0, n_attacks):
            a_id = 'attack_' + str(i)
            walk_state['keys'].append({'key': 81, 'action': {'type':'stateaction.statetransition', 'state': a_id}})
            state_machine['states'].append({
                'id': a_id,
                'type': 'state.anim',
                'anim': a_id,
                'next_state': 'walk'
            })

    e.components.append(state_machine)

    return e


def player2D(ciao):
    e = Entity()
    e.model = ciao.get('model', None)
    tile_size = getattr(monkey.engine.data.globals, 'tile_size', [1, 1])
    size = tiles_to_world(ciao.get('size'), tile_size)
    max_speed = ciao.get('max_speed')
    time_acc = ciao.get('time_acc')
    show_boxes = getattr(monkey.engine.data.globals, 'show_boxes', False)
    jump_height = ciao.get('jump_height')
    time_to_jump_apex = ciao.get('time_to_jump_apex')
    print('Jump height = ' + str(jump_height))
    gravity = (2.0 * jump_height) / (time_to_jump_apex * time_to_jump_apex)
    jump_speed = abs(gravity) * time_to_jump_apex
    e.tag = ciao.get('tag', None)
    e.components.append({
        'type': 'components.controller2D',
        'size': [size[0], size[1], 0],
        'offset': [0, size[1] * 0.5, 0],
        'mask_up': 2,
        'mask_down': 2 | 32,
        'debug': show_boxes
    })
    e.components.append({'type': 'components.dynamics'})
    e.components.append({'type': 'components.keyinput'})
    e.components.append({
        'type': 'components.smart_collider',
        'flag': monkey.engine.data.CollisionFlags.player,
        'mask': monkey.engine.data.CollisionFlags.foe,
        'tag': monkey.engine.data.CollisionTags.player,
        'debug': True
    })
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


def box_platform_3d(ciao):
    e = Entity()
    size = ciao['size']
    top_tex = ciao['top']
    side_tex = ciao['side']
    collision_tag = ciao.get('collision_tag', 0)
    shape = sh3d.AABB(size=size, offset=(0, 0, -size[2]))
    e.model = {
        'type': 'model.prism',
        'repeat': ciao['repeat'],
        'poly': [0, 0, size[0], 0, size[0], size[2], 0, size[2]],
        'top': top_tex,
        'side': side_tex,
        'height': size[1],
        'offset': [0, size[1], 0]
    }
    e.add_component(Collider(shape=shape, flag=2, mask=0, tag=collision_tag, debug=True))
    return e


def rect_platform_3d(ciao):
    e = Entity()
    outline = ciao['poly']
    height = ciao.get('height', 1.0)

    y = ciao.get('y', 0.0)
    top_tex = ciao['top']
    side_tex = ciao['side']
    collision_tag = ciao.get('collision_tag', 0)
    shape = sh3d.Prism(shape=sh.Poly(outline=outline), height=height, walls=ciao.get('walls', []))
    e.model = {
        'type': 'model.prism',
        'repeat': ciao['repeat'],
        'poly': outline,
        'top': top_tex,
        'side': side_tex,
        'height': height,
        'offset': [0, height, 0]
    }
    # e.add_component(comp.ShapeGfxColor(shape=shape, color=color))
    e.add_component(Collider(shape=shape, flag=2, mask=0, tag=collision_tag, debug=True))
    return e

def dir_light(ciao):
    e = Entity()
    e.add_component({
        'type': 'light.directional',
        'ambient': ciao.get('ambient'),
        'diffuse': ciao.get('diffuse'),
        'direction': ciao.get('direction')
    })
    return e

def entity(ciao):
    e = Entity()
    e.model = ciao.get('model', None)
    e.scale = ciao.get('scale')
    e.components = ciao.get('components', [])
    e.tag = ciao.get('tag', None)
    children = ciao.get('children')
    if children:
        tile_size = getattr(monkey.engine.data.globals, 'tile_size', [1, 1])# monkey.engine.room_vars.get('tile_size', [1, 1])
        for c in children:
            entity_desc = c
            positions = c.get('pos', [0, 0, 0])
            if 'ref' in c:
                entity_desc = monkey.engine.get_asset(entity_desc, c['ref'])
            factory = monkey.engine.get_item_factory(entity_desc['type'])
            if not factory:
                print('Don''t have factory for item: ' + entity_desc['type'])
                exit(1)
            for ip in range(0, len(positions), 3):
                pos = positions[ip:ip + 3]
                child = factory(entity_desc)
                child.pos = tiles_to_world(pos, tile_size)
                e.children.append(child)

    return e
