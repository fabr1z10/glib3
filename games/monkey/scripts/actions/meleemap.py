from . import shared as a

import scumm.actions
import example
import entity
from script import Script
import actions
import status
import monkey
import vars

click_meleemap_lookout = a.Actions.goto_room('lookout', status.pos.lookout_path, 'w')
click_meleemap_clearing = a.Actions.goto_room('clearing', status.pos.clearing_path, 'w')

walkto_clearing_path = a.Actions.goto_room('meleemap', status.pos.melee_clearing, 'w')
lookat_circus_tent = a.Actions.say(['$lines/44'])
walkto_circus_tent = a.Actions.goto_room('circus', status.pos.circus_entry, 'w')
