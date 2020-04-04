from lib_py.scumm.scumm import State
from lib_py.scumm.scumm import Item
from lib_py.scumm.scumm import DynamicItem
import lib_py.scumm.entity as se
import lib_py.engine as engine
import lib_py.scumm.scripts as ssc
from mi1_py.text.eng.text import strings as s


#		offset = {-10,0},
st = engine.data['strings']

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

State.addItem (
    id = 'lookout.lookout', 
    item = Item(
        text = s['objects']['lookout'], 
        width = 20, 
        height = 47, 
        offset= [-10,0],
        walkto = [134, 36], 
        dir = 'w',
        actions = {
            'look': ssc.say(lines=[st['dialogues']['lookout'][51]])

        }

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