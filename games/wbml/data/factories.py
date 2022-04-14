from mopy.entity import Entity
import mopy.monkey as monkey
import data
import mopy.util as utils
import mopy.factories.items as items
import copy


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
    e.tag = args.get('tag')
    if 'tile_size' not in asset:
        asset['tile_size'] = [16, 16]
    e.model = asset
    print ('THE TAG IS ' + str(e.tag))
    e.read_children(args)
    return e
