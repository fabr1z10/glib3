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

State.addItem (
    id = 'village1.poster', 
    item = Item(
        text = st['objects']['poster'],
        width = 20, 
        height = 23, 
        walkto = [269, 15], 
        dir = 'n',
        actions = {
            'look': ssc.say(lines=[ st['lines'][1], st['lines'][2] ]),
        }))

# door to Scumm bar
State.addItem(
    id = 'village1.door',
    item = Item(
        text = st['objects']['door'],
        width= 30,
        height= 45,
        walkto = var.village1_door_pos,
        dir = 'n',
        actions = {
            'open': ssc.openDoor (doorId='village1.door', var='door.village.scummbar'),
            'close': ssc.closeDoor (doorId='village1.door', var = 'door.village.scummbar'),
            'walkto': ssc.walkDoor (var='door.village.scummbar', room='scummbar', pos = var.scummbar_door_pos, dir='e')
        }
    )
)
