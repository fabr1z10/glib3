##########################
# main function
# ----------------------------------------------
#  this shouldn't change much across games.
#  Typically you call startUp and init factories to initialize
#  factories for rooms and items.

import example
import sys
import vars as v

from pathlib import Path

# add folder
path = Path(__file__)
sys.path.append(str(path.parent.parent / 'lib'))

import lib.engine as eng
import factories.roomdefault
import shader

engine = eng.Engine()

engine.add_shader(shader.ShaderType.unlit_textured)
engine.add_shader(shader.ShaderType.unlit_color)
engine.add_shader(shader.ShaderType.text)


engine.add_room_factory('default', factories.roomdefault.make_platformer_room)




engine.vars = v
#engine.startUp()

#initFactories()
