from . import shared as a

import scumm.actions
import example
import entity
from script import Script
#import scripts.actions as aa

import actions
import status
import monkey
import vars


def gl(id):
    return monkey.engine.read('$dialogues/fettuccini/' + str(id))

def give_pot_alfredo(item, id):
    s = a.Scripts.walk('alfredo')
    s.add_action(a.custom_actions.disable_controls)
    s.add_action(actions.Animate(tag='player', anim='circus_cutscene_1', sync=True))
    s.add_action(scumm.actions.Say(tag='bill', font='monkey', lines=[gl(82)]))
    s.add_action(actions.Animate(tag='player', anim='circus_cutscene_1', fwd=False, sync=True))
    s.add_action(actions.Animate(tag='player', anim='idle_s'))
    s.add_action(scumm.actions.Say(tag='alfredo', font='monkey', lines=[gl(83)]))
    s.add_action(scumm.actions.Say(tag='bill', font='monkey', lines=[gl(84)]), id=1)
    s.add_action(scumm.actions.Walk(tag='alfredo', pos=(333, 1)), after=[1], id=2)
    s.add_action(scumm.actions.Walk(tag='bill', pos=(296, 24)), after=[1], id=3)
    s.add_action(scumm.actions.Walk(tag='player', pos=(250, 24)), after=[1], id=4)
    s.add_action(actions.Scroll(pos=(48, 0), relative=True, speed=50, cam ='maincam'), after=[1])
    s.add_action(scumm.actions.Turn(tag='alfredo', dir='n'), after=[2], id=5)
    s.add_action(scumm.actions.Turn(tag='bill', dir='w'), after=[3], id=6)
    s.add_action(scumm.actions.Turn(tag='player', dir='s'), after=[4], id=7)
    s.add_action(scumm.actions.Say(tag='alfredo', font='monkey', lines=[gl(85)]), after=[5,6,7])
    s.add_action(scumm.actions.Say(tag='bill', font='monkey', lines=[gl(86)]))
    s.add_action(scumm.actions.Say(tag='alfredo', font='monkey', lines=[gl(87)]))
    s.add_action(scumm.actions.Walk(tag='player', pos=(264, 23)))
    s.add_action(scumm.actions.Turn(tag='player', dir='e'))
    s.add_action(scumm.actions.Say(tag='player', font='monkey', lines=[gl(88)]))
    s.add_action(scumm.actions.Walk(tag='player', pos=(250, 24)))
    s.add_action(scumm.actions.Turn(tag='player', dir='s'))
    s.add_action(actions.Animate(tag='player', anim='circus_cutscene_2', sync=True))
    s.add_action(actions.SetActive(tag='player',value=False))
    s.add_action(actions.Delay(sec=1), id=10)
    s.add_action(a.custom_actions.add_item('circus_explosion'), after=[10])
    s.add_action(a.custom_actions.add_item('flying_guybrush'), after=[10])
    s.add_action(actions.Animate(tag='circus_explosion', anim='default', sync=True), id=11)
    s.add_action(actions.Animate(tag='flying_guybrush', anim='default', sync=True), id=12)
    s.add_action(a.custom_actions.remove_item('circus_explosion'), after=[11])
    s.add_action(scumm.actions.Say(tag='alfredo', font='monkey', lines=[gl(89)]), after=[12])
    s.add_action(scumm.actions.Say(tag='bill', font='monkey', lines=[gl(90)]), id=13)
    s.add_action(scumm.actions.Walk(tag='alfredo', pos=(87, 29)), after=[13])
    s.add_action(scumm.actions.Turn(tag='alfredo', dir='e'))
    s.add_action(scumm.actions.Walk(tag='bill', pos=(126, 29)), after=[13])
    s.add_action(scumm.actions.Turn(tag='bill', dir='w'))
    s.add_action(scumm.actions.Say(tag='alfredo', font='monkey', lines=[gl(91)]))
    s.add_action(scumm.actions.Say(tag='bill', font='monkey', lines=[gl(92)]))
    s.add_action(a.custom_actions.add_to_inventory('pieces_of_eight', 478))
    #{type = scumm.action.remove_from_inventory, args = {id = "kitchen.pot"}},
    s.add_action(a.custom_actions.enable_controls)
    s.add_action(scumm.actions.StartDialogue('fettuccini', 'm3'))
    example.play(s)

