import example
import lib_py.engine as engine
import lib_py.scumm.scumm as scumm
import lib_py.scumm.functions as func
import lib_py.scumm.helper as helper
import lib_py.scumm.scripts as sscripts

from outrun.factories.rooms.default import defaultRoom
#from smb_py.factories.items.items1 import img, sprite, platform, brick, tilemap, coinbrick, mushroombrick, bg, makeSpawn, makePipeIn, line, makeCollect, multicoinbrick, makeMovingPlatform
rf={
    'default': defaultRoom
}
fi={

}
# rf = {
#     'default': defaultRoom
# }

# fi = {
#     'img': img,
#     'sprite': sprite,
#     'platform': platform,
#     'line': line,
#     'brick': brick,
#     'tilemap': tilemap,
#     'coinbrick': coinbrick,
#     'mcoinbrick': multicoinbrick,
#     'mushroombrick': mushroombrick,
#     'spawn': makeSpawn,
#     'bg': bg,
#     'warp': makePipeIn,
#     'collect': makeCollect,
#     'movingplatform': makeMovingPlatform
# }

engine.startUp(rf,fi)
# engine.device_size = (256, 256)
# engine.window_size = (512, 512)
# engine.title = 'Super Mario Bros'
# engine.room = 'world1_1'

# engine.addFont (engine.assets.Font('main', './fonts/prstartk.ttf'))

# #engine.loadSprites()
# #engine.loadText ('eng')

# from smb_py.rooms import *
# #import smb_py.rooms.world1_1
