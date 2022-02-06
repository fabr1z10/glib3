import mopy
from mopy.script import Script
from mopy.actions import Walk, Turn, Say, ChangeRoom, Msg
from mopy.scumm.actionlib import start_dialogue, update_item, open_door, close_door, sierra_enable_controls, pickup_item
import mopy.scumm.shortcut as sc
from mopy.entity import TextAlignment


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


def walk_and_pickup(item_id, e):
    s = walk_to(item_id)
    s.add_action(pickup_item(item_id, e.id))
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


def sierra_msg(text):
    gl = mopy.scumm.gl #mopy.monkey.engine.data.globals
    s = Script()
    s.add_action(sierra_enable_controls(False))
    s.add_action(Msg(
        font=gl.msg_font,
        color=(127, 83, 30, 255),
        align=TextAlignment.center,
        text=mopy.monkey.engine.read(text),
        pos=(gl.sci_viewport[2] * 0.5, gl.sci_viewport[3] * 0.5, 1),
        inner_texture=gl.msg_inner_texture,
        border_texture=gl.msg_border_texture,
        eoc=True,
        timeout=1000,
        box=True,
        padding=(4, 5)))
    s.add_action(sierra_enable_controls(True))
    return s