import example
import lib_py.engine as engine
import lib_py.scumm.scumm as scumm
import lib_py.scumm.functions as func
import lib_py.scumm.helper as helper
import lib_py.scumm.scripts as sscripts
import lib_py.scumm.entity as se

engine.startUp(lang='eng')

engine.addShader (engine.ShaderType.skeletal)
engine.device_size = (320, 200)
engine.window_size = (640, 400)
engine.title = 'Test'
engine.room = 'test1'

engine.addFont (engine.assets.Font('monkey', './fonts/prstartk.ttf'))

from rooms import *


