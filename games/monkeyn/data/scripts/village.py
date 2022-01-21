import mopy.scumm.scriptlib as sl
import mopy.scumm.actionlib as al
import mopy


def lookat_village_poster(item_id, entity):
    return sl.walk_and_say(item_id, ['$lines/1', '$lines/2'])


def walkto_village_cliffside(item_id, entity):
    return sl.walk_and_change_room(item_id, 'lookout', mopy.monkey.engine.data.game.pos.lookout_stairs, 'n', 'walkarea_0')


def walkto_village_archway1(item_id, entity):
    return sl.walk_and_change_room(item_id, 'village2', mopy.monkey.engine.data.game.pos.village2_archway, 's', 'walkarea_0')

def walkto_village_archway2(item_id, entity):
    return sl.walk_and_change_room(item_id, 'village1', mopy.monkey.engine.data.game.pos.village1_archway, 'w', 'walkarea_0')

def walkto_village_archway3(item_id, entity):
    return sl.walk_and_change_room(item_id, 'village3', mopy.monkey.engine.data.game.pos.village3_archway, 'w', 'walkarea_0')

def walkto_village_archway4(item_id, entity):
    return sl.walk_and_change_room(item_id, 'village2', mopy.monkey.engine.data.game.pos.village2_archway3, 's', 'walkarea_0')

def open_village_door_scummbar(item_id, entity):
    return sl.walk_and_open_door(item_id, 'scummbar')

def open_village_door_voodoolady(item_id, entity):
    return sl.walk_and_open_door(item_id, 'voodoolady')

def close_village_door_scummbar(item_id, entity):
    return sl.walk_and_close_door(item_id, 'scummbar')

def close_village_door_voodoolady(item_id, entity):
    return sl.walk_and_close_door(item_id, 'voodoolady')

def walkto_village_door_scummbar(item_id, entity):
    return sl.walk_to_door(item_id, 'scummbar', 'scummbar', mopy.monkey.engine.data.game.pos.scummbar_main_door, 'e')


def open_village_door_scummbar_out(item_id, entity):
    return sl.walk_and_open_door(item_id, 'scummbar')


def close_village_door_scummbar_out(item_id, entity):
    return sl.walk_and_close_door(item_id, 'scummbar')


def walkto_village_door_scummbar_out(item_id, entity):
    return sl.walk_to_door(item_id, 'scummbar', 'village1', mopy.monkey.engine.data.game.pos.village_scummbar_door, 's')

def lookat_village_fireplace(item_id, entity):
    return sl.walk_and_say(item_id, ['$lines/3'])