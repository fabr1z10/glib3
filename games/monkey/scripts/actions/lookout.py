from . import shared as a

import scumm.actions
import example
import entity
from script import Script
import actions
import status
import monkey
import vars




walkto_lookout_stairs = a.Actions.goto_room('village1', status.pos.village_cliffside, 'e')
walkto_lookout_path = a.Actions.goto_room('meleemap', status.pos.melee_village, 'n')

