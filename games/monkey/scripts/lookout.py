from . import shared as a

import mopy.scumm as scumm
import example
import mopy.entity as entity
from mopy.script import Script
import mopy.actions as actions
import data.vars as vars
import data
import mopy.monkey as monkey
import random



walkto_lookout_stairs = a.Actions.goto_room('village1', vars.pos.village_cliffside, 'e')
walkto_lookout_path = a.Actions.goto_room('meleemap', vars.pos.melee_village, 'n')
talkto_lookout = a.Actions.start_dialogue('lookout')

def gl(id):
    return monkey.engine.read('$dialogues/lookout/' + str(id))

def lookout_start_dialogue(s, *args):
    s.add_action(scumm.actions.Say(tag='player', font='monkey', lines=[gl(args[0])]))
    s.add_action(scumm.actions.Turn(tag='lookout',dir='s'))
    lines = [gl(5), gl(43) + gl(53 + random.randint(0, 1))] if vars.talked_to_lookout == 1 else [gl(5), gl(6), gl(7), gl(8), gl(9)]
    s.add_action(scumm.actions.Say(tag='lookout', font='monkey', lines=lines))

def on_exit_lookout():
    s = Script()
    s.add_action(scumm.actions.Turn(tag='lookout', dir='w'))
    s.add_action(scumm.actions.ExitDialogue())
    data.dialogues['lookout']['lines'][6]['active'] = True
    example.play(s)


def on_start_lookout():
    a.chase_storekeeper_func('lookout')


def on_load_lookout():
    a.storekeeper_script(vars.pos.lookout_path, 'meleemap', (48, 105), 'n')