import mopy
from mopy.script import Script
from mopy.actions import Walk, Turn, Say, ChangeRoom
from mopy.scumm.actionlib import start_dialogue, update_item, open_door, close_door
import mopy.scumm.shortcut as sc


def walk_to(item_id):
    # now get the walk_to for this item
    s = Script(uid='_main')
    item = sc.get_item(item_id)

    pos = item.get('walk_to')
    wdir = item.get('wdir', None)
    s.add_action(Walk(pos, 'player'))
    if wdir:
        s.add_action(Turn(wdir, 'player'))
    return s


def walk_and_say(item_id, lines):
    s = walk_to(item_id)
    s.add_action(Say(lines=lines, tag='player'))
    return s


def walk_and_change_room(item_id, room, pos, dir, parent='walkarea_0'):
    s = walk_to(item_id)
    s.add_action(update_item(mopy.monkey.engine.data.globals.current_player, {'room': room, 'pos': pos, 'dir': dir, 'parent': parent}))
    s.add_action(ChangeRoom(room))
    return s

def walk_and_dialogue(item_id, dialogue_id):
    a = walk_to(item_id)
    a.add_action(start_dialogue(dialogue_id, False))
    return a


def walk_and_open_door(item_id, door_id):
    s = walk_to(item_id)
    s.add_action(open_door(item_id, door_id))
    return s


def walk_and_close_door(item_id, door_id):
    s = walk_to(item_id)
    s.add_action(close_door(item_id, door_id))
    return s


def walk_to_door(item_id, door_id, room, pos, dir, parent='walkarea_0'):
    if getattr(mopy.monkey.engine.data.game.doors, door_id) == 'open':
        s = walk_and_change_room(item_id, room, pos, dir, parent)
    else:
        s = walk_to(item_id)
    return s