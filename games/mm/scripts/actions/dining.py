from . import shared as a
import scumm.actions
import example
import entity
from script import Script
import actions
import status
import monkey
import vars

open_door_dining_kitchen = a.Actions.open_door()
close_door_dining_kitchen = a.Actions.close_door()
walkto_door_dining_kitchen = a.Actions.walk_door('kitchen', status.Pos.door_kitchen_dining, 'w')

open_door_dining_storage = a.Actions.open_door()
close_door_dining_storage = a.Actions.close_door()
walkto_door_dining_storage = a.Actions.walk_door('storage', status.Pos.door_storage_dining, 'w')


