from mopy.entity import Entity, Text, TextAlignment
from mopy.components import Gfx, Collider, SmartCollider, SkeletalCollider, ShadowRenderer, ShapeGfxColor, Info
import mopy.monkey as monkey
import mopy.shapes3d as sh3d
import mopy.shapes as sh
import mopy
from mopy.util import tiles_to_world
import copy
import math

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
    dt = monkey.engine.data.globals

    e = Entity()
    e.layer = 1
    e.tag = ciao.get('tag', None)
    scale = ciao.get('scale', 1)
    e.scale = (scale, scale, 1)
    e.model = ciao.get('model', None)
    energy = ciao.get('energy', 1)
    if isinstance(e.model, dict):
        ciao = copy.deepcopy(mopy.monkey.engine.get_asset(e.model['template']))
        f = getattr(mopy.monkey.engine.data.scripts, ciao['builder'])
        if not f:
            print ("hey I need a function: " + f + " to create the model")
        e.model = f(ciao, e.model['args'])
    size = ciao.get('size', dt.default_size)

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
    e.add_component({
        'type': 'components.info',
        'stuff': {
            'energy': energy,
            'attacks': ciao.get('attacks', None)
        }
    })

    # scaling should be applied only if current room has a scaling associated
    if dt.room_scaling:
        e.add_component({
            'type': 'components.scaler',
            'p0': dt.room_scaling[0],
            'p1': dt.room_scaling[1]
        })
    # shadow
    apply_shadow = getattr(dt, 'apply_shadow', False)
    if apply_shadow:
        shadow = Entity()
        shadow.add_component(ShadowRenderer(**dt.shadow))
        e.add(shadow)
    return e


def pr3D(ciao):
    t = get_char_desc(ciao)
    model_desc = t.get('model')
    dt = monkey.engine.data.globals
    is_sprite = isinstance(model_desc, str)
    max_speed = t.get('max_speed', dt.default_speed)
    jump_height = t.get('jump_height', dt.default_jump_height)
    time_to_jump_apex = t.get('time_to_jump_apex', dt.default_time_to_jump_apex)
    gravity = (2.0 * jump_height) / (time_to_jump_apex * time_to_jump_apex)
    e = common3D(t)
    walk_state = {
        'id': 'walk',
        'type': 'state.foe_path',
        'moves': ciao['moves'],
        'max_speed': max_speed,
        'gravity': gravity
    }
    states = [walk_state]
    state_machine = {
        'type': 'components.state_machine',
        'initial_state': 'walk',
        'states': states
    }
    e.components.append(state_machine)

    return e


# an AABB that triggers a callback when player collides with it
def collider(ciao):
    e = Entity()
    dt = monkey.engine.data.globals
    size = ciao['size']
    e.add_component(Collider(shape=sh3d.AABB(size), flag=dt.CollisionFlags.foe, mask=dt.CollisionFlags.player,
                             tag=dt.CollisionTags.player_callback, debug=dt.show_boxes))
    e.add_component(Info(func=ciao['func']))
    return e


