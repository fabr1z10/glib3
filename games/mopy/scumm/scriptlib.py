import mopy
from mopy.script import Script
from mopy.actions import Walk, Turn, Say
from mopy.scumm.actionlib import start_dialogue


def walk_to(item_id):
    # now get the walk_to for this item
    items = mopy.monkey.engine.data.items
    s = Script(uid='_main')
    item = items[item_id]
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


def walk_and_dialogue(item_id, dialogue_id):
    a = walk_to(item_id)
    a.add_action(start_dialogue(dialogue_id, False))
    return a