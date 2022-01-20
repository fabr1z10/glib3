### default actions
import mopy
import example
from mopy.script import Script
from mopy.actions import Walk, Turn, Say, Sayd
import mopy.scumm.scriptlib as sl
import mopy.scumm.actionlib as al
import mopy.scumm as scumm
import random


def _a(*args):
    return ['$dialogues/lookout/' + str(x) for x in args]

def _b(n):
    return mopy.monkey.engine.read('$dialogues/lookout/' + str(n))


def talkto_main_lookout(item_id, entity):
    return sl.walk_and_dialogue(item_id, 'lookout')

def on_exit_lookout():
    s = Script()
    s.add(Turn('w', 'main.lookout'))
    s.add(al.exit_dialogue())
    return s


def lookout_start_dialogue(args):
    s = Script()
    s.add(Say(_a(args[0]), 'player'))
    s.add_action(Turn('s', 'main.lookout'))
    l = [_b(5), (_b(43) + _b(53 + random.randint(0, 1)))] if scumm.gl.talked_to_lookout == 1 else [_b(5), _b(6), _b(7), _b(8), _b(9)]
    s.add(Sayd(l, 'main.lookout'))
    return s

# my name is Guybrush Threepwood
def lookout_4(args):
    s = Script()
    s.add(Say(_a('imguy', 17), 'player'))
    s.add(Say(_a(18, 19, 20, 21), 'main.lookout'))
    scumm.gl.talked_to_lookout = 1
    return s


def lookout_9(args):
    s = Script()
    s.add(Say(_a(22), 'player'))
    s.add(Say(_a(23, 24, 25, 26), 'main.lookout'))
    return s


def lookout_8(args):
    s = Script()
    s.add(Say(_a('fortune'), 'player'))
    s.add(Say(_a(42), 'main.lookout'))
    return s

def lookout_5(args):
    s = Script()
    s.add(Say(_a('squinky'), 'player'))
    if mopy.monkey.engine.data.dialogues['lookout']['lines'][4].get('clicked', 0) == 0:
        s.add(Say(_a(41), 'main.lookout'))
    else:
        s.add(Say(_a(27), 'main.lookout'))
    return s

