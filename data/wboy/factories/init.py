from factories.rooms.default import defaultRoom
from factories.items.items1 import img, sprite, platform, brick, tilemap, bgp, coinbrick, makeKoopa, mushroombrick, bg, makeSpawn, makePipeIn, line, makeCollect, multicoinbrick, makeMovingPlatform, makeSimpleFoe

from lib_py.engine import data

def initFactories():
    
    data ['factories']['rooms'] = {
        'default': defaultRoom
    }
    data ['factories']['items'] = {
        'img': img,
        'sprite': sprite,
        'platform': platform,
        'line': line,
        'brick': brick,
        'tilemap': tilemap,
        'coinbrick': coinbrick,
        'mcoinbrick': multicoinbrick,
        'mushroombrick': mushroombrick,
        'spawn': makeSpawn,
        'bg': bgp,
        'warp': makePipeIn,
        'collect': makeCollect,
        'movingplatform': makeMovingPlatform,
        'foe': makeSimpleFoe,
        'koopa': makeKoopa
    }    

