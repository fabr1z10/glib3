from . import shared as a

import mopy.scumm as scumm
import example
from mopy.script import Script
import mopy.actions as actions

import data.vars as vars


import random


lookat_yellow_plant = a.Actions.say(['$lines/47'])
lookat_yellow_petal = a.Actions.say(['$lines/48'])
lookat_swordmaster_sign = a.Actions.say(['$lines/49'])
lookat_campsite = a.Actions.say(['$lines/52'])
lookat_bones = a.Actions.say(['$lines/55'])
lookat_red_plant = a.Actions.say(['$lines/53'])
lookat_rock_and_plant = a.Actions.say(['$lines/56'])

pickup_red_plant = a.Actions.say(['$lines/54'])


def helper_swordmaster_sign(x, anim, bridge):
    s = a.Scripts.walk(x)
    s.add_action(actions.Animate(tag='player', anim='operate_e'))
    s.add_action(actions.Animate(tag='player', anim='idle_e'))
    s.add_action(actions.Animate(tag='swordmaster_sign', anim=anim))
    s.add_action(actions.Animate(tag='trunk_bridge', anim=anim))
    s.add_action(a.custom_actions.set_variable('@vars/forest_bridge', anim))
    s.add_action(scumm.actions.SetWall('walkarea_0', 0, bridge))
    example.play(s)


def push_swordmaster_sign(x, y):
    helper_swordmaster_sign(x, 'activated', False)


def pull_swordmaster_sign(x, y):
    helper_swordmaster_sign(x, 'closed', True)

def pickup_yellow_plant(x, y):
    if 'yellow_petal' not in vars.inventory:
        s = a.Scripts.walk(x)
        s.add_action(a.custom_actions.add_to_inventory("yellow_petal"))
        example.play(s)

walkto_forest1_exit = a.Actions.goto_room('meleemap', vars.pos.melee_fork, 's')
walkto_forest1_forest2 = a.Actions.goto_room('forest2', vars.pos.forest1_entry, 'w')
walkto_forest1_forest2b = a.Actions.goto_room('forest2', vars.pos.forest1_entry, 'w')
walkto_forest2_forest1 = a.Actions.goto_room('forest1', (238, 68), 's')
walkto_forest2_forest9 = a.Actions.goto_room('forest9', (0, 24), 'e')
walkto_forest2_forest3 = a.Actions.goto_room('forest3', (135, 69), 's')
walkto_forest3_forest2 = a.Actions.goto_room('forest2', (257, 69), 's')
walkto_forest3_forest4 = a.Actions.goto_room('forest4', (0, 35), 'e')
walkto_forest4_forest3 = a.Actions.goto_room('forest3', (310, 35), 'w')
walkto_forest4_forest5 = a.Actions.goto_room('forest5', (241, 69), 's')
walkto_forest5_forest4 = a.Actions.goto_room('forest4', (310, 35), 'w')
walkto_forest5_forest6 = a.Actions.goto_room('forest6', (0, 35), 'e')
walkto_forest5_forest8 = a.Actions.goto_room('forest8', (136, 65), 's')
walkto_forest6_forest5 = a.Actions.goto_room('forest5', (0, 35), 'e')
walkto_forest6_forest7 = a.Actions.goto_room('forest7', (0, 30), 'e')
walkto_forest7_forest6 = a.Actions.goto_room('forest6', (151, 69), 's')
walkto_forest7_swordmaster = a.Actions.goto_room('swordmaster', (0, 20), 'e')

walkto_forest9_forest2 = a.Actions.goto_room('forest2', (0, 35), 'e')
walkto_forest9_forest10_1 = a.Actions.goto_room('forest10', (310, 24), 'w')
walkto_forest9_forest10_2 = a.Actions.goto_room('forest10', (310, 24), 'w')
walkto_forest9_forest8 = a.Actions.goto_room('forest8', (310, 24), 'w')

walkto_forest10_forest9 = a.Actions.goto_room('forest9', (259, 69), 's')
walkto_forest10_forest11 = a.Actions.goto_room('forest11', (320, 24), 'w')

walkto_forest11_forest10 = a.Actions.goto_room('forest10', (0, 24), 'e')
walkto_forest11_forest12 = a.Actions.goto_room('forest12', (310, 24), 'w')

walkto_forest12_forest11 = a.Actions.goto_room('forest11', (257, 59), 's')
walkto_forest12_forest13 = a.Actions.goto_room('forest13', (310, 28), 's')

walkto_forest13_forest12 = a.Actions.goto_room('forest12', (0, 46), 'e')
walkto_forest13_forest14 = a.Actions.goto_room('forest14', (0, 48), 'e')

walkto_forest14_forest13 = a.Actions.goto_room('forest13', (257, 59), 's')
walkto_forest14_forest15 = a.Actions.goto_room('forest15', (153, 68), 's')

walkto_forest15_forest14 = a.Actions.goto_room('forest14', (50, 59), 's')
walkto_forest15_forest18 = a.Actions.goto_room('forest18', (135, 65), 's')

walkto_forest18_forest15 = a.Actions.goto_room('forest15', (0, 32), 's')
walkto_forest18_forest19 = a.Actions.goto_room('forest19', (310, 32), 's')

walkto_forest19_forest18 = a.Actions.goto_room('forest18', (0, 24), 's')
walkto_forest19_forest20 = a.Actions.goto_room('forest20', (310, 32), 'w')
walkto_forest19_forest8 = a.Actions.goto_room('forest8', (0, 24), 'e')

walkto_forest8_forest19 = a.Actions.goto_room('forest19', (0, 44), 'e')
walkto_forest8_forest5 = a.Actions.goto_room('forest5', (310, 24), 'w')
walkto_forest8_forest9 = a.Actions.goto_room('forest9', (310, 36), 'w')

walkto_forest20_forest19 = a.Actions.goto_room('forest19', (156, 69), 's')

#walkto_forest2_forest9 = a.Actions.goto_room('forest9', (238, 68), 's')


def on_start_forest1():
    a.chase_storekeeper_func('forest1')


def on_load_forest1():
    a.storekeeper_script(vars.pos.f1f2, 'forest2', (257, 45), 'n')


def on_start_forest2():
    a.chase_storekeeper_func('forest2')


def on_load_forest2():
    a.storekeeper_script((257, 69), 'forest3', (242, 35), 'e')


def on_start_forest3():
    a.chase_storekeeper_func('forest3')


def on_load_forest3():
    a.storekeeper_script((320, 69), 'forest4', (249, 35), 'e')


def on_start_forest4():
    a.chase_storekeeper_func('forest4')


def on_load_forest4():
    a.storekeeper_script((320, 35), 'forest5', (78, 24), 'w')


def on_start_forest5():
    a.chase_storekeeper_func('forest5')


def on_load_forest5():
    a.storekeeper_script((0, 24), 'forest6', (151, 40), 'n')


def on_start_forest6():
    a.chase_storekeeper_func('forest6')


def on_load_forest6():
    a.storekeeper_script((151, 69), 'forest7', (101, 30), 'e')


def on_start_forest7():
    a.chase_storekeeper_func('forest6')


def on_load_forest7():
    if example.get('storekeeper').valid:
        s = Script()
        s.add_action(a.custom_actions.disable_controls)
        s.add_action(scumm.actions.Walk(tag='storekeeper', pos=(160, 20)))
        s.add_action(actions.Delay(sec=0.5))
        s.add_action(actions.Animate(tag='swordmaster_sign', anim='activated'))
        s.add_action(actions.Animate(tag='trunk_bridge', anim='activated'))
        s.add_action(a.custom_actions.set_variable('@forest_bridge', 'activated'))
        s.add_action(scumm.actions.SetWall('walkarea_0', 0, False))
        s.add_action(scumm.actions.Walk(tag='storekeeper', pos=(320, 47)))
        s.add_action(actions.SetActive(tag='storekeeper', value=False))
        s.add_action(a.custom_actions.update_item(item_id='storekeeper', room='swordmaster', pos=(144, 20), dir='e',
            parent='walkarea_0', size=None))
        s.add_action(a.custom_actions.set_timestamp('@storekeeper_last_update'))
        s.add_action(a.custom_actions.enable_controls)
        example.play(s)


def on_start_swordmaster():
    a.chase_storekeeper_func('swordmaster')


def on_load_swordmaster():
    if example.get('storekeeper').valid:
        s = Script()
        s.add_action(a.custom_actions.disable_controls)
        s.add_action(a.custom_actions.set_follow(False), id=1)
        s.add_action(scumm.actions.Walk(tag='storekeeper', pos=(375, 68)), id=2)
        s.add_action(actions.Scroll(pos=(304, 72), cam='maincam', speed=50, relative=False), after=[1])
        s.add_action(scumm.actions.Walk(tag='player', pos=(210, 14)), id=3, after=[1])
        s.add_action(scumm.actions.Turn(tag='storekeeper', dir='e'), after=[2])
        s.add_action(scumm.actions.Turn(tag='player', dir='s'), after=[3])
        s.add_action(scumm.actions.Say(tag='player', font='monkey', lines=a.make_lines(['$lines/50'])))
        s.add_action(scumm.actions.Turn(tag='player', dir='n'))
        s.add_action(actions.Delay(sec=1.0), after=[2])
        # TODO change room to sword master house here
        s.add_action(a.custom_actions.enable_controls)
        example.play(s)