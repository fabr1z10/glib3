from lib_py.scumm.scumm import State
from lib_py.scumm.entity import Item, CharItem
import lib_py.scumm.scripts as ssc
from lib_py.scumm.functions import d3
import lib_py.engine as engine
import mi1_py.variables as var
from lib_py.script import Script
from lib_py.actions import RunScript,Animate,SetActive,Scroll,Move,Delay
from lib_py.scumm.actions import EnableControls, Turn
st = engine.data['strings']

def openFake(doorIn, doorOut, scrollPos, gotoPos, dir):
    def f():
        s = Script()
        s.addAction (Animate(tag=doorIn, anim = 'open'))
        s.addAction (Delay(0.5))
        s.addAction (SetActive(tag='player', value=False))
        s.addAction (Animate(tag=doorIn, anim = 'closed'))
        s.addAction (Scroll(pos=scrollPos, relative=False,speed=50,cam='maincam'))
        s.addAction (Animate(tag=doorOut, anim = 'open'))
        s.addAction (Delay(0.5))
        s.addAction (Move(immediate=True, speed=0, tag='player', to=gotoPos))
        s.addAction (Turn(dir=dir, tag='player'))
        s.addAction (SetActive(tag='player', value=True))
        s.addAction (Animate(tag=doorOut, anim = 'closed'))
        return s
    return f



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
    dir = 'w',
    actions = {
        'talkto': ssc.startDialogue('lowmoral')
    }

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

State.addItem(Item(
    id = 'village2.fakedoor1',
    text = st['objects']['door'],
    model = 'fakedoor1',
    width = 20,
    height = 30,
    walkto= (389, 36),
    dir = 'w',
    pos = (377, 37, -1),
    actions = {
        'open': openFake ('village2.fakedoor1', 'village2.fakedoor3', (160, 0), (135, 60), 's')
    }))

State.addItem(Item(
    id = 'village2.fakedoor2',
    text = st['objects']['door'],
    model = 'fakedoor2',
    width = 10,
    height = 20,
    walkto= (206, 58),
    dir = 'e',
    pos = (208, 59, -1),
    actions = {
        'open': openFake ('village2.fakedoor2', 'village2.fakedoor4', (188, 0), (188, 60), 'w')
    }))

State.addItem(Item(
    id = 'village2.fakedoor3',
    text = st['objects']['door'],
    model = 'fakedoor3',
    width = 10,
    height = 15,
    walkto= (135, 60),
    dir = 'n',
    pos = (130,63,-1),
    actions = {
        'open': openFake ('village2.fakedoor3', 'village2.fakedoor1', (389, 0), (389, 36), 'e')
    }))


State.addItem(Item(
    id = 'village2.fakedoor4',
    text = st['objects']['door'],
    model = 'fakedoor4',
    width = 10,
    height = 15,
    walkto= (188, 61),
    dir = 'n',
    pos = (184,64,-1),
    actions = {
        'open': openFake ('village2.fakedoor4', 'village2.fakedoor2', (206, 0), (206, 58), 'w')
    }))


# door to voodoo lady
State.addItem( Item(
    id = 'village2.door',
    text = st['objects']['door'],
    model = 'door_village_voodoolady',
    pos = (220, 52),
    width= 26,
    height= 26,
    walkto = (220, 48),
    dir = 'e',
    actions = {
        'open': ssc.openDoor (doorId='village2.door', var='village_voodoolady'),
        'close': ssc.closeDoor (doorId='village2.door', var = 'village_voodoolady'),
        'walkto': ssc.walkDoor (var='village_voodoolady', room='voodoolady', pos = var.voodoolady_door_pos, dir='e')
    }))