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

def sh(l):
    rv = monkey.engine.read
    return [rv('$dialogues/storekeeper/' + str(x)) for x in l]

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
