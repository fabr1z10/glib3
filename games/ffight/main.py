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
import factories.room
import factories.items

import shader

engine = eng.Engine()

# add here add-on libraries you need
engine.libs.append('platformer')

engine.add_shader(shader.ShaderType.unlit_textured)
engine.add_shader(shader.ShaderType.unlit_color)
engine.add_shader(shader.ShaderType.text)

#v.characters = engine.open_data_file('characters.yaml')

#player = v.characters[v.player]
#v.player_scale = player['scale']
#v.player_model = player['model']
#v.player_speed = player['speed']


#engine.add_room_factory('default', factories.roomdefault.make_platformer_room)
engine.add_room_factory('3d', factories.room.make_platformer_room_3d)

# engine.add_item_factory('floor', factories.items.floor)
# engine.add_item_factory('wall', factories.items.wall)
# engine.add_item_factory('block', factories.items.block)
# engine.add_item_factory('platform', factories.items.platform)
engine.add_item_factory('player', factories.items.character_player)
# engine.add_item_factory('player_beast', factories.items.character_player_beast)
# engine.add_item_factory('character', factories.items.character)
#
# engine.add_item_factory('skeleton', factories.items.skeleton_player)
# engine.add_item_factory('skeleton.foe', factories.items.skeleton_enemy)
# engine.add_item_factory('3d.skeleton', factories.items.skeleton_player_3d)
# engine.add_item_factory('item', factories.items.sprite_item)
# engine.add_item_factory('plane', factories.items.plane)
engine.add_item_factory('aabb', factories.items.aabb3d)
engine.add_item_factory('bg', factories.items.static_bg)

engine.vars = v
#engine.startUp()

#initFactories()
