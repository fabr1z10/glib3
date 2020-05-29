from lib_py.scumm.scumm import State
from lib_py.scumm.entity import Item
import lib_py.scumm.scripts as ssc
import lib_py.engine as engine
import mi1_py.variables as var

st = engine.data['strings']

State.addItem (Item(
    id = 'village1.cliffside', 
    text = st['objects']['cliffside'],
    pos = (0, 0),
    width = 10, 
    height = 144, 
    walkto = (10, 144), 
    dir = 'w',
    actions = {
        'walkto': ssc.changeRoom(room = 'lookout', pos =var.lookout_stairs, dir='n')
    }))
    
State.addItem (Item(
    id = 'village1.poster', 
    text = st['objects']['poster'],
    pos = (259, 27),
    width = 20, 
    height = 23, 
    walkto = [269, 15], 
    dir = 'n',
    actions = {
        'look': ssc.say(lines=[ st['lines'][1], st['lines'][2] ]),
    }))

# door to Scumm bar
State.addItem( Item(
    id = 'village1.door',
    text = st['objects']['door'],
    model = 'door_village_scummbar',
    pos = (699, 7),
    width= 30,
    height= 45,
    walkto = var.village1_door_pos,
    dir = 'n',
    actions = {
        'open': ssc.openDoor (doorId='village1.door', var='village_scummbar'),
        'close': ssc.closeDoor (doorId='village1.door', var = 'village_scummbar'),
        'walkto': ssc.walkDoor (var='village_scummbar', room='scummbar', pos = var.scummbar_door_pos, dir='e')
    }))
