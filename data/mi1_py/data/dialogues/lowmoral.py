from lib_py.scumm.dialogue import Dialogue, DialogueNode
from lib_py.script import Script
from lib_py.actions import Animate, Delay
from lib_py.scumm.scumm import State
from lib_py.scumm.scripts import changeRoom
from lib_py.scumm.functions import d3, d4
import lib_py.engine as engine
import mi1_py.variables as var
from lib_py.scumm.actions import Say
import mi1_py.scripts as scripts

import example

sl = engine.data['strings']['dialogues']['lowmoral']

d = Dialogue('lowmoral', sl)

def start(self):
    return

def end(self):
    s = Script()
    s.addAction (Animate(tag='lmf1', anim='idle_e'))
    s.addAction (Animate(tag='lmf2', anim='idle_e'))
    s.addAction (Animate(tag='lmf3', anim='idle_e'))
    example.play(s)

def keg():
    s = Script()
    s.addAction (Say([sl[48]], tag='player'), 0)
    s.addAction (Say([sl[53]], tag='lmf3'), 1, after = [0])
    s.addAction (Say([sl[52]], tag='lmf1'), 2, after = [0])
    s.addAction (Animate ('idle_s', tag='lmf2'), after = [1,2])
    s.addAction (Animate ('idle_s', tag='lmf3'), after = [1,2])
    s.addAction (Animate ('idle_n', tag='lmf1'), after = [1,2])
    s.addAction (Delay (1), 3)
    s.addAction (Say([sl[52]], tag='lmf3'), 4, after = [3])
    s.addAction (Say([sl[53]], tag='lmf1'), 5, after = [3])
    s.addAction (Animate ('idle_s', tag='lmf2'), after = [4, 5])
    s.addAction (Animate ('idle_s', tag='lmf3'), after = [4, 5])
    s.addAction (Animate ('idle_n', tag='lmf1'), after = [4, 5])
    s.addAction (Delay (1), 3)
    s.addAction (Animate ('idle_e', tag='lmf2'))
    s.addAction (Animate ('idle_e', tag='lmf1'))
    s.addAction (Say([sl[54], sl[55]], tag='lmf3'))
    return s

d.addStartScript(start)
d.addEndScript (end)

# nice rat!
d.add (1, d3(sl, ['player', ('a', 1)], ['lmf1', 'a:talk_e', ('_', 6), 'a:idle_e_1']), 1, True, [1,49])
d.add (2, d3(sl, 
    ['player', ('a', 2)], 
    ['village2.rat', ('_', 34, 35)],
    ['lmf1', 'a:talk_e', ('_', 36, 37), 'a:idle_e_1'],
    ['lmf3', ('a', 38)]), -1, True, [2])
# are you pirates?
d.add (4, d3(sl,
    ['player', ('a', 4)],
    ['lmf1', 'a:idle_n'],
    ['lmf2', 'a:idle_s'],
    ['lmf3', 'a:idle_s'],
    ['lmf1', 'd:2', 'a:idle_e_1'],
    ['lmf2', 'a:talk_e'],
    ['lmf3', 'a:talk_e', ('_', 43, 44), 'a:idle_e', 'd:0.5', 'a:talk_e', ('_', 45, 46), 'a:idle_e', 'd:0.5'],
    ['lmf3', 'A:punch'],
    ['lmf2', 'a:hit', 'd:0.2', 'a:idle_e'],
    ['lmf3', 'A:idle_e'],
    ['lmf1', 'a:talk_e', ('_', 47), 'a:idle_e']), 4, True)
d.add (5, d3(sl,
    ['player', ('a', 5)]), -1, True)


# after are you pirates?
d.add (48, keg, -1, True, parent=[4])
d.add (49, d3(sl, 
    ['player', ('a', 49)], 
    ['lmf1', 'a:talk_e', ('_', 6), 'a:idle_e']), 1, True, parent=[4])
d.add (50, d3(sl, 
    ['player', ('a', 50)],
    ), -1, True, parent=[4])
d.add (51, d3(sl, 
    ['player', ('a', 51)],
    ['lmf1', 'a:idle_n'],
    ['lmf3', ('a', 58), 'a:idle_s'],
    ['lmf2', 'a:idle_s'],
    ['lmf1', 'a:talk_e', ('_', 59), 'a:idle_n'],
    ['lmf3', ('a', 60), 'a:idle_s'],
    ['lmf1', 'a:talk_e', ('_', 61, 62), 'a:idle_n'],
    ['lmf3', ('a', 63), 'd:1'],
    ['lmf1', 'a:talk_e', ('_', 64, 65)]), -1, True, parent=[4])

# after nice rat
d.add (7, d3(sl, 
    ['player', ('a', 7)], 
    ['lmf1', 'a:talk_e', ('_', 11), 'a:idle_e_1'], 
    ['lmf2', 'a:talk_e', ('_', 12), 'd:0.5'], 
    ['lmf1', 'a:idle_n', ('_', 13)],
    ['lmf3', 'A:punch'],
    ['lmf2', 'a:hit', 'd:0.2', 'a:idle_e'],
    ['lmf1', 'a:talk_e', ('_', 14), 'a:idle_e'],
    ['lmf3', 'a:talk_s', ('_', 15, 16), 'a:idle_e']), 7, True, parent=[1])

# after yes I love rats
d.add (17, d3(sl, 
    ['player', ('a', 17)],
    ['lmf3', 'a:talk_e', ('_', 21, 22, 23), 'a:idle_e'],
    ['lmf1', 'a:talk_e', ('_', 24), 'a_idle_e']), 0, True, parent=[7])
d.add (18, d3(sl, 
    ['player', ('a', 18)],
    ['lmf3', 'a:talk_e', ('_', 41, 22, 23), 'a:idle_e'],
    ['lmf1', 'a:talk_e', ('_', 24), 'a_idle_e']), 0, True, parent=[7])
d.add (19, d3(sl, 
    ['player', ('a', 19)],
    ['lmf3', 'a:talk_e', ('_', 41, 22, 23), 'a:idle_e'],
    ['lmf1', 'a:talk_e', ('_', 24), 'a_idle_e']), 0, True, parent=[7])




State.addDialogue (d)
