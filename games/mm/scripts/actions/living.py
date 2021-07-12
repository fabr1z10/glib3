from . import shared as a
import scumm.actions
import example
import entity
from script import Script
import actions
import status
import monkey
import vars

open_door_living_entry = a.Actions.open_door()
close_door_living_entry = a.Actions.close_door()
walkto_door_living_entry = a.Actions.walk_door('entry', status.Pos.door_entry_living, 'w')

def open_radio(item_id, entity):
    s = a.Scripts.walk(item_id)
    s.add_action(actions.CallFunc(f=a.openDoor(item_id, 'open')))
    #s.add_action(actions.CallFunc(f=activateBreakers(True)))
    example.play(s)


def close_radio(item_id, entity):
    s = a.Scripts.walk(item_id)
    s.add_action(actions.CallFunc(f=a.openDoor(item_id, 'closed')))
    #s.add_action(actions.CallFunc(f=activateBreakers(True)))
    example.play(s)