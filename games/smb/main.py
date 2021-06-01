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
import factories.items

import shader

engine = eng.Engine()

# add here add-on libraries you need
engine.libs.append('platformer')

engine.add_shader(shader.ShaderType.unlit_textured)
engine.add_shader(shader.ShaderType.unlit_color)
engine.add_shader(shader.ShaderType.text)


engine.add_room_factory('default', factories.roomdefault.make_platformer_room)
engine.add_item_factory('platform', factories.items.platform)
engine.add_item_factory('player', factories.items.player)
engine.add_item_factory('foe', factories.items.foe)
engine.add_item_factory('koopa', factories.items.koopa)
engine.add_item_factory('plant', factories.items.plant)
engine.add_item_factory('pipe', factories.items.pipe)

engine.add_item_factory('brick', factories.items.brick)
engine.add_item_factory('mushroom_brick', factories.items.mushroom_brick)
engine.add_item_factory('coin_brick', factories.items.coin_brick)
engine.add_item_factory('multi_coin_brick', factories.items.multi_coinbrick)
engine.add_item_factory('moving_bonus', factories.items.moving_bonus)
engine.add_item_factory('tile_map', factories.items.tile_map)
engine.add_item_factory('hotspot', factories.items.hotspot)
engine.add_item_factory('bg', factories.items.bg)
engine.add_item_factory('warp', factories.items.warp)
engine.add_item_factory('line', factories.items.line)
engine.add_item_factory('moving_platform', factories.items.moving_platform)

v.tile_data = engine.open_data_file('data.yaml')

engine.vars = v
#engine.startUp()

#initFactories()
