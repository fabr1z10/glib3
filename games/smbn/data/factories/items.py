from mopy.script import Script
import mopy.actions as act
import example
import mopy.util as utils
import mopy.monkey as monkey
import data
from mopy.entity import Entity, Text, TextAlignment
import mopy.monkey as monkey
import data
import mopy.util as utils
import mopy.factories.items as items
from mopy.components import Collider, Info
import copy
import mopy

def hotspot(args):
    glo = mopy.monkey.engine.data.globals
    hotspot = Entity()
    size = args['size']
    hotspot.add_component(Collider(debug=True, flag=glo.CollisionFlags.foe, mask=glo.CollisionFlags.player, tag=glo.CollisionTags.hotspot,
                                   shape=mopy.shapes3d.AABB([size[0], size[1], 1])))
    hotspot.add_component(Info(callback=args['callback'], args=args.get('args', [])))
    return hotspot



def scoreboard(args):
    glo = mopy.monkey.engine.data.globals
    font = 'sprites.mario_font'
    board = Entity()
    board.add(Text(font=font, size=8, text='MARIO', color=(1, 1, 1, 1), align=TextAlignment.top_left, pos=(32, 224, 0)))
    board.add(Text(font=font, size=8, text=str(glo.score), color=(1, 1, 1, 1), align=TextAlignment.top_left, pos=(32, 216, 0), tag='label_score'))
    board.add(Text(font=font, size=8, text='WORLD', color=(1, 1, 1, 1), align=TextAlignment.top_left, pos=(136, 224, 0)))
    board.add(Text(font=font, size=8, text='x', color=(1, 1, 1, 1), align=TextAlignment.bottom, pos=(158, 208, 0), tag='label_world'))
    board.add(Text(font=font, size=8, text='TIME', color=(1, 1, 1, 1), align=TextAlignment.bottom_right, pos=(224, 216, 0)))
    board.add(Text(font=font, size=8, text='0', color=(1, 1, 1, 1), align=TextAlignment.bottom_right, pos=(224, 208, 0), tag='label_time'))
    return board

# - type: _fps_counter
# font: mario_font
# size: 8
# pos: [0, 15, 0]


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
    # add special keys
    # TODO change this... if player2D changes.. breaks everything
    p.components[-1]['states'][-1]['keys'] = [
        {
            'key': data.globals.Keys.down,
            'action': {
                'type': 'stateaction.callback',
                'f': data.scripts.warp_down
            }
        }]
    p.components[-1]['states'].append({
        'type': 'state.anim',
        'id': 'warp',
        'anim': 'idle'
    })
    # p.components[-1]['states'].append({
    #     'type': 'state.npc_walk',
    #     'id': 'npcwalk',
    #     'max_speed': 100,
    #     'gravity': data.globals.gravity,
    #     'jump_speed': 0,
    #     'collision_mask': 8
    # })
    p.components[-1]['states'].append({
        'type': 'state.anim',
        'id': 'slide',
        'anim': 'slide'
    })
    p.components[-1]['states'].append({
        'type': 'state.anim',
        'id': 'dead',
        'anim': 'dead'
    })
    p.pos = utils.tiles_to_world(data.globals.start_positions[data.globals.start_position]['pos'], data.globals.tile_size)
    p.auto_pos = True
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
        mdl = args.get('model', None)
        if mdl:
            asset = copy.deepcopy(monkey.engine.get_asset(args.get('model', None)))
            asset['tile_size'] = [16,16]
            p.model = asset

    return p


def coin(args):
    e = Entity()
    e.model = args.get('model', 'sprites.pickupcoin')
    e.add_component({
        'type': 'components.smart_collider',
        'tag': data.CollisionTags.pickup_coin,
        'flag': data.CollisionFlags.foe,
        'mask': data.CollisionFlags.player,
        'debug': True
    })
    return e



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

def on_create_flying_coin(nid, x, y, z):
    s = Script()
    yt = y + data.globals.tile_size[1]
    s.add_action(act.MoveAccelerated(v0=[0, 100], a=[0, -100], yStop=yt, entity_id=nid))
    s.add_action(act.RemoveEntity(nid))
    s.add_action(act.CreateEntity('scripts.factories.score_100', pos=(x, yt, z), use_tile=False))
    example.play(s)


def on_create_score_100(nid, x, y, z):
    data.tils.add_score(100)
    s = Script()
    s.add_action(act.Move(speed=100, by=[0, 64], entity_id=nid))
    s.add_action(act.RemoveEntity(nid))
    example.play(s)


def on_create_mushroom(nid, x, y, z):
    s = Script()
    s.add_action(act.Move(speed=10, by=[0, 16.1], entity_id=nid))
    s.add_action(act.SetState(entity_id=nid, state='walk'))
    example.play(s)

def score_100(args):
    e = Entity()
    e.model = 'score_100'
    e.on_create = on_create_score_100
    return e


def flying_coin(args):
    e = Entity()
    e.model = 'flying_coin'
    e.on_create = on_create_flying_coin
    return e

def mushroom(args):
    e = None
    if data.globals.player_mode == 0:
        e = bonus('mushroom', 10, data.CollisionTags.mushroom)
        e.on_create = on_create_mushroom
    else:
        e = bonus('flower', 0, data.CollisionTags.flower)
        e.on_create = on_create_mushroom
    return e

def mushroom_1up(args):
    e = bonus('mushroom_1up', 10, data.CollisionTags.mushroom)
    e.on_create = on_create_mushroom
    return e

def on_create_brick_piece(vx, vy):
    def f(nid, x, y, z):
        s = Script()
        s.add_action(act.MoveAccelerated(entity_id=nid, v0=[vx, vy], a=[0, -0.5 * data.globals.gravity], yStop=0))
        s.add_action(act.RemoveEntity(entity_id=nid))
        example.play(s)
    return f


def brick_piece(args):
    e = Entity()
    e.model = args['model']
    e.on_create = on_create_brick_piece(args['vx'], args['vy'])
    return e


def bonus(model, speed, tag):
    e = Entity()
    e.model = model
    size = data.globals.tile_size
    max_speed = speed
    gravity, jump_speed = utils.compute_gravity(monkey.engine.data.globals.jump_height,
                                                monkey.engine.data.globals.time_to_jump_apex)
    e.add_component({
        'type': 'components.smart_collider',
        'tag': tag,
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
        'initial_state': 'idle',
        'states': [{
            'id': 'walk',
            'type': 'state.npc_walk',
            'flip_hor': False,
            'max_speed': max_speed,
            'jump_speed': jump_speed,
            'gravity': gravity,
            'jump_up_anim': 'walk',
            'jump_down_anim': 'walk',
            'flip_on_edge': False
        }, {
            'id': 'idle',
            'type': 'state.null',
        }]
    })
    return e