from lib_py.scumm.room import RoomDialogue
from lib_py.script import Script
import lib_py.scumm.entity as se
import lib_py.scumm.actions as sa
import lib_py.engine as engine
import example

st = engine.data['strings']
sl = st['dialogues']['mancomb']

def f():
    s = Script()
    s.addAction (sa.Say(lines = [sl[1], sl[2]], tag ='mancomb.mancomb'))
    s.addAction (sa.StartDialogue (dialogueId='mancomb'))
    example.play(s)


def builder():
    r = RoomDialogue(id='scummbar')
    r.add (se.BackgroundItem(image='gfx/mancomb.png', pos = [0,0,-1]), 'main')
    r.addItem (id = 'mancomb.mancomb')
    #r.addItem (id = 'guybrush.dialogue')
    r.init.append(f)
    return r

engine.addRoom (id = 'mancomb', f=builder)
