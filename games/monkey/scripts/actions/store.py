from . import shared as a

import scumm.actions
import example
import entity
from script import Script
import actions
import status
import monkey
import vars
import func
import random


open_store_door = a.Actions.open_door()
close_store_door = a.Actions.close_door()
pickup_sword = a.Actions.pickup()
pickup_shovel = a.Actions.pickup()
lookat_sword = a.Actions.say(['$lines/45'])
lookat_shovel = a.Actions.say(['$lines/46'])


def on_start_store():
    print('PIPPO!?')
    #func.set_item_pos('storekeeper', 'village3', (0,0))


def sh(l):
    rv = monkey.engine.read
    return [rv('$dialogues/storekeeper/' + str(x)) for x in l]


def walkto_store_door(aa, ba):
    if example.get(aa).anim == 'open' and (status.has_shovel_not_paid() or status.has_sword_not_paid()):
        s = a.Scripts.walk(aa)
        s.add_action(actions.SuspendScript(s='_storekeeper'))
        s.add_action(scumm.actions.Say(tag='storekeeper', font='monkey', lines=sh([33])))
        s.add_action(scumm.actions.Walk(tag='player', pos=(229, 7)))
        s.add_action(scumm.actions.Turn(tag='player', dir='e'))
        s.add_action(scumm.actions.StartDialogue(dialogue_id='storekeeper'))
        example.play(s)
    else:
        return a.Actions.walk_door('village3', status.pos.village_store_door, 's')(aa, ba)


def talkto_storekeeper(aa, ba):
    s = a.Scripts.walk('storekeeper')
    s.add_action(a.custom_actions.disable_controls)
    s.add_action(scumm.actions.Say(tag='storekeeper', font='monkey', lines=a.make_lines(['$dialogues/storekeeper/10'])))
    s.add_action(scumm.actions.StartDialogue(dialogue_id='storekeeper'))
    example.play(s)


def say_random():
    s = Script(uid='_storekeeper')
    s.add_action(scumm.actions.Say(tag='storekeeper', font='monkey', lines=a.make_lines(['$dialogues/storekeeper/' + str(random.randint(2, 9))])))
    s.add_action(actions.Delay(sec=5))
    s.add_action(actions.CallFunc(f=say_random))
    example.play(s)

def init_store():
    # only if storekeeper in store
    if example.get('storekeeper').valid:
        s = Script(uid='_storekeeper')
        s.add_action(scumm.actions.Say(tag='storekeeper', font='monkey', lines=a.make_lines(['$dialogues/storekeeper/1'])))
        s.add_action(actions.Delay(sec=5))
        s.add_action(actions.CallFunc(f=say_random))
        s.add_action(actions.CallFunc(f=say_random))
        example.play(s)

def pippolandia():
    s = Script()
    s.add_action(scumm.actions.Say(tag='player', font='monkey', lines=a.make_lines(['$dialogues/storekeeper/11'])))
    s.add_action(scumm.actions.Say(tag='storekeeper', font='monkey', lines=a.make_lines(['$dialogues/storekeeper/12'])))
    s.add_action(scumm.actions.ExitDialogue())
    s.add_action(actions.ResumeScript(s='_storekeeper'))
    example.play(s)

def on_entry_storekeeper():
    s = Script()
    s.add_action(actions.SuspendScript(s='_storekeeper'))
    if ('sword' in vars.inventory) or ('shovel' in vars.inventory):
        s.add_action(scumm.actions.InitDialogue('storekeeper'))
    else:
        s.add_action(scumm.actions.Say(tag='player', font='monkey', lines=a.make_lines(['$dialogues/storekeeper/11'])))
        s.add_action(scumm.actions.Say(tag='storekeeper', font='monkey', lines=a.make_lines(['$dialogues/storekeeper/12'])))
        s.add_action(scumm.actions.ExitDialogue())
        s.add_action(actions.ResumeScript(s='_storekeeper'))
    example.play(s)

def on_exit_storekeeper():
    s = Script()
    s.add_action(scumm.actions.ExitDialogue())
    # resume script unless storekeeper is away
    if vars.items['storekeeper']['room'] == 'store':
        s.add_action(actions.ResumeScript(s='_storekeeper'))
    example.play(s)





def ask_sword_price(s, *args):
    s.add_action(scumm.actions.Say(tag='player', font='monkey', lines=sh([18])))
    s.add_action(scumm.actions.Say(tag='storekeeper', font='monkey', lines=sh([20, 21] if status.knows_sword_price == 0 else [25, 26])))
    status.knows_sword_price = 1


def ask_shovel_price(s, *args):
    s.add_action(scumm.actions.Say(tag='player', font='monkey', lines=sh([args[0]])))
    s.add_action(scumm.actions.Say(tag='storekeeper', font='monkey', lines=sh([27, 28] if status.knows_shovel_price == 0 else [31, 32])))
    status.knows_shovel_price = 1


def replace_sword(s, *args):
    rv = monkey.engine.read
    s.add_action(scumm.actions.Say(tag='player', font='monkey', lines=[rv('$dialogues/storekeeper/' + str(args[0]))]))
    s.add_action(scumm.actions.Say(tag='storekeeper', font='monkey', lines=[rv('$dialogues/storekeeper/' + str(args[1]))]))
    s.add_action(scumm.actions.Walk(tag='player', pos=(226, 18)))
    s.add_action(scumm.actions.Turn(tag='player', dir='n'))
    s.add_action(actions.SetActive(tag='sword', value=True))
    s.add_action(a.custom_actions.rm_from_inventory('sword'))
    s.add_action(scumm.actions.Walk(tag='player', pos=(229, 7)))
    s.add_action(scumm.actions.Turn(tag='player', dir='e'))
    s.add_action(scumm.actions.Say(tag='storekeeper', font='monkey', lines=[rv('$dialogues/storekeeper/24')]))


def replace_shovel(s, *args):
    rv = monkey.engine.read
    s.add_action(scumm.actions.Say(tag='player', font='monkey', lines=[rv('$dialogues/storekeeper/' + str(args[0]))]))
    s.add_action(scumm.actions.Say(tag='storekeeper', font='monkey', lines=[rv('$dialogues/storekeeper/' + str(args[1]))]))
    s.add_action(scumm.actions.Walk(tag='player', pos=(151, 69)))
    s.add_action(scumm.actions.Turn(tag='player', dir='w'))
    s.add_action(actions.SetActive(tag='shovel', value=True))
    s.add_action(a.custom_actions.rm_from_inventory('shovel'))
    s.add_action(scumm.actions.Walk(tag='player', pos=(229, 7)))
    s.add_action(scumm.actions.Turn(tag='player', dir='e'))
    s.add_action(scumm.actions.Say(tag='storekeeper', font='monkey', lines=[rv('$dialogues/storekeeper/24')]))



def buy_sword(s, *args):
    s.add_action(scumm.actions.Say(tag='player', font='monkey', lines=sh([34])))
    s.add_action(scumm.actions.Say(tag='storekeeper', font='monkey', lines=sh([35, 36, 37])))
    s.add_action(a.custom_actions.add_to_inventory('pieces_of_eight', -100))
    status.paid_sword = 1

def ask_for_sword_master(s, *args):
    s.add_action(scumm.actions.Say(tag='player', font='monkey', lines=sh([38])))
    #s.add_action(scumm.actions.Say(tag='storekeeper', font='monkey', lines=sh([39, 40, 41, 42, 43, 44, 45, 46, 47])))
    s.add_action(scumm.actions.Walk(tag='storekeeper', pos=status.pos.store_entry))
    #s.add_action(scumm.actions.Turn(tag='storekeeper', dir='e'))
    #s.add_action(scumm.actions.Say(tag='storekeeper', font='monkey', lines=sh([52])))
    #s.add_action(scumm.actions.Turn(tag='storekeeper', dir='w'))
    s.add_action(actions.SetActive(tag='storekeeper', value=False))
    s.add_action(actions.Animate(tag='store_door', anim='closed'))
    s.add_action(a.custom_actions.update_item(item_id='storekeeper', room='village3', pos=(683, 10), dir='e', parent='walkarea_0', size=None))
    s.add_action(a.custom_actions.set_timestamp('@storekeeper_left_store'))
    s.add_action(a.custom_actions.set_timestamp('@storekeeper_last_update'))
    # save timestamp to record WHEN storekeeper left



def ask_for_sword_master_2(s, *args):
    s.add_action(scumm.actions.Say(tag='player', font='monkey', lines=sh([48])))
    s.add_action(scumm.actions.Say(tag='storekeeper', font='monkey', lines=sh([49])))
    s.add_action(scumm.actions.Say(tag='player', font='monkey', lines=sh([50])))
    s.add_action(scumm.actions.Say(tag='storekeeper', font='monkey', lines=sh([44,45,51, 47])))