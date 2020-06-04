from lib_py.scumm.dialogue import Dialogue, DialogueNode
from lib_py.script import Script
from lib_py.actions import Animate
from lib_py.scumm.scumm import State
from lib_py.scumm.scripts import changeRoom
from lib_py.scumm.functions import d3
import lib_py.engine as engine
import mi1_py.variables as var
import lib_py.scumm.actions as sa
import mi1_py.scripts as scripts

import example

sl = engine.data['strings']['dialogues']['citizen']

d = Dialogue('citizen', sl)

def start(self):
    if var.knows_map == 1:
        self.current = 5


def end(self):
    s = Script()
    s.addAction (Animate(tag='citizen', anim='idle_s'))
    example.play(s)

d.addStartScript(start)
d.addEndScript (end)


d.add (2, d3(sl, ['player', ('a', 2)], ['citizen', 'a:talk_e', ('_', 6, 7)]), -1, True, [2, 3, 4, 5], [10,11])
d.add (3, d3(sl, ['player', ('a', 3)], ['citizen', 'a:talk_e', ('_', 6, 7)]), -1, True, [2, 3, 4, 5], [10,11])
d.add (4, d3(sl, ['player', ('a', 4)], ['citizen', 'a:talk_e', ('_', 16, 6, 7)]), -1, True, [2,3,5 ])
d.add (5, scripts.citi1, 5, True, [2,3,4,5,10,11])

d.add (10, scripts.citi2(10), 5, False, [10, 11, 12])
d.add (11, scripts.citi3, 5, False, [10,11, 12])
d.add (12, scripts.citi2(12), 5, False, [10,11,12])

d.add (24, d3(sl, ['player', ('a', 24)], ['citizen', 'a:talk_e', ('_', 26)]), -1, True, parent=[5])
d.add (25, d3(sl, ['player', ('a', 25)], ['citizen', 'a:talk_e', ('_', 26)]), -1, True, parent=[5])
d.add (35, d3(sl, ['player', ('a', 25)], ['citizen', 'a:talk_e', ('_', 26)]), -1, lambda: State.has('pieces_of_eight', 100), parent=[5])



State.addDialogue (d)
