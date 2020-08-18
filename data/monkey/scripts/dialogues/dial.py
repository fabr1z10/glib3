from lib_py.script import Script
from lib_py.scumm.actions import Say, StartDialogue, Turn
from lib_py.actions import ChangeRoom, Animate
from lib_py.scumm.helper import gt, gd, gv, sv
from lib_py.scumm.scumm import Data, State
from lib_py.engine import data
from monkey.scripts.builder import make_dialogue, make_dialogue_mancomb, goto

slo = data['strings']['dialogues']['lookout']

def lookout_intro(line):
    def f():
        lines = []
        if not gv('@talked_to_lookout'):
            sv('@talked_to_lookout', True)
            lines = [slo[5], slo[6], slo[7], slo[8], slo[9]]
        else:
            lines = [slo[5], slo[43]]
        s = Script()
        s.addAction (Say(lines=[slo[line]], tag='player', font='monkey'))
        s.addAction (Turn (dir='s', tag='lookout'))
        s.addAction (Say(lines=lines, tag='lookout', font='monkey'))
        return s
    return f

def onstart_lookout():
    Data.dialogues['lookout'].nodes['overhere'].status=1
    return None

def onend_lookout():
    s = Script()
    s.addAction (Turn(dir='w', tag='lookout'))
    return s

lookout_intro1 = lookout_intro('intro1')
lookout_intro2 = lookout_intro('intro2')
lookout_intro3 = lookout_intro('intro3')
lookout_intro4 = lookout_intro('intro4')
lookout_imguy = make_dialogue ( slo, [
    ['player', 'imguy', 17],
    ['lookout', 18, 19, 20, 21]])
lookout_actuallyimguy = make_dialogue ( slo, [
    ['player', 'actuallyimguy', 17],
    ['lookout', 18, 19, 20, 21]])
lookout_fortune = make_dialogue ( slo, [
    ['player', 'fortune'],
    ['lookout', 42]])
lookout_whoru = make_dialogue ( slo, [
    ['player', 'whoru'],
    ['lookout', 30, 31, 32, 33]])
lookout_whyguvworried = make_dialogue ( slo, [
    ['player', 'whyguvworried'],
    ['lookout', 35, 36, 37]])
lookout_bat = make_dialogue ( slo, [
    ['player', 'bat'],
    ['lookout', 39, 40]])

def lookout_overhere():
    s = Script()
    s.addAction (Say(lines = [ slo['overhere'] ], tag='player'))
    s.addAction (Say(lines = [ slo[15] ], tag='lookout'))
    s.addAction (Turn (tag='lookout', dir='e'))
    s.addAction (Say(lines = [ slo[16] ], tag='lookout'))
    return s

def lookout_squinky():
    print ('AAAAAAAAA')
    if Data.dialogues['lookout'].nodes['imguy'].said:
        print ('B')
        return make_dialogue (slo, [
            [ 'player', 'squinky'],
            [ 'lookout', 27 ],
            [ 'player', 28],
            [ 'lookout', 29 ]])()
    else:
        print ('C')
        return make_dialogue (slo, [
            [ 'player', 'squinky'],
            [ 'lookout', 41 ]])()


def onend_mancomb():
    return goto('scummbar', '@scummbar_mancomb', 'n')()

mancomb_imguy = make_dialogue_mancomb([
    ['player', 'imguy'],
    ['o', 9, 10, 11]
])

mancomb_rupirate = make_dialogue_mancomb([
    ['player', 'rupirate'],
    ['o', 29, 30, 24, 25, 26 ]
])

mancomb_insulted = make_dialogue_mancomb([
    ['player', 'insulted'],
    ['o', 47, 48 ]
])
mancomb_yourname2 = make_dialogue_mancomb([
    ['player', 'yourname2'],
    ['o', 17, 18 ]
])
mancomb_ilikeguy = make_dialogue_mancomb([
    ['player', 'ilikeguy'],
    ['o', 16 ]
])