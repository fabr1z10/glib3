import script
import scumm.actions
import example
import actions
import random

def random_move(id):
    def f():
        s = script.Script()
        x = random.randint(0, 316)
        y = random.randint(0, 42)
        print ('CALLED WITH ' + str(x) + ' ' + str(y))
        s.add_action(scumm.actions.Walk(id=id, pos=[x, y]))
        return s
    return f


def pane(id):
    s = script.Script(loop=0)
    s.add_action(actions.RunScript(func=random_move(id)), id=0)
    example.play(s)
