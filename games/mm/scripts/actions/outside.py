from . import shared as a
import scumm.actions
import example
import entity
from script import Script
import actions
import status
import monkey
import vars

# one-object actions

read_sign = a.Actions.say(['$lines/1', '$lines/2'])
walkto_path_outside_frontdoor = a.Actions.goto_room('frontdoor', [960, 2], 'w')

read_grandfather_clock = a.Actions.say(['$lines/8'])
open_door_entry_basement = a.Actions.say(['$lines/9'])

def push_gargoyle_right(item_id, entity):
    s = a.Scripts.walk(item_id)
    s.add_action(actions.CallFunc(f=a.openDoor('door_entry_basement', 'open')))
    example.play(s)

def walkto_door_entry_basement(item_id, entity):
    if example.get(item_id).anim == 'open':
        a.Actions.goto_room('basement', [577, 108], 's')(item_id, entity)
    else:
        s = a.Scripts.walk(item_id)
        example.play(s)


open_door_entry_living = a.Actions.open_door()
close_door_entry_living = a.Actions.close_door()
walkto_door_entry_living = a.Actions.walk_door('living', [54, 6], 'e')

pull_gargoyle_right = push_gargoyle_right





def pino(t):
    example.get('door_entry_basement').setAnim('closed')