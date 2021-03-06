from lib_py.scumm.scumm import State
from lib_py.scumm.entity import Item, CharItem
import lib_py.scumm.scripts as ssc
import lib_py.engine as engine
import mi1_py.variables as var

st = engine.data['strings']
sl = st['dialogues']['lookout']

State.addItem (Item(
    id = 'lookout.fire',
    model = 'fire', 
    pos = (126, 52)))

State.addItem (Item(
    id = 'lookout.stairs', 
    text = st['objects']['stairs'],
    pos = (230, 0),
    width = 30, 
    height = 10, 
    walkto = var.lookout_stairs, 
    dir = 's',
    actions = {
        'walkto': ssc.changeRoom(room = 'village1', pos = [8, 71, 0], dir='s')
    }))

State.addItem (CharItem (
    id = 'lookout',
    text = st['objects']['lookout'],
    model='lookout', 
    pos = (114, 36),
    width = 20, 
    height = 47, 
    offset= [-10,0],
    walkto = [134, 36], 
    dir = 'w', 
    state='idle', 
    text_color=[170, 170, 170, 255], 
    text_offset=[0,60],
    chardir = 'w',
    speed = 100,
    actions = {
        'look': ssc.say(lines=[st['dialogues']['lookout'][50]]),
        'talkto': ssc.startDialogue('lookout')
    }
))

# State.addItem (Item(
#     id = 'lookout.lookout', 
#     text = st['objects']['lookout'],
#     width = 20, 
#     height = 47, 
#     offset= [-10,0],
#     walkto = [134, 36], 
#     dir = 'w',


