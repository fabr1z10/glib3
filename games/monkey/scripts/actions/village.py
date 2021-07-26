from . import shared as a

import scumm.actions
import example
import entity
from script import Script
import actions
import status
import monkey
import vars




lookat_village1_poster = a.Actions.say(['$lines/1', '$lines/2'])
walkto_cliffside = a.Actions.goto_room('lookout', status.pos.lookout_stairs, 'n')
walkto_village1_archway = a.Actions.goto_room('village2', status.pos.village2_archway, 's')

open_village_scummbar_door = a.Actions.open_door()
close_village_scummbar_door = a.Actions.close_door()
walkto_village_scummbar_door = a.Actions.walk_door('scummbar',status.pos.scummbar_main_door, 'e')
