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