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

#pickup_developer = a.Actions.pickup()
pickup_tentacle_chow = a.Actions.pickup()
pickup_canned_goods = a.Actions.pickup()
pickup_fruit_drinks = a.Actions.pickup()
pickup_glass_jar = a.Actions.pickup()


