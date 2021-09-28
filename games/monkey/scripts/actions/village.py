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

def sh(l):
    rv = monkey.engine.read
    return [rv('$dialogues/storekeeper/' + str(x)) for x in l]

open_village_scummbar_door = a.Actions.open_door()
close_village_scummbar_door = a.Actions.close_door()
open_village3_store_door = a.Actions.open_door()
close_village3_store_door = a.Actions.close_door()






walkto_village_scummbar_door = a.Actions.walk_door('scummbar',status.pos.scummbar_main_door, 'e')
walkto_village3_store_door = a.Actions.walk_door('store',status.pos.store_entry, 'e')



def init_village3():
    print('CIAO === ' + str(status.storekeeper_left_store))
    if example.get('storekeeper').valid:
        s = Script()
        s.add_action(scumm.actions.Walk(tag='storekeeper', pos=status.pos.village3_archway))
        s.add_action(actions.SetActive(tag='storekeeper', value=False))

