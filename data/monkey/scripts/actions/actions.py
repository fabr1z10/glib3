from lib_py.script import Script
from lib_py.scumm.actions import Say, StartDialogue, Turn, EnableControls, EnableBlock
from lib_py.actions import ChangeRoom, CallFunc, Animate, SuspendScript, ResumeScript, Msg, RunScript, AddEntity
from lib_py.scumm.helper import gt, gd, gv, sv
from lib_py.scumm.scumm import Data, State
#from scripts.builder import goto
from lib_py.engine import write, read, fetch
from lib_py.scumm.scripts import say, pickup, goto, gotoDoor
from lib_py.scumm.builder.item import buildItem

import example



def setvar (varname, value):
    def f():
        print(varname + ' setttt')
        write (varname, value)
    return f

def toggleDoor (itemId: str, open: bool):
    def f():
        print ('ciao'+itemId)
        s = Script()
        status = 'open' if open else 'closed'
        s.addAction (CallFunc (f = setvar(Data.items[itemId]['anim'], status)))
        # set corresponding variables
        #sv(Data.items[itemId]['anim'], status)
        print ('set to ' + status)
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
open_kitchen_door = toggleDoor ('kitchen_door', True)
close_kitchen_door = toggleDoor ('kitchen_door', False)
walkto_kitchen_door = gotoDoor ('kitchen_door', 'scummbar', '@&scummbar_kitchen', 'w')
look_meat = say(['@lines/35'], 'player')
look_pot = say(['@lines/36'], 'player')
look_fish = say(['@lines/37'], 'player')
pickup_meat = pickup('meat')
pickup_pot = pickup('pot')

def collide_with_kitchen_trap():
    print ('ciappo')
    s = Script()
    s.addAction (AddEntity (buildItem (id = 'seagull'), 'main'))
    s.addAction (Animate (anim='fly', tag='seagull', sync=True))
    s.addAction (Animate (anim='eat', tag='seagull'))
    example.play(s)

def open_scummbar_door_kitchen():
    c : example.Wrap1 = example.get('cook')
    if c.valid:
        return toggleDoor ('scummbar_door_kitchen', True)()
    else:
        s = Script()
        s.addAction ( SuspendScript ('_cook'))
        s.addAction ( EnableControls(False))
        s.addAction ( Animate (tag='scummbar_door_kitchen', anim='open'))
        s.addAction ( Msg (text = gt('@lines/34'), font = 'monkey', pos = [588,90,1], color = [85, 255, 255, 255] ))
        s.addAction ( Animate (tag='scummbar_door_kitchen', anim='closed'))
        s.addAction ( EnableControls(True))
        s.addAction ( ResumeScript ('_cook'))
        return s

close_scummbar_door_kitchen = toggleDoor ('scummbar_door_kitchen', False)

def walkto_scummbar_door_kitchen():
    a =  fetch (Data.items['scummbar_door_kitchen']['anim'])
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
            else:
                return goto ('kitchen', '@&kitchen_door', 'e')()
        else:
            return goto ('kitchen', '@&kitchen_door', 'e')()
    return None

def open_kitchen_door_pier():
    s = Script()
    s.addAction ( RunScript (toggleDoor('kitchen_door_pier', True)()))
    s.addAction ( EnableBlock ('walkarea', 0, False))
    return s

def close_kitchen_door_pier():
    s = Script()
    s.addAction ( RunScript (toggleDoor('kitchen_door_pier', False)()))
    s.addAction ( EnableBlock ('walkarea', 0, True))
    return s