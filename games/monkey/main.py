import sys
from pathlib import Path
import example
import vars
import status


# import required libraries
path = Path(example.dir)
sys.path.append(example.dir)
sys.path.append(str(path.parent / 'lib'))

import scumm.scumm as sx
import factories.room
import factories.items


engine = sx.init_scumm(vars, status)

import scripts.actions
engine.scripts = scripts.actions

import init

init.start()
# add here add-on libraries you need


# place custom factories here ...
engine.add_room_factory('default', factories.room.default_room)
engine.add_room_factory('map', factories.room.map_room)


engine.add_item_factory('bg', factories.items.bg)
engine.add_item_factory('walkarea', factories.items.walkarea)
