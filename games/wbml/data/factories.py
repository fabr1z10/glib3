from mopy.entity import Entity
import mopy.monkey as monkey
import data
from mopy.components import Collider, Info
import mopy
import mopy.util as utils
import mopy.factories.items as items
import copy
from mopy.room import build_entity

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
        }]
    p.components[-1]['states'].append({
        'type': 'state.anim',
        'id': 'knock',
        'anim': 'knock'
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