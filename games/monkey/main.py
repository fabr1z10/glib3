import mopy.scumm as scumm
import factories.room
import factories.items
import data
import init
import scripts

engine = scumm.init(data, scripts)

init.start()

# place custom factories here ...
engine.add_room_factory('default', factories.room.default_room)
engine.add_room_factory('map', factories.room.map_room)
engine.add_item_factory('bg', factories.items.bg)
engine.add_item_factory('walkarea', factories.items.walkarea)





# import sys
# from pathlib import Path
# import example
# import vars
# import status
#
#
# # import required libraries
# path = Path(example.dir)
# print(path)
# exit(1)
# sys.path.append(example.dir)
# sys.path.append(str(path.parent / 'lib'))
#
# import scumm.scumm as sx
#
#
# engine = sx.init_scumm(vars, status)
#
# import scripts.actions
# engine.scripts = scripts.actions
#
# import init
#
# init.village()
# # add here add-on libraries you need
#
#
