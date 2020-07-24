from lib_py.script import Script
from lib_py.scumm.actions import Walk
import example

def onstart_lookout():
    # guybrush walk to center screen
    s = Script()
    s.addAction (Walk(pos=[240,30], tag='player'))
    return s