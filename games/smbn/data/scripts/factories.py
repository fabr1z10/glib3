from mopy.entity import Entity
from mopy.script import Script
import mopy.actions as act
import example
import mopy.util as utils
import mopy.monkey as monkey
import data


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