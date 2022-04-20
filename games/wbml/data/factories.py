from mopy.entity import Entity
import mopy.monkey as monkey
import data
from mopy.components import Collider, Info, Platform, PolygonalMover
import mopy
import mopy.util as utils
import mopy.shapes as sh
import mopy.factories.items as items
import copy
from mopy.actions import Blink, SetVariable
from mopy.room import build_entity
from mopy.script import Script
import example

def foe(args):
    gl = mopy.monkey.engine.data.globals
    e = Entity()
    e.model = args['model']

    size = args['size']
    max_speed = args['max_speed']
    gravity, jump_speed = utils.compute_gravity(monkey.engine.data.globals.jump_height,
                                                monkey.engine.data.globals.time_to_jump_apex)
    flip_on_edge = args.get('flip_on_edge', False)

    e.add_component({
        'type': 'components.smart_collider',
        'tag': gl.CollisionTags.foe,
        'flag': gl.CollisionFlags.foe,
        'mask': gl.CollisionFlags.player,
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
            'direction': args.get('direction', -1),
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


def ciappo(e):
    gl = mopy.monkey.engine.data.globals
    gl.invincible = True
    example.get('player').setState('walk', {})
    s = Script()
    s.seq([
        Blink(duration=gl.invincible_time, blink_duration=0.1, tag='player'),
        SetVariable(name='globals.invincible', value=False)
    ])
    example.play(s)





def player(args):
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
            'key': data.globals.Keys.up,
            'action': {
                'type': 'stateaction.callback',
                'f': data.scripts.enter_door
            }
        }, {
            'key': data.globals.Keys.attack,
            'action': {
                'type': 'stateaction.statetransition',
                'state': 'attack'
            }
        }]
    p.components[-1]['states'].append({
        'type': 'state.anim',
        'id': 'knock',
        'anim': 'knock'
    })
    p.components[-1]['states'].append({
        'id': 'attack',
        'type': 'state.anim',
        'anim': 'attack',
        'next_state': 'walk'
    })
    p.components[-1]['states'].append({
        'id': 'hit',
        'type': 'state.npc_walk',
        'max_speed': 100,
        'jump_speed': 0,
        'gravity': data.globals.gravity,
        'walk': 'hit',
        'walk_anim': 'hit',
        'jump_up_anim': 'hit',
        'jump_down_anim': 'hit',
        'on_land': ciappo
    })
    p.pos = utils.tiles_to_world(data.globals.start_positions[data.globals.start_position]['pos'], data.globals.tile_size)
    p.auto_pos = True
    return p


def rect(args):
    p = items.rect_platform(args)
    size = args.get('size')
    tiles = args.get('tiles')
    data = []
    for j in range(0, size[1] - 1):
        for i in range(0, size[0]):
            tile = None
            if i == 0 and size[0] > 1:
                tile = (6, 7)
            elif i == size[0] - 1 and size[0] > 1:
                tile = (10, 11)
            else:
                tile = (8, 9)
            data.extend([tiles[tile[0]], tiles[tile[1]]])
    for i in range(0, size[0]):
        tile = None
        if i == 0 and size[0] > 1:
            tile = (0, 1)
        elif i == size[0] - 1 and size[0] > 1:
            tile = (4, 5)
        else:
            tile = (2, 3)
        data.extend([tiles[tile[0]], tiles[tile[1]]])
    p.model = {
        'type': 'model.tiled',
        'tex': 'gfx/wbml.png',
        'img_tile_size': [16, 16],
        'tile_size': [16, 16],
        'size': size,
        'data': data
    }
    return p


def bg(args):
    e = Entity()
    asset = copy.deepcopy(monkey.engine.get_asset(args.get('model', None)))
    e.anim = args.get('anim', None)
    e.tag = args.get('tag')
    if 'tile_size' not in asset:
        asset['tile_size'] = [16, 16]
    e.model = asset

    print ('THE TAG IS ' + str(e.tag))
    e.read_children(args)
    return e


def trunk(args):
    door = args.get('door')
    tag= 'door_' + str(door)
    e = Entity()
    e.model = 'model.trunk'
    door_info = mopy.monkey.engine.data.globals.doors[door]
    if door_info['open'] == 1:
        anim = door_info['anim']
    else:
        anim = 'barred'
    e.children.append(build_entity({
        'type': '_line',
        'size': [4, 0],
        'pass_thru': True},
        [1, 4]))


    e.children.append(build_entity({
        'type': 'bg', 'model': 'sprites.door', 'anim': anim, 'tag': tag}, [2, 0, 0]))
    # check if door is available
    if door_info['open'] == 1:
        coll = Entity()
        coll.add_component(Collider(shape={
            'type': 'shape3d.aabb',
            'size': [16, 32, 0]},
            flag=12,
            mask=mopy.monkey.engine.data.globals.CollisionFlags.player,
            tag=mopy.monkey.engine.data.globals.CollisionTags.door,
            debug=True))
        coll.pos =[2.5*16, 0, 0]
        coll.add_component(Info(door_id=door))

        e.children.append(coll)
    return e


def moving_platform(args):
    e = Entity()
    gl = mopy.monkey.engine.data.globals
    width = args.get('width')
    points = args.get('points')
    points = [x*16 for x in points]
    speed = args.get('speed')
    e.model = {
        'type': 'model.tiled',
        'tex': 'gfx/wbml.png',
        'img_tile_size': [16, 16],
        'tile_size': [16, 16],
        'size': [width, 1],
        'data': [0, 9] * width
    }
    e.add_component(Platform())
    e.add_component(Collider(debug=True,flag=gl.CollisionFlags.platform_passthrough, mask=gl.CollisionFlags.player, tag=0,
        shape=sh.Line(a=[0, 16, 0], b=[width * 16, 16, 0])))
    e.add_component(PolygonalMover(points=points, speed=speed, mode=1))
        #e.add_component(comp.PolygonalMover(origin=(pos[0],pos[1]), loop=args[6], pct=args[4], moves=[
        #    {'delta': [0, args[5]*vars.tile_size], 'speed': args[7], 'hold': 0}]))
    return e