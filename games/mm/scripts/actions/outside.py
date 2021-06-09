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