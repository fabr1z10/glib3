from lib_py.script import Script
from lib_py.scumm.actions import Say, StartDialogue
from lib_py.actions import ChangeRoom, Animate
from lib_py.scumm.helper import gt, gd, gv, sv
from lib_py.scumm.scumm import Data, State

def say(lines, tag):
    def f():
        s = Script()
        l = [gt(line) for line in lines]
        s.addAction (Say(lines=l, tag=tag, font='monkey'))
        return s
    return f

def goto(room, pos, dir = None, node = 'walkarea' ):
    def f():
        s = Script()
        Data.putItem (State.player, room, gv(pos), node)
        if dir is not None:
            Data.items[State.player]['dir'] = dir
        s = Script()
        s.addAction (ChangeRoom(room = room))
        return s
    return f

def gotoDoor(doorId: str, room, pos, dir = None, node = 'walkarea' ):
    def f():
        a =gv(Data.items[doorId]['anim'])
        if gv(Data.items[doorId]['anim']) == 'open':
            return goto(room, pos, dir, node)()
    return f


def toggleDoor (itemId: str, open: bool):
    def f():
        s = Script()
        status = 'open' if open else 'closed'
        # set corresponding variables
        sv(Data.items[itemId]['anim'], status)
        s.addAction (Animate(anim = status, tag = itemId))
        return s
    return f

def openDialogue (dialogueId: str):
    def f():
        s = Script()
        s.addAction (StartDialogue(dialogueId))
        return s
    return f


open_ = say(['@defaultactions/1'], 'player')
look_ = say(['@defaultactions/4'], 'player')
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