def foe3D(ciao):
    t = get_char_desc(ciao)
    model_desc = t.get('model')
    dt = monkey.engine.data.globals
    is_sprite = isinstance(model_desc, str)
    e = common3D(t)
    #return e
    max_speed = t.get('max_speed', dt.default_speed)
    time_acc = t.get('time_acc', dt.default_time_acc)
    jump_height = t.get('jump_height', dt.default_jump_height)
    time_to_jump_apex = t.get('time_to_jump_apex', dt.default_time_to_jump_apex)
    attacks = t.get('attacks', None)
    n_attacks = len(attacks) - 1 if attacks else 0

    gravity = (2.0 * jump_height) / (time_to_jump_apex * time_to_jump_apex)
    jump_speed = abs(gravity) * time_to_jump_apex
    walk_state = {
        'id': 'walk',
        'type': 'state.foe_chase_3D',
        'max_speed': max_speed,
        'time_acc': time_acc,
        'gravity': gravity,
        'walk_state': 'walk',
        'jump_speed': jump_speed,
        'attacks': attacks
    }

    hit_state = {
        'id': 'hit',
        'type': 'state.hit',
        'max_speed': 4 * max_speed,
        'time_acc': 0.5,
        'gravity': gravity,
        'hit_anim': 'hit',
        'next_state': 'walk'
    }

    states = [walk_state, hit_state]
    states.extend(make_death_sequence(model_desc, gravity, max_speed))

    state_machine = {
        'type': 'components.state_machine',
        'initial_state': 'walk',
        'states': states
    }

    if n_attacks > 0:
        for i in range(0, n_attacks):
            a_id = 'attack_' + str(i)
            attack_style = attacks[i].get('style', 'anim')
            win_anim = attacks[i].get('win', 'idle')
            win_dist = attacks[i].get('dist', 80)
            if attack_style == 'anim':
                state_machine['states'].append({
                    'id': a_id,
                    'type': 'state.anim',
                    'anim': a_id,
                    'next_state': 'walk'
                })
            elif attack_style == 'jmp':
                state_machine['states'].append({
                    'id': a_id,
                    'type': 'state.jump_attack',
                    #'anim': a_id,
                    'next_state': 'walk',
                    'max_speed': max_speed,
                    'gravity': gravity,
                    'cast_mask': dt.CollisionFlags.player,
                    'cast_tag': dt.CollisionTags.big_foe,
                    'peak_height': 200,
                    'down_speed': 1000.0
                })
                state_machine['states'].append({
                    'id': 'land',
                    'type': 'state.anim',
                    'anim': 'land',
                    'next_state': 'idle'
                })
                state_machine['states'].append({
                    'id': 'idle',
                    'type': 'state.foe_path',
                    'moves': [
                        {'direction': [1, 0, 0], 'distance': win_dist, 'on_end': 0, 'anim': 'walk'},
                        {'direction': [1, 0, 0], 'distance': 0, 'on_end': 0, 'anim': win_anim},
                    ],
                    'max_speed': max_speed,
                    'gravity': gravity
                })



    e.components.append(state_machine)
    if is_sprite:
        e.add_component(SmartCollider(
            flag=dt.CollisionFlags.foe,
            mask=dt.CollisionFlags.player_attack,
            tag=dt.CollisionTags.foe,
            debug=True,
            cast_tag=dt.CollisionTags.foe_attack,
            cast_mask=dt.CollisionFlags.player))
    else:
        e.add_component(SkeletalCollider(
            flag=dt.CollisionFlags.foe,
            mask=dt.CollisionFlags.player_attack,
            tag=dt.CollisionTags.foe,
            cast_tag=dt.CollisionTags.foe_attack,
            cast_mask=dt.CollisionFlags.player))
    # apply_shadow = getattr(dt, 'apply_shadow', False)
    # if apply_shadow:
    #     shadow = Entity()
    #     shadow.add_component(ShadowRenderer(angle=20.0))
    #     e.add(shadow)
    return e


def make_death_sequence(model, gravity, speed):
    # get animations
    if isinstance(model, str):
        anims = monkey.engine.get_asset(model)['animations']
    else:
        anims = dict()
    dseq = []

    if 'airfall' in anims and 'liedown' in anims:
        dseq.append({
            'id': 'dead',
            'type': 'state.dead',
            'max_speed': mopy.monkey.engine.data.globals.dead_sequnce_vel[0],
            'vy': mopy.monkey.engine.data.globals.dead_sequnce_vel[1],
            'gravity': gravity * 0.5,
            'start_anim': 'hit',
            'fall_anim': 'airfall',
            'lie_anim': 'liedown',
            'blink_after': mopy.monkey.engine.data.globals.dead_sequence_blink_after,
            'remove_after': mopy.monkey.engine.data.globals.dead_sequence_remove_after,
        })
    elif 'dead_0' in anims:
        j = 0
        while 'dead_' + str(j) in anims:
            dseq.append({
                'id': 'dead_' + str(j),
                'type': 'state.anim',
                'anim': 'dead_' + str(j)
            })
            j += 1
    else:
        dseq.append({
            'id': 'dead',
            'type': 'state.hit',
            'max_speed': 8 * speed,
            'timeout': 1,
            'gravity': gravity,
            'hit_anim': 'hit'
        })
    return dseq

def wa3d(desc):
    outline = desc.get('poly')
    depth = desc.get('depth')
    fy = desc.get('fy', 0)
    if fy > 0:
        outline = [fy - outline[i] if i % 2 == 1 else outline[i] for i in range(0, len(outline))]
        print(outline)
    height = desc.get('height', 1.0)
    depth_y = depth * math.sqrt(2.0)
    y0 = outline[1] - depth - height
    x0 = 0
    z0 = -depth_y
    pos = (x0, y0, z0)
    top = (x0, y0 + height, z0)
    #vars.walk_areas.append (WalkAreaInfo(x0, y0 + height, z0, fy, outline[1]))
    color = desc.get('color', [1, 1, 1, 1])
    oline = []
    a0 = 0 #outline[1]
    for i in range(0, len(outline), 2):
        oline.append(outline[i] - x0)
        oline.append((outline[i+1] - a0) * math.sqrt(2.0))
    print(oline)

    pos=(0,0,0)
    e = Entity(pos=pos)
    e.auto_pos= True
    shape = sh3d.Prism(shape=sh.Poly(outline=oline), height=height, walls=desc.get('walls',[]))
    print(shape)
    e.model = {'type': 'model.shape', 'shape': shape, 'color': color}
    #e.add_component(ShapeGfxColor(shape=shape, color=color))
    dt = monkey.engine.data.globals
    e.add_component(Collider(shape=shape, flag=dt.CollisionFlags.platform, mask=0, tag=dt.CollisionTags.platform))
    return e



