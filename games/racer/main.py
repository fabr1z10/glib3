from mopy.engine import Engine
import data

engine = Engine(data=data)

#
# import sys
# from pathlib import Path
#
# # link libraries
# path = Path(__file__)
# sys.path.append(str(path.parent.parent / 'lib'))
#
# # start up engine
# import lib.engine as eng
# import shader
# import factories.roomdefault
# import factories.items
#
#
# engine = eng.Engine()
#
# # add here add-on libraries you need
# engine.libs.append('racer')
# engine.add_shader(shader.ShaderType.unlit_textured)
# engine.add_shader(shader.ShaderType.unlit_color)
# engine.add_shader(shader.ShaderType.text)
#
# engine.add_room_factory('default', factories.roomdefault.make_platformer_room)
#
#
# # itme factories
# engine.add_item_factory('platform', factories.items.platform)
# engine.add_item_factory('incline_platform', factories.items.incline_platform)
# engine.add_item_factory('player', factories.items.player)
