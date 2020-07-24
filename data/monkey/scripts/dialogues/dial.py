from lib_py.script import Script
from lib_py.scumm.actions import Say, StartDialogue, Turn
from lib_py.actions import ChangeRoom, Animate
from lib_py.scumm.helper import gt, gd, gv, sv
from lib_py.scumm.scumm import Data, State
from lib_py.engine import data

slo = data['strings']['dialogues']['lookout']

def lookout_intro(line):
    def f():
        lines = []
        if not gv('@talked_to_lookout'):
            sv('@talked_to_lookout', True)
            lines = [slo[5], slo[6], slo[7], slo[8], slo[9]]
        else:
            lines = [slo[5], slo[43]]
        s = Script()
        s.addAction (Say(lines=[slo[line]], tag='player', font='monkey'))
        s.addAction (Turn (dir='s', tag='lookout'))
        s.addAction (Say(lines=lines, tag='lookout', font='monkey'))
        return s
    return f

def onend_lookout():
    s = Script()
    s.addAction (Turn(dir='w', tag='lookout'))
    return s

lookout_intro1 = lookout_intro('intro1')
lookout_intro2 = lookout_intro('intro2')
lookout_intro3 = lookout_intro('intro3')
lookout_intro4 = lookout_intro('intro4')