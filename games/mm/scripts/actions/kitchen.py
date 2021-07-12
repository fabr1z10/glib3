from . import shared as a
import scumm.actions
import example
import entity
from script import Script
import actions
import status
import monkey
import vars

open_door_kitchen_entry = a.Actions.open_door()
close_door_kitchen_entry = a.Actions.close_door()
walkto_door_kitchen_entry = a.Actions.walk_door('entry', status.Pos.door_entry_kitchen, 's')

open_door_kitchen_dining = a.Actions.open_door()
close_door_kitchen_dining = a.Actions.close_door()
walkto_door_kitchen_dining = a.Actions.walk_door('dining', status.Pos.door_dining_kitchen, 'e')

def init_kitchen():
    opfridge(vars.items['fridge']['anim'][0] == 'o')()

def open_fridge(item_id, entity):
    s = a.Scripts.walk(item_id)
    s.add_action(actions.CallFunc(f=a.openDoor(item_id, 'open')))
    s.add_action(actions.CallFunc(f=opfridge(True)))
    #s.add_action(actions.CallFunc(f=activateBreakers(True)))
    example.play(s)

def opfridge(open: bool):
    def f():
        b = example.get('pepsi')
        if b.valid:
            b.setActive(open)
    return f

def close_fridge(item_id, entity):
    s = a.Scripts.walk(item_id)
    s.add_action(actions.CallFunc(f=a.openDoor(item_id, 'closed')))
    s.add_action(actions.CallFunc(f=opfridge(False)))
    #s.add_action(actions.CallFunc(f=activateBreakers(True)))
    example.play(s)

pickup_pepsi = a.Actions.pickup()
read_pepsi = a.Actions.say(['$lines/14'])
