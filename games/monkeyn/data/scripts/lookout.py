### default actions
import mopy
import example
from mopy.script import Script
from mopy.actions import Walk, Turn, Say
import mopy.scumm.scriptlib as sl
import mopy.scumm.actionlib as al
import mopy.scumm as scumm
import random

def _a(*args):
    return ['$dialogues/lookout/' + str(x) for x in args]


def talkto_main_lookout(item_id, entity):
    return sl.walk_and_dialogue(item_id, 'lookout')


def lookout_start_dialogue(args):
    s = Script()
    s.add(Say(_a(args[0]), 'player'))
    s.add_action(Turn('s', 'main.lookout'))
    l = [5, 43, 53 + random.randint(0, 1)] if scumm.gl.talked_to_lookout == 1 else [5, 6, 7, 8, 9]
    s.add(Say(_a(*l), 'main.lookout'))
    return s

# my name is Guybrush Threepwood
def lookout_4(args):
    s = Script()
    s.add(Say(_a('imguy', 17), 'player'))
    s.add(Say(_a(18, 19, 20, 21), 'main.lookout'))
    scumm.gl.talked_to_lookout = 1
    return s