def get_char_desc(ciao):
    id = ciao.get('id')
    if not id:
        print ('** unknown character: ' + str(id))
        exit(1)
    t = copy.deepcopy(monkey.engine.get_asset(id))
    model_desc = t.get('model')
    dt = monkey.engine.data.globals
    is_sprite = isinstance(model_desc, str)
    return t

def player3D(ciao):
    t = get_char_desc(ciao)
    model_desc = t.get('model')
    dt = monkey.engine.data.globals
    is_sprite = isinstance(model_desc, str)
    e = common3D(t)
    e.tag = 'player'
    max_speed = t.get('max_speed', dt.default_speed)
    time_acc = t.get('time_acc', dt.default_time_acc)
    jump_height = t.get('jump_height', dt.default_jump_height)
    time_to_jump_apex = t.get('time_to_jump_apex', dt.default_time_to_jump_apex)
    attacks = t.get('attacks', None)
    jattacks = t.get('jump_attacks', None)
    n_attacks = len(attacks) - 1 if attacks else 0
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

    jump_state = {
        'id': 'jump',
        'type': 'state.player_jump_3D',
        'max_speed': max_speed,
        'time_acc': time_acc,
        'gravity': gravity,
        'anim_up': 'jumpup',
        'anim_down': 'jumpdown',
    }

    hit_state = {
        'id': 'hit',
        'type': 'state.hit',
        'max_speed': max_speed,
        'time_acc': 0.2,
        'gravity': gravity,
        'hit_anim': 'hit',
        'next_state': 'walk'
    }

    # handle death sequence
    # case 1. animations include airfall and liedown -->
    # case 2. animations include dead_n --> add
    states = [walk_state, hit_state, jump_state]


    states.extend(make_death_sequence(model_desc, gravity, max_speed))


    state_machine = {
        'type': 'components.state_machine',
        'initial_state': 'walk',
        'states': states
    }

    akeys = getattr(monkey.engine.data.globals, 'attack_keys')

    if n_attacks > 0:
        walk_state['keys'] = []
        for i in range(0, n_attacks):
            a_id = 'attack_' + str(i)
            walk_state['keys'].append({'key': akeys[i] , 'action': {'type':'stateaction.statetransition', 'state': a_id}})
            state_machine['states'].append({
                'id': a_id,
                'type': 'state.anim',
                'anim': a_id,
                'next_state': 'walk'
            })

    if jattacks:
        jump_state['keys'] = []
        i = 0
        for attack in jattacks:
            jump_state['keys'].append({'key': akeys[i], 'action': {'type': 'stateaction.play_anim', 'anim': attack['anim']}})
            i += 1
        print(jump_state['keys'])
        #exit(1)

    e.components.append(state_machine)
    if is_sprite:
        e.add_component(SmartCollider(
            flag=dt.CollisionFlags.player,
            mask=dt.CollisionFlags.foe_attack,
            tag=dt.CollisionTags.player,
            debug=True,
            cast_tag=dt.CollisionTags.player_attack,
            cast_mask=dt.CollisionFlags.foe | dt.CollisionFlags.platform))
    else:
        e.add_component(SkeletalCollider(
            flag=dt.CollisionFlags.player,
            mask=dt.CollisionFlags.foe_attack,
            tag=dt.CollisionTags.player,
            cast_tag=dt.CollisionTags.player_attack,
            cast_mask=dt.CollisionFlags.foe | dt.CollisionFlags.platform))



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
        'cast_mask': monkey.engine.data.CollisionFlags.foe,
        'cast_tag': getattr(monkey.engine.data.CollisionTags, 'player_attack'),
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
    top_tex = ciao.get('top')
    side_tex = ciao.get('side')
    collision_tag = ciao.get('collision_tag', 0)
    shape = sh3d.Prism(shape=sh.Poly(outline=outline), height=height, walls=ciao.get('walls', []))
    if top_tex and side_tex:
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
