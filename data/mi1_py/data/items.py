import mi1_py.data.lookout
from lib_py.scumm.scumm import State
import lib_py.engine as engine
from lib_py.scumm.scumm import DynamicItem
import lib_py.scumm.entity as se


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