import example
import lib_py.engine as engine

engine.startUp()

engine.device_size = [256, 256]
engine.window_size = [512, 512]
engine.title = 'Physics test'
engine.room = 'test1'

engine.addFont (engine.assets.Font('main', './fonts/arial.ttf'))

import physics.rooms.test1
