from lib_py.scumm.scumm import State
from lib_py.scumm.scumm import Item
from lib_py.scumm.scumm import DynamicItem
import lib_py.scumm.entity as se
import lib_py.engine as engine
from mi1_py.text.eng.text import strings as s



# interactive items
State.addItem (
    id = 'lookout.stairs', 
    item = Item(
        text = s['objects']['stairs'], 
        width = 30, 
        height = 10, 
        walkto = [250, 0], 
        dir = 's',

        )
    )


# dynamic items
engine.addEntity(
    id = 'guybrush',
    e = se.Character(
        model = 'guybrush', 
        speed = 100, 
        dir = 'e', 
        state = 'idle',
        text_color = [255, 255, 255, 255],
	    text_offset = [0, 60]
    ))



# place dynamic items in rooms
State.setDynamicItem (room='lookout', item = DynamicItem(
    id = 'guybrush', params = { 'tag': 'player', 'pos': [200,30,0], 'dir': 's', 'state': 'idle'}, parent='walkarea' ))