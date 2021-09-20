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


def walkto_circus_tent(item, entity):
    if status.circus_feat_done == 0:
        return a.Actions.goto_room('circus', status.pos.circus_entry, 'w')(item, entity)
    else:
        return a.Actions.say(['$dialogues/fettuccini/104'])(item, entity)

