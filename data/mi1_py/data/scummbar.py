from lib_py.scumm.scumm import State
from lib_py.scumm.scumm import Item
from lib_py.scumm.dialogue import Dialogue, NodeStatus
from lib_py.scumm.dialogue import Line, DialogueNode
from lib_py.script import Script
import lib_py.scumm.actions as sa
import lib_py.scumm.scripts as ssc
import lib_py.engine as engine
import mi1_py.variables as var
import example

st = engine.data['strings']


# engine.items['scummbar.door.out'] = make_door {
# 	tag = 'scummbar.door.out',
# 	model = 'door_scummbar_village',
# 	pos = {32, 24, -1},
# 	size = {38, 47},
# 	walk_to = mi.rooms.scummbar.door_out,
# 	dir = 'w',
# 	var = 'door_village_scummbar',
# 	go_to = {
# 		room = 'village1',
# 		pos = mi.rooms.village1.door,
# 		dir = 's'
# 	}
# }

# door leading out
State.addItem(
    id = 'scummbar.door.out',
    item = Item(
        text = st['objects']['door'],
        width = 38,
        height = 47,
        walkto = var.scummbar_door_pos,
        dir = 'w',
        actions = {
            'open': ssc.openDoor (doorId='scummbar.door.out', var = 'door.village.scummbar'),
            'close': ssc.closeDoor (doorId='scummbar.door.out', var = 'door.village.scummbar'),
            'walkto': ssc.walkDoor (var = 'door.village.scummbar', room='village1', pos=var.village1_door_pos, dir='s')
        }
    )
)