def cane():
    print ('CAZZZIMMM')
    example.get('alfredo').setAnim('idle_e')
    example.get('bill').setAnim('idle_e')

def gsay(id):
    def f(n):
        m = n if isinstance(n, tuple) else [n]
        a = [monkey.engine.read('$dialogues/fettuccini/' + str(x)) for x in m]
        return scumm.actions.Say(tag=id, font='monkey', lines=a)
    return f

psay = gsay('player')

def asay(n):
    m = n if isinstance(n, tuple) else [n]
    a = [monkey.engine.read('$dialogues/fettuccini/' + str(x)) for x in m]
    return scumm.actions.Say(tag='alfredo', font='monkey', lines=a)

def bsay(n):
    m = n if isinstance(n, tuple) else [n]
    a = [monkey.engine.read('$dialogues/fettuccini/' + str(x)) for x in m]
    return scumm.actions.Say(tag='bill', font='monkey', lines=a)


def fettuccini_exit(s, *args):
    s.add_action(scumm.actions.HideDialogue())
    s.add_action(psay(63))
    a.goto_room(s, 'clearing', status.pos.circus_tent, 's')
    example.play(s)



def pane(s, *args):
    rv = monkey.engine.read
    print ('STOCAZZIO!')
    s.add_action(actions.KillScript(s='_fettuccini'))
    s.add_action(scumm.actions.Say(tag='player', font='monkey', lines=[rv('$dialogues/fettuccini/' + str(args[0]))]), id=1)
    s.add_action(scumm.actions.Walk(tag='alfredo', pos=(148, 7)), after=[1])
    s.add_action(scumm.actions.Turn(tag='alfredo', dir='e'))
    s.add_action(scumm.actions.Walk(tag='bill', pos=(218, 7)), after=[1])
    s.add_action(scumm.actions.Turn(tag='bill', dir='w'))
    s.add_action(scumm.actions.Turn(tag='player', dir='s'))

    if status.circus_status == 0:
        s.add_action(asay(34))
        # s.add_action(bsay(35))
        # s.add_action(asay(36))
        # s.add_action(bsay(37))
        # s.add_action(asay(38))
        # s.add_action(bsay(39))
        # s.add_action(asay(40))
        # s.add_action(bsay(41))
        # s.add_action(asay(42))
        # s.add_action(bsay(43))
        # s.add_action(asay(44))
        # s.add_action(bsay(45))
        # s.add_action(asay(46))
        # s.add_action(bsay(47))
        # s.add_action(asay(48))
        # s.add_action(bsay(49))
        # s.add_action(asay(50))
        # s.add_action(bsay(51))
        # s.add_action(asay(52))
        # s.add_action(bsay(53))
        # s.add_action(asay((54, 55)))
        # s.add_action(bsay(56))
        # s.add_action(asay(57))
        # s.add_action(bsay(58))
        # s.add_action(asay(59))
        s.add_action(bsay(60))
        status.circus_status = 1
    elif status.circus_status == 1:
        s.add_action(asay(67))
        s.add_action(bsay(68))
    elif status.circus_status == 2:
        s.add_action(asay(67))
        s.add_action(bsay(68))
        s.add_action(asay(70))


    #s.add_action(scumm.actions.StartDialogue('fettuccini', 'm1'))
    #f(2, {34}), f(3, {35}), f(2, {36}), f(3, {37}), f(2, {38}), f(3, {39}), f(2, {40}), f(3, {41}), f(2, {42}), f(3, {
    #    43}), f(2, {44}), f(3, {45}), f(2, {46}), f(3, {47}), f(2, {48}),
    #f(3, {49}), f(2, {50}), f(3, {51}), f(2, {52}), f(3, {53}), f(2, {54, 55}), f(3, {56}), f(2, {57}), f(3, {58}), f(2,
                                                                                                                      #{
                                                                                                                      #    59}),
    #f(3, {60}),
    #{type = action.set_variable, args = {var = "circus_knows_trick", value = true}}
    #example.play(s)

def append_script(s):
    rv = monkey.engine.read
    s.add_action(id = 100, action=asay(10))
    s.add_action(bsay(11))
    s.add_action(asay(12))
    s.add_action(bsay(13))
    s.add_action(asay(14))
    s.add_action(bsay(15))
    s.add_action(asay(16))
    s.add_action(bsay(17))
    s.add_action(asay(18))
    s.add_action(bsay(19))
    s.add_action(asay(20))
    s.add_action(bsay(21))
    s.add_action(asay(22))
    s.add_action(bsay(23))
    s.add_action(asay(5))
    s.add_action(bsay(5))
    s.add_action(asay(24))
    s.add_action(bsay(25))
    s.add_action(asay(5))
    s.add_action(bsay(5))
    s.add_action(asay(26))
    s.add_action(bsay(27))
    s.add_action(asay(28))
    s.add_action(bsay((22, 23)))
    s.add_action(asay(5))
    s.add_action(bsay(5))
    s.add_action(asay(5))
    s.add_action(bsay(5))

def init_circus():
    example.get('player').follow(False)
    s = Script(uid='_fettuccini')
    s.on_kill =cane
    rv = monkey.engine.read
    s.add_action(actions.Scroll(pos=(0, 72), cam='maincam', speed=0, relative=False))
    s.add_action(id=1, action=actions.CallFunc(f=a.Callbacks.enable_controls(False)))
    s.add_action(scumm.actions.Walk(tag='player', pos=(178, 9)), after=[1])
    # TODO add after debug
    # if status.circus_status == 0:
    #     s.add_action(asay(1), after=[1])
    #     s.add_action(bsay(2))
    #     s.add_action(asay(3))
    #     s.add_action(bsay(4))
    #     s.add_action(asay(5))
    #     s.add_action(bsay(5))
    #     s.add_action(asay(6))
    #     s.add_action(bsay(7))
    #     s.add_action(asay(8))
    #     s.add_action(bsay(9))
    s.add_action(action=actions.CallFunc(f=a.Callbacks.enable_controls(True)))
    s.add_action(scumm.actions.StartDialogue(dialogue_id='fettuccini'))
    append_script(s)
    s.set_loop(100)
    # --            action.disable_controls
    # {id = 1},
    # --            action.walkto
    # {id = 2, actor = "guybrush", pos = {178, 9}},
    # --            action.say
    # {id = 3, after = {1}, actor = "circus.purpleclown", lines = {d[1]}},
    # --            action.say
    # {id = 4, actor = "circus.greenclown", lines = {d[2]}},
    # --            action.say
    # {id = 5, actor = "circus.purpleclown", lines = {d[3]}},
    # --            action.say
    # {id = 6, actor = "circus.greenclown", lines = {d[4]}},
    # --            action.say
    # {id = 7, actor = "circus.purpleclown", lines = {d[5]}},
    # --            action.say
    # {id = 8, actor = "circus.greenclown", lines = {d[5]}},
    # --            action.say
    # {id = 9, actor = "circus.purpleclown", lines = {d[6]}},
    # --            action.say
    # {id = 10, actor = "circus.greenclown", lines = {d[7]}},
    # --            action.say
    # {id = 11, actor = "circus.purpleclown", lines = {d[8]}},
    # --            action.say
    # {id = 12, actor = "circus.greenclown", lines = {d[9]}},
    # --            action.start_dialogue
    # {id = 13, dialogue = "fettuccini"},
    example.play(s)