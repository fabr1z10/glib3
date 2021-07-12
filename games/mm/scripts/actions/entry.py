from . import shared as a
import scumm.actions
import example
import entity
from script import Script
import actions
import status
import monkey
import vars

open_door_entry_living = a.Actions.open_door()
close_door_entry_living = a.Actions.close_door()
walkto_door_entry_living = a.Actions.walk_door('living', status.Pos.door_living_entry, 'e')