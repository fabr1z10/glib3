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


lookat_yellow_plant = a.Actions.say(['$lines/47'])
lookat_yellow_petal = a.Actions.say(['$lines/48'])
lookat_swordmaster_sign = a.Actions.say(['$lines/49'])

def pickup_yellow_plant(x, y):
    if 'yellow_petal' not in vars.inventory:
        s = a.Scripts.walk(x)
        s.add_action(a.custom_actions.add_to_inventory("yellow_petal"))
        example.play(s)

walkto_forest1_exit = a.Actions.goto_room('meleemap', status.pos.melee_fork, 's')
walkto_forest1_forest2 = a.Actions.goto_room('forest2', status.pos.forest1_entry, 'w')
walkto_forest1_forest2b = a.Actions.goto_room('forest2', status.pos.forest1_entry, 'w')
walkto_forest2_forest1 = a.Actions.goto_room('forest1', (238, 68), 's')
walkto_forest2_forest3 = a.Actions.goto_room('forest3', (135, 69), 's')
walkto_forest3_forest2 = a.Actions.goto_room('forest2', (257, 69), 's')
walkto_forest3_forest4 = a.Actions.goto_room('forest4', (0, 35), 'e')
walkto_forest4_forest3 = a.Actions.goto_room('forest3', (310, 35), 'w')
walkto_forest4_forest5 = a.Actions.goto_room('forest5', (241, 69), 's')
walkto_forest5_forest4 = a.Actions.goto_room('forest4', (310, 35), 'w')
walkto_forest5_forest6 = a.Actions.goto_room('forest6', (0, 35), 'e')
walkto_forest5_forest8 = a.Actions.goto_room('forest8', (310, 35), 'w')
walkto_forest6_forest5 = a.Actions.goto_room('forest5', (0, 35), 'e')
walkto_forest6_forest7 = a.Actions.goto_room('forest7', (0, 30), 'e')
walkto_forest7_forest6 = a.Actions.goto_room('forest6', (151, 69), 's')

#walkto_forest2_forest9 = a.Actions.goto_room('forest9', (238, 68), 's')

