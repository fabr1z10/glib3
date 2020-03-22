import sys

sys.path.append('/home/fabrizio/glib3/data')

import lib_py.engine as engine
import settings

settings.monkey = engine.Engine(deviceSize=[320,200], windowSize=[640,400], uiHeight = 56, startRoom='lookout')

settings.monkey.title = 'The secret of Monkey Island'

import rooms.lookout
