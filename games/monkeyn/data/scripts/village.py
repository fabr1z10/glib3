import mopy.scumm.scriptlib as sl
import mopy.scumm.actionlib as al
import mopy


def lookat_village_poster(item_id, entity):
    return sl.walk_and_say(item_id, ['$lines/1', '$lines/2'])


def walkto_village_cliffside(item_id, entity):
    return sl.walk_and_change_room(item_id, 'lookout', mopy.monkey.engine.data.game.pos.lookout_stairs, 'n', 'walkarea_0')