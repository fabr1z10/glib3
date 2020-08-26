from lib_py.script import Script
from lib_py.scumm.actions import Say, StartDialogue, Turn
from lib_py.actions import ChangeRoom, CallFunc, Animate, SuspendScript, ResumeScript
from lib_py.scumm.helper import gt, gd, gv, sv
from lib_py.scumm.scumm import Data, State
from scripts.builder import goto


import example

def say(lines, tag):
    def f():
        s = Script()
        l = [gt(line) for line in lines]
        s.addAction (Say(lines=l, tag=tag, font='monkey'))
        return s
    return f



def gotoDoor(doorId: str, room, pos, dir = None, node = 'walkarea' ):
    def f():
        a =gv(Data.items[doorId]['anim'])
        if gv(Data.items[doorId]['anim']) == 'open':
            return goto(room, pos, dir, node)()
    return f

def setvar (varname, value):
    def f():
        sv (varname, value)
    return f

def toggleDoor (itemId: str, open: bool):
    def f():
        print ('ciao')
        s = Script()
        status = 'open' if open else 'closed'
        s.addAction (CallFunc (f = setvar(Data.items[itemId]['anim'], status)))
        # set corresponding variables
        #sv(Data.items[itemId]['anim'], status)
        #print ('set to ' + status)
        s.addAction (Animate(anim = status, tag = itemId))
        return s
    return f

def openDialogue (dialogueId: str):
    def f():
        s = Script()
        s.addAction (StartDialogue(dialogueId))
        return s
    return f

####################
# default scripts
####################
open_ = say(['@defaultactions/1'], 'player')
close_ = say(['@defaultactions/2'], 'player')
push_ = say(['@defaultactions/3'], 'player')
pull_ = say(['@defaultactions/3'], 'player')
look_ = say(['@defaultactions/4'], 'player')
pickup_ = say(['@defaultactions/5'], 'player')
talkto_ = say(['@defaultactions/2'], 'player')
turnon_ = say(['@defaultactions/2'], 'player')
turnoff_ = say(['@defaultactions/2'], 'player')
use_ = say(['@defaultactions/2'], 'player')
give_ = say(['@defaultactions/2'], 'player')

look_lookout = say(['@dialogues/lookout/50'], 'player')
talkto_lookout = openDialogue('lookout')
look_village1_poster = say(['@lines/1', '@lines/2'], 'player')
walkto_lookout_stairs = goto ('village1', '@village1_lookout', 'e')
walkto_lookout_path = goto ('meleemap', '@meleemap_lookout', 'n')
walkto_village1_cliffside = goto ('lookout', '@lookout_stairs', 'n')
walkto_village1_archway = goto ('village2', '@village2_village1', 's')
open_village1_door = toggleDoor ('village1_door', True)
close_village1_door = toggleDoor ('village1_door', False)
walkto_village1_door = gotoDoor ('village1_door', 'scummbar', '@scummbar_entrance', 'e')
open_scummbar_door_out = toggleDoor ('scummbar_door_out', True)
close_scummbar_door_out = toggleDoor ('scummbar_door_out', False)
walkto_scummbar_door_out = gotoDoor ('scummbar_door_out', 'village1', '@village1_door', 's')
walkto_village2_archway1 = goto ('village1', '@village1_village2', 'w')
walkto_village2_archway3 = goto ('village3', '@village3_village2', 'w')
walkto_village3_archway = goto ('village2', '@village2_village3', 's')
open_village2_door = toggleDoor ('village2_door', True)
close_village2_door = toggleDoor ('village2_door', False)
walkto_village2_door = gotoDoor ('village2_door', 'voodoolady', '@voodoolady_door', 'e')
look_scummbar_pirate1 = say (['@lines/5'], 'player')
talkto_scummbar_pirate1 = say (['@lines/5'], 'player')
talkto_scummbar_mancomb = goto('mancomb', None)
look_scummbar_fireplace = say (['@lines/3'], 'player')
look_scummbar_pirate4 = say (['@lines/6'], 'player')
talkto_scummbar_pirate4 = say (['@lines/6'], 'player')

def walkto_scummbar_door_kitchen():
    a = gv(Data.items['scummbar_door_kitchen']['anim'])
    print ('a = ' + str(a))
    if a == 'open':
        c : example.Wrap1 = example.get('cook')
        if c.valid:
            if c.x > 320:
                going_left = c.flipx 
                s = Script()
                s.addAction (SuspendScript ('_cook'))
                s.addAction ( Turn(tag='cook', dir='e'))
                s.addAction ( Say(lines= [gt('@lines/32'), gt('@lines/33')], tag='cook'))
                if going_left:
                    s.addAction ( Turn(tag='cook', dir='w'))
                s.addAction ( Animate (tag ='cook', anim='walk_e'))
                s.addAction (ResumeScript ('_cook'))
                return s
    return None