from . import shared as a

import scumm.actions
import example
import entity
from script import Script
import actions
import status
import monkey
import vars




lookat_scummbar_fireplace = a.Actions.say(['$lines/3'])


def cook_init_helper(s, id):
    s.add_action(actions.Delay(sec=5), id=id)
    s.add_action(actions.CallFunc(f=a.openDoor('scummbar_kitchen_door', 'open')))
    s.add_action(actions.CallFunc(f=a.Callbacks.add_item('cook', {'pos': '@pos/scummbar_kitchen_door', 'parent': 'walkarea_0'})))
    s.add_action(scumm.actions.Walk(tag='cook', pos=(115, 18)))
    s.add_action(scumm.actions.Turn(tag='cook', dir='n'))
    s.add_action(actions.Delay(sec=2))
    s.add_action(scumm.actions.Walk(tag='cook', pos=status.pos.scummbar_kitchen_door))
    s.add_action(actions.RemoveEntity(tag='cook'))
    s.add_action(actions.Animate(tag='scummbar_kitchen_door', anim='closed'))

def anim_helper(tag):
    s1 = Script(loop=0, uid='_' + tag)
    s1.add_action(actions.DelayRandom(1.0, 5.0))
    s1.add_action(actions.Animate(tag=tag, anim='idle_2', sync=True))
    s1.add_action(actions.Animate(tag=tag, anim='idle_1'))
    example.play(s1)

def init_scummbar():

    if monkey.engine.previous_room == 'kitchen':
        s = Script(loop=100, uid='cook')
        s.add_action(actions.CallFunc(f=a.Callbacks.add_item('cook', {'pos': (115, 18), 'parent': 'walkarea_0'})))
        s.add_action(scumm.actions.Turn(tag='cook', dir='n'))
        s.add_action(actions.Delay(sec=2))
        s.add_action(scumm.actions.Walk(tag='cook', pos = status.pos.scummbar_kitchen_door))
        s.add_action(actions.RemoveEntity(tag='cook'))
        s.add_action(actions.Animate(tag='scummbar_kitchen_door', anim='closed'))
        cook_init_helper(s, 100)
        example.play(s)
    else:
        s = Script(loop=0, uid='cook')
        cook_init_helper(s, 0)
        example.play(s)
    
    anim_helper('scummbar_mancomb')
    anim_helper('scummbar_estevan')


close_scummbar_kitchen_door = a.Actions.close_door()

def cook_upset(aa, ba, open_door):
    # cook is in scummbar
    if open_door:
        s = a.Scripts.set_door('open')(aa, ba)
    else:
        s = a.Scripts.walk('scummbar_kitchen_door')
    rv = monkey.engine.read
    cook: example.Wrap1 = example.get('cook')

    if cook.valid and cook.x > 320:
        s.add_action(actions.SuspendScript(s='cook'))
        s.add_action(scumm.actions.Turn(tag='cook', dir='e'))
        s.add_action(scumm.actions.Say(lines=[rv('$lines/32'), rv('$lines/33')], tag='cook', font='monkey'))
        s.add_action(scumm.actions.Turn(tag='cook', dir='w'))
        s.add_action(actions.Animate(tag='cook', anim='walk_e'))
        s.add_action(actions.ResumeScript(s='cook'))
    example.play(s)


def walkto_scummbar_kitchen_door(aa, ba):
    if example.get('scummbar_kitchen_door').anim == 'closed':
        a.Actions.walkto()(aa, ba)
    else:
        cook: example.Wrap1 = example.get('cook')
        if cook.valid and cook.x > 320:
            cook_upset(aa, ba, False)
        else:
            a.Actions.walk_door('kitchen', status.pos.kitchen_door, 'e')(aa, ba)

def open_scummbar_kitchen_door(aa, ba):
    cook: example.Wrap1 = example.get('cook')
    if cook.valid:
        print('Cook is in kitchen @ ' + str(cook.x))
    else:
        print('Cook is not in kitchen')

    if not cook.valid:
        s = a.Scripts.walk('scummbar_kitchen_door')
        s.add_action(actions.Animate(tag='scummbar_kitchen_door', anim='open'))
        s.add_action(actions.Msg(text=monkey.engine.read('$lines/32'), font='monkey', pos=(609, 78), color=status.colors.cook_text_color))
        s.add_action(actions.Msg(text=monkey.engine.read('$lines/34'), font='monkey', pos=(609, 78), color=status.colors.cook_text_color))
        s.add_action(actions.Animate(tag='scummbar_kitchen_door', anim='closed'))
        example.play(s)
    else:
        cook_upset(aa, ba, True)





def talkto_important_looking_pirates(aa, ba):
    s = a.Scripts.walk('important_looking_pirates')
    m = '$dialogues/important_looking_pirates/'
    if status.pirates_know_guybrush == 0:
        l = [monkey.engine.read(m+'1')]
    else:
        l = [monkey.engine.read(m + '40'), monkey.engine.read(m + '41')]
    s.add_action(scumm.actions.EnableUI(False))
    s.add_action(scumm.actions.Say(tag='important_looking_pirate_2', lines=l, font='monkey'))
    s.add_action(scumm.actions.StartDialogue('ilp'))
    example.play(s)




talkto_scummbar_mancomb = a.Actions.change_room('mancomb')
talkto_scummbar_estevan = a.Actions.change_room('estevan')
talkto_scummbar_loom = a.Actions.change_room('loom')

lookat_scummbar_mancomb = talkto_scummbar_mancomb
lookat_scummbar_estevan = talkto_scummbar_estevan
lookat_scummbar_loom = talkto_scummbar_loom

def pappo():
    s = Script()
    s.add_action(scumm.actions.EnableUI(False))
    l = ['$dialogues/mancomb/1', '$dialogues/mancomb/2']
    lines = [monkey.engine.read(x) for x in l]
    s.add_action(scumm.actions.Say(tag='mancomb', lines=lines, animate=False, font='monkey'))
    s.add_action(scumm.actions.StartDialogue('mancomb'))
    example.play(s)


def on_enter_estevan():
    s = Script()
    s.add_action(scumm.actions.EnableUI(False))
    l = ['$dialogues/estevan/1']
    lines = [monkey.engine.read(x) for x in l]
    s.add_action(scumm.actions.Say(tag='estevan', lines=lines, animate=False, font='monkey'))
    s.add_action(scumm.actions.StartDialogue('estevan'))
    example.play(s)

def on_enter_loom():
    s = Script()
    s.add_action(scumm.actions.EnableUI(False))
    l = ['$dialogues/loom/1']
    lines = [monkey.engine.read(x) for x in l]
    s.add_action(scumm.actions.Say(tag='loom', lines=lines, animate=False, font='monkey'))
    s.add_action(scumm.actions.StartDialogue('loom'))
    example.play(s)

def on_exit_mancomb():
    s = Script()
    s.add_action(actions.ChangeRoom('scummbar'))
    example.play(s)


def on_exit_estevan():
    a.Actions.goto_room('scummbar', status.pos.estevan, 's')(None, None)

def on_exit_loom():
    a.Actions.goto_room('scummbar', status.pos.loom, 'n')(None, None)