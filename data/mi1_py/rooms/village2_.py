from lib_py.scumm.scumm import State
from lib_py.scumm.entity import Item, CharItem
import lib_py.scumm.scripts as ssc
from lib_py.scumm.functions import d3
import lib_py.engine as engine
import mi1_py.variables as var
from lib_py.script import Script
from lib_py.actions import RunScript
from lib_py.scumm.actions import EnableControls
st = engine.data['strings']

State.addItem (Item(
    id = 'village2.archway', 
    text = st['objects']['archway'],
    pos = (416, 34),
    width = 40, 
    height = 50, 
    walkto = var.village2_village1,
    dir = 'n',
    actions = {
        'walkto': ssc.changeRoom(room = 'village1', pos = var.village1_village2, dir='w')
    }))

State.addItem (Item(
    id = 'village2.village3', 
    text = st['objects']['archway'],
    pos = (146, 63),
    width = 30, 
    height = 30, 
    walkto = var.village2_village3,
    dir = 'n',
    actions = {
        'walkto': ssc.changeRoom(room = 'village3', pos = var.village3_village2, dir='w')
    }))


def talkToCitizen():
    s = Script()
    s.addAction (EnableControls(False))
    lines = ('_', 27, 28) if var.knows_map == 1 else (('_', 1) if not var.talked_to_citizen else ('_', 8, 9))
    s.addAction (RunScript (d3 (st['dialogues']['citizen'], 
        ['citizen', 'a:talk_s', lines, 'a:idle_s'])()))
    s.addAction (RunScript (ssc.startDialogue('citizen')()))
    var.talked_to_citizen = 1
    return s


State.addItem(CharItem(
    id = 'citizen',
    text = st['objects']['citizen'],
    model = 'citizen',
    pos = (325, 27),
    width = 30,
    height= 40,
    walkto = (360, 27),
    dir = 'w',
    offset = (-15, 0),
    text_color= (255, 85, 85, 255),
    text_offset= (0, 60),
    speed = 0,
    state='idle',
    chardir='s',
    actions = {
        #'look': ssc.say(lines=[st['dialogues']['lookout'][50]]),
        'talkto': talkToCitizen
    }

))

State.addItem(Item(
    id = 'lmf',
    text = st['objects']['lowmoralfiber'],
    pos = (0,0),
    width =60,
    height=60,
    walkto = (85,14),
    dir = 'w'
))

State.addItem(CharItem(
    id = 'lmf1',
    model = 'lowmoral1',
	pos = (18, 10),
	text_color =(255, 85, 255, 255),
	text_offset = (0,60),
    state = 'idle',
    chardir='e',
	speed = 0))

State.addItem(CharItem(
    id = 'lmf2',
    model = 'lowmoral2',
	pos =(44, 20),
	text_color = (85, 255, 255, 255),
	text_offset = (0,60),
    state='idle',
    chardir='e',
	speed = 0))

State.addItem(CharItem(
    id = 'lmf3',
    model = 'lowmoral3',
	pos =(56, 23),
	text_color = (85, 255, 85, 255),
	text_offset = (0,60),
    state='idle',
    chardir='e',
	speed = 0))

State.addItem(CharItem(
    id = 'village2.rat',
    model = 'rat',
	pos =(56, 10),
	text_color = (170,170,170,170),
	text_offset = (0,60),
    state='idle',
    chardir='w',
	speed = 0))