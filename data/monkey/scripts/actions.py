from lib_py.script import Script
from lib_py.scumm.actions import Say


def walkto_lookout_stairs():
    s = Script()
    s.addAction (Say (lines = ['ciao'], tag = 'player', font = 'monkey'))
    return s