import mopy.scumm.scriptlib as sl
import mopy.scumm.actionlib as al
import mopy.actions as actions
from mopy.script import Script
import mopy
import example



def on_init_mancomb():
    s = Script()
    s.add_action(al.start_dialogue('mancomb', False))
    example.play(s)