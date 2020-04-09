from lib_py.scumm.scumm import State
from lib_py.scumm.scumm import Item
from lib_py.scumm.dialogue import Dialogue
from lib_py.scumm.dialogue import DialogueLine
from lib_py.script import Script
import lib_py.scumm.actions as sa
import lib_py.scumm.scripts as ssc
import lib_py.engine as engine
import mi1_py.variables as var

st = engine.data['strings']
sl = st['dialogues']['lookout']

State.addItem (
    id = 'lookout.stairs', 
    item = Item(
        text = st['objects']['stairs'], 
        width = 30, 
        height = 10, 
        walkto = [250, 0], 
        dir = 's'))

State.addItem (
    id = 'lookout.lookout', 
    item = Item(
        text = st['objects']['lookout'],
        width = 20, 
        height = 47, 
        offset= [-10,0],
        walkto = [134, 36], 
        dir = 'w',
        actions = {
            'look': ssc.say(lines=[st['dialogues']['lookout'][50]]),
            'talkto': ssc.startDialogue('lookout')
        }))

d = Dialogue('lookout')

def f():
    print ('cane!')

def g():
    s = Script()
    l = [sl[5], sl[6], sl[7], sl[8], sl[9]] if not var.talked_to_lookout else [sl[5], sl[43], sl[53]]
    var.talked_to_lookout = True    
    s.addAction (sa.Say(lines = [sl[1]], tag='player'))
    s.addAction (sa.Turn(tag='lookout.lookout', dir='s'))
    s.addAction (sa.Say(tag='lookout.lookout', lines = l))
    return s    

d.addLine (1, 0, DialogueLine(sl[1], g, False, 1))
d.addLine (2, 0, DialogueLine(sl[2], f, False, 1))
d.addLine (3, 0, DialogueLine(sl[3], f, False, 1))
d.addLine (4, 0, DialogueLine(sl[4], f, False, 1))
d.addLine (6, 1, DialogueLine(sl[10], f, False, -1))
d.addLine (7, 1, DialogueLine(sl[11], f, False, -1))
d.addLine (8, 1, DialogueLine(sl[12], f, False, -1))

State.addDialogue (d)
