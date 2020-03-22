import sys

sys.path.append('/Users/fabrizioventurini/glib3/data')

import lib_py.engine as engine
import lib_py.assets as assets
import settings

e = engine.Engine(deviceSize=[320,200], windowSize=[640,400], uiHeight = 56, startRoom='lookout')

e.addFont(assets.Font('ui', './fonts/monkeysmall.ttf'))
e.shaders = ['unlit_textured', 'unlit_color', 'text']
settings.monkey =e


settings.monkey.title = 'The secret of Monkey Island'

import rooms.lookout
