from lib_py.scumm.dialogue import Dialogue, DialogueNode
from lib_py.script import Script
from lib_py.scumm.scumm import State
from lib_py.scumm.scripts import changeRoom
from lib_py.scumm.functions import dialogueHelper1
import lib_py.engine as engine
import mi1_py.variables as var
import lib_py.scumm.actions as sa
import example

sl = engine.data['strings']['dialogues']['mancomb']

d = Dialogue('mancomb', sl)

characters = [
    ( (20,100), (255,255,255,255)),
    ( (240,100), (255,255,255,255))
]

def end(self):
    s =changeRoom(room = 'scummbar', pos = var.scummbar_mancomb_pos, dir='n')()
    example.play(s)

d.addEndScript (end)

d.add (3, dialogueHelper1(sl, characters, [1, 3], [0, 9, 10, 11]), 3, True)
d.add (4, dialogueHelper1(sl, characters, [1, 4], [0, 29, 30, 24, 25, 26]), 0, True, closeNodes=[4, 5], actNodes=[27])
d.add (5, dialogueHelper1(sl, characters, [1, 5], [0, 40, 41]), 5, True, closeNodes=[4, 5], actNodes=[27])
d.add (27, dialogueHelper1(sl, characters, [1, 27], [0, 31, 32, 33]), 27, False, closeNodes=[27])
d.add (6, dialogueHelper1(sl, characters, [1, 6], [0, 7]), -1, True)

# where's the guvnor
d.add (34, dialogueHelper1(sl, characters, [1, 34], [0,52,53 ]), 34, True, parent=[27])
d.add (35, dialogueHelper1(sl, characters, [1, 35], [0, 64, 65]), 0, True, parent=[27])
d.add (36, dialogueHelper1(sl, characters, [1, 36], [0, 37, 6, 7]), -1, True, parent=[27])

# why pirates not welcome?
d.add (54, dialogueHelper1(sl, characters, [1, 54], [0, 59, 60, 61, 62, 63 ]), 0, True, parent=[34])
d.add (55, dialogueHelper1(sl, characters, [1, 55], [0, 58, 59, 60, 61, 62, 63 ]), 0, True, parent=[34])
d.add (56, dialogueHelper1(sl, characters, [1, 56], [0, 6, 7]), -1, True, parent=[34])

# who's in charge
d.add (42, dialogueHelper1(sl, characters, [1, 42], [0, 24, 25, 26]), 0, True, parent=[5])
d.add (43, dialogueHelper1(sl, characters, [1, 43], [0, 31, 32, 33]), 27, True, closeNodes=[27], parent=[5])
d.add (44, dialogueHelper1(sl, characters, [1, 44], [0, 6, 7]), -1, True, parent=[5])

# my name is guybrush
d.add (12, dialogueHelper1(sl, characters, [1, 12], [0, 16]), 3, True, closeNodes=[12], parent=[3])
d.add (13, dialogueHelper1(sl, characters, [1, 13], [0, 17, 18]), 13, True, closeNodes=[13], parent=[3])
d.add (14, dialogueHelper1(sl, characters, [1, 14], [0, 45, 46, 18]), 13, True, parent=[3])
d.add (15, dialogueHelper1(sl, characters, [1, 15], [0, 47, 48]), -1, True, parent=[3])

d.add (19, dialogueHelper1(sl, characters, [1, 19], [0, 23, 24, 25, 26]), 0, True, parent=[13])
d.add (20, dialogueHelper1(sl, characters, [1, 20], [0, 28, 24, 25, 26]), 0, True, parent=[13])

State.addDialogue (d)
