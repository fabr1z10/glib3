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


lookat_village1_poster = a.Actions.say(['$lines/1', '$lines/2'])
walkto_cliffside = a.Actions.goto_room('lookout', status.pos.lookout_stairs, 'n')
walkto_village1_archway = a.Actions.goto_room('village2', status.pos.village2_archway, 's')
walkto_village2_archway_to_village1 = a.Actions.goto_room('village1', status.pos.village1_archway, 'w')
walkto_village2_archway_to_village3 = a.Actions.goto_room('village3', status.pos.village3_archway, 'w')
walkto_village3_archway = a.Actions.goto_room('village2', status.pos.village2_archway3, 's')


def talkto_citizen(x, y):
    bb = shc('$dialogues/citizen/')
    lines = [1]
    if status.talked_to_citizen == 1:
        lines = [8, 9]
    elif status.talked_to_citizen == 2:
        lines = [8, 9, 27, 28]
    s = a.Scripts.walk(x)
    s.add_action(a.custom_actions.disable_controls)
    s.add_action(scumm.actions.Turn(tag='citizen', dir='e'))
    s.add_action(scumm.actions.Say(tag='citizen', lines=bb(lines), font='monkey'))
    s.add_action(scumm.actions.StartDialogue(dialogue_id='citizen'))
    if status.talked_to_citizen == 0:
        status.talked_to_citizen = 1
    example.play(s)

def on_exit_citizen():
    s = Script()
    s.add_action(a.custom_actions.enable_controls)
    s.add_action(scumm.actions.Turn(tag='citizen', dir='s'))
    example.play(s)



def sh(l):
    rv = monkey.engine.read
    return [rv('$dialogues/storekeeper/' + str(x)) for x in l]

def shc(m):
    def f(l):
        rv = monkey.engine.read
        return [rv(m + str(x)) for x in l]
    return f


open_village_scummbar_door = a.Actions.open_door()
close_village_scummbar_door = a.Actions.close_door()
open_village3_store_door = a.Actions.open_door()
close_village3_store_door = a.Actions.close_door()






walkto_village_scummbar_door = a.Actions.walk_door('scummbar',status.pos.scummbar_main_door, 'e')
walkto_village3_store_door = a.Actions.walk_door('store',status.pos.store_entry, 'e')


def on_start_village3():
    a.chase_storekeeper_func('village3')


def on_start_village2():
    a.chase_storekeeper_func('village2')


def on_start_village1():
    a.chase_storekeeper_func('village1')


def on_load_village3():
    a.storekeeper_script(status.pos.village3_archway, 'village2', (162, 41), 's')


def on_load_village2():
    a.storekeeper_script(status.pos.village2_archway, 'village1', (820, 34), 'w')


def on_load_village1():
    a.storekeeper_script(status.pos.village_cliffside, 'lookout', (258, 52), 'n')


def citizen_map(s, *args):
    bb =shc('$dialogues/citizen/')
    s.add_action(a.custom_actions.set_variable("@talked_to_citizen", 2))
    s.add_action(scumm.actions.Say(tag='player', font='monkey', lines=bb([args[0]])))
    s.add_action(scumm.actions.Say(tag='citizen', font='monkey', lines=bb(args[1])))
    # business
    s.add_action(scumm.actions.Say(tag='citizen', font='monkey', lines=bb([18])))
    s.add_action(actions.Animate(tag='citizen', anim='open_jacket', sync=True))
    s.add_action(actions.Animate(tag='citizen', anim='idle_e_1', sync=True))
    s.add_action(actions.Delay(sec=1))
    s.add_action(actions.Animate(tag='citizen', anim='talk_e_1', sync=True))
    s.add_action(scumm.actions.Say(tag='citizen', font='monkey', animate=False, lines=bb([19])))
    s.add_action(actions.Animate(tag='citizen', anim='idle_e_1', sync=True))
    s.add_action(actions.Delay(sec=1))
    s.add_action(actions.Animate(tag='citizen', anim='open_jacket', sync=True, fwd=False))
    s.add_action(scumm.actions.Say(tag='citizen', font='monkey', lines=bb([20])))
    s.add_action(actions.Animate(tag='citizen', anim='rollmap', sync=True))
    s.add_action(actions.Animate(tag='citizen', anim='idle_e_2', sync=True))
    s.add_action(actions.Delay(sec=1))
    s.add_action(actions.Animate(tag='citizen', anim='talk_e_2', sync=True))
    s.add_action(scumm.actions.Say(tag='citizen', font='monkey', animate=False, lines=bb([21, 22])))
    s.add_action(actions.Animate(tag='citizen', anim='idle_e_2', sync=True))
    s.add_action(actions.Animate(tag='citizen', anim='rollmap', sync=True, fwd =False))
    s.add_action(scumm.actions.Say(tag='citizen', font='monkey', lines=bb([23])))
    example.play(s)