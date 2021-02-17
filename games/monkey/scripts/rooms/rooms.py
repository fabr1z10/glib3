from lib_py.script import Script
from lib_py.scumm.actions import Walk, Turn, StartDialogue
from lib_py.scumm.builder.item import buildItem
import lib_py.engine as eng
from lib_py.actions import Delay, DelayRandom, Animate, Msg, RunScript, AddEntity,RemoveEntity
from scripts.builder import make_dialogue_mancomb
from scripts.actions import toggleDoor


import example

def onstart_lookout():
    # guybrush walk to center screen
    s = Script()
    s.addAction (Walk(pos=[240,30], tag='player'))
    return s

def run_background_script(actor, a, b, c, d):
    s = Script(loop = 0)
    s.addAction (DelayRandom(min=a, max=b))
    s.addAction (Animate(tag=actor, anim='idle_2', fwd = True, sync = True))
    s.addAction (DelayRandom(min=c, max=d))
    s.addAction (Animate(tag=actor, anim='idle_2', fwd = False, sync = True))
    s.addAction (Animate(tag=actor, anim='idle_1', fwd = True, sync = True))
    example.play(s)

def onstart_scummbar():
    run_background_script('scummbar_pirate1', 1, 4, 1, 4)
    run_background_script('scummbar_pirate2', 1, 4, 1, 4)
    run_background_script('scummbar_mancomb', 1, 4, 0, 0)    
    run_background_script("scummbar_pirate3", 1, 4, 0.5, 0.5)
    run_background_script("scummbar_pirate4", 1, 4, 0, 0)
    run_background_script("scummbar_pirate5", 1, 4, 1, 2)
    run_background_script("scummbar_pirate7", 1, 4, 1, 2)
    run_background_script("scummbar_pirate8", 1, 4, 0, 0)
    run_background_script("scummbar_pirate9", 1, 4, 0, 0)
    run_background_script("scummbar_estevan", 1, 4, 0, 0)
    run_background_script("scummbar_loom", 1, 4, 0, 0)
    # play the cook script
    if eng.previous_room != 'kitchen':
        s = Script (id = '_cook', loop= 0)
        s.addAction (Delay (sec = 10))
        s.addAction (RunScript ( toggleDoor('scummbar_door_kitchen', True)() ))
        s.addAction (AddEntity (buildItem (id = 'cook'), 'walkarea'))
        s.addAction (Walk (tag ='cook', pos = [125, 17]))
        s.addAction (Turn (tag = 'cook', dir='n'))
        s.addAction (Delay (sec = 10))
        s.addAction (Walk (tag = 'cook', pos = [589, 14]))
        s.addAction (RemoveEntity (tag='cook'))
        s.addAction (RunScript ( toggleDoor('scummbar_door_kitchen', False)() ))
        example.play(s)


def onstart_mancomb():
    print ('ciao')
    s = make_dialogue_mancomb ( [ ['o', 1, 2]])()
    s.addAction (StartDialogue ('mancomb'))
    example.play(s)
    pass

