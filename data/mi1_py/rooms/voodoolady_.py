from lib_py.scumm.scumm import State
from lib_py.scumm.entity import Item, CharItem
import lib_py.scumm.scripts as ssc
from lib_py.scumm.functions import d3
import lib_py.engine as engine
import mi1_py.variables as var
from lib_py.script import Script
from lib_py.actions import RunScript,Animate,SetActive,Scroll,Move,Delay
from lib_py.scumm.actions import EnableControls, Turn, Say

st = engine.data['strings']
sl = engine.data['strings']['lines']

def look_knickknacks():
    s = Script()
    s.addAction (Say(tag='player', lines= [sl[16],sl[17],sl[18],sl[19]]))
    s.addAction (Turn(tag='player', dir='s'))
    s.addAction (Say(tag='player', lines= [sl[20],sl[21]]))
    return s

# door to voodoo lady
State.addItem( Item(
    id = 'voodoolady.door',
    text = st['objects']['door'],
    model = 'door_voodoolady_village',
    pos = (87, 42),
    width= 33,
    height= 58,
    walkto = var.voodoolady_door_pos,
    dir = 'w',
    actions = {
        'open': ssc.openDoor (doorId='voodoolady.door', var='village_voodoolady'),
        'close': ssc.closeDoor (doorId='voodoolady.door', var = 'village_voodoolady'),
        'walkto': ssc.walkDoor (var='village_voodoolady', room='village2', pos = var.village2_voodoolady, dir='w')
    }))

State.addItem(Item(
    id = 'voodoolady.baskets',
    text = st['objects']['baskets'],
    model = 'baskets',
    width = 50,
    height = 20,
    walkto= (100, 10),
    dir = 's',
    pos = (74, 0),
    actions = {
        'open': ssc.say(lines=[ sl[7], sl[8] ]),
        'look': ssc.say(lines=[ sl[9] ])
    }))

State.addItem(Item(
    id = 'voodoolady.trunk',
    text = st['objects']['trunk'],
    model = 'voodoolady_trunk',
    width = 70,
    height = 30,
    walkto= (260, 14),
    dir = 's',
    pos = (230, 0),
    actions = {
        'look': ssc.say(lines=[ sl[24] ])
    }))

State.addItem(Item(
    id = 'voodoolady.couch',
    text = st['objects']['couch'],
    width = 77,
    height = 28,
    walkto= (209, 40),
    dir = 'n',
    pos = (179, 46),
    actions = {
        'look': ssc.say(lines=[ sl[23] ]),
        'use': ssc.say(lines=[ sl[22] ])
    }))

State.addItem(Item(
    id = 'voodoolady.chalice',
    text = st['objects']['chalice'],
    width = 12,
    height = 14,
    walkto= (272, 8),
    dir = 's',
    priority=2,
    pos = (292, 12),
    actions = {
        'look': ssc.say(lines=[ sl[31] ])
    }))    

State.addItem(Item(
    id = 'voodoolady.knickknacks',
    text = st['objects']['knickknacks'],
    width = 35,
    height = 34,
    walkto= (189, 41),
    dir = 'n',
    pos = (176, 64),
    actions = {
        'look': look_knickknacks
    }))      

State.addItem(Item(
    id = 'voodoolady.statue',
    text = st['objects']['statue'],
    width = 24,
    height = 44,
    walkto= (185, 40),
    dir = 'w',
    pos = (153,44),
    actions = {
        'look':  ssc.say(lines=[ sl[15] ])
    }))      

State.addItem(Item(
    id = 'rubber.chicken',
    text = st['objects']['rubberchicken'],
    model='rubberchicken',
    width = 20,
    height = 20,
    walkto= (248, 12),
    priority=2,
    dir = 's',
    pos = (238, 16,1),
    actions = {
        'pickup': ssc.pickup('rubber.chicken')
    }))
