import script
import scumm.actions
import example

def walkto(x, y):
    s = script.Script(uid='_main')
    s.add_action(scumm.actions.Walk(pos=[x, y], tag='player'))
    example.play(s)