from . import shared as a

import scumm.actions
import example
import entity
from script import Script
import actions
import status
import monkey
import vars

import random


lookat_village1_poster = a.Actions.say(['$lines/1', '$lines/2'])
walkto_cliffside = a.Actions.goto_room('lookout', status.pos.lookout_stairs, 'n')
walkto_village1_archway = a.Actions.goto_room('village2', status.pos.village2_archway, 's')
walkto_village2_archway_to_village1 = a.Actions.goto_room('village1', status.pos.village1_archway, 'w')
walkto_village2_archway_to_village3 = a.Actions.goto_room('village3', status.pos.village3_archway, 'w')
walkto_village3_archway = a.Actions.goto_room('village2', status.pos.village2_archway3, 's')



open_village_scummbar_door = a.Actions.open_door()
close_village_scummbar_door = a.Actions.close_door()
open_village3_store_door = a.Actions.open_door()
close_village3_store_door = a.Actions.close_door()

open_store_door = a.Actions.open_door()
close_store_door = a.Actions.close_door()
walkto_store_door = a.Actions.walk_door('village3', status.pos.village_store_door, 's')

walkto_village_scummbar_door = a.Actions.walk_door('scummbar',status.pos.scummbar_main_door, 'e')
walkto_village3_store_door = a.Actions.walk_door('store',status.pos.store_entry, 'e')


def open_storekeeper(aa, ba):
    s = a.Scripts.walk('storekeeper')
    s.add_action(actions.ResumeScript(s='_storekeeper'))

    # m = '$dialogues/important_looking_pirates/'
    # if status.pirates_know_guybrush == 0:
    #     l = [monkey.engine.read(m+'1')]
    # else:
    #     l = [monkey.engine.read(m + '40'), monkey.engine.read(m + '41')]
    # s.add_action(scumm.actions.EnableUI(False))
    # s.add_action(scumm.actions.Say(tag='important_looking_pirate_2', lines=l, font='monkey'))
    # s.add_action(scumm.actions.StartDialogue('ilp'))
    example.play(s)


def talkto_storekeeper(aa, ba):
    s = a.Scripts.walk('storekeeper')
    s.add_action(actions.SuspendScript(s='_storekeeper'))

    # m = '$dialogues/important_looking_pirates/'
    # if status.pirates_know_guybrush == 0:
    #     l = [monkey.engine.read(m+'1')]
    # else:
    #     l = [monkey.engine.read(m + '40'), monkey.engine.read(m + '41')]
    # s.add_action(scumm.actions.EnableUI(False))
    # s.add_action(scumm.actions.Say(tag='important_looking_pirate_2', lines=l, font='monkey'))
    # s.add_action(scumm.actions.StartDialogue('ilp'))
    example.play(s)

def say_random():
    s = Script(uid='_storekeeper')
    s.add_action(scumm.actions.Say(tag='storekeeper', font='monkey', lines=a.make_lines(['$dialogues/storekeeper/' + str(random.randint(2, 3))])))
    s.add_action(actions.Delay(sec=5))
    s.add_action(actions.CallFunc(f=say_random))
    example.play(s)

def init_store():
    s = Script(uid='_storekeeper')
    s.add_action(scumm.actions.Say(tag='storekeeper', font='monkey', lines=a.make_lines(['$dialogues/storekeeper/1'])))
    s.add_action(actions.Delay(sec=5))
    s.add_action(actions.CallFunc(f=say_random))
    example.play(s)

def pippolandia():
    print ('fottimie!')