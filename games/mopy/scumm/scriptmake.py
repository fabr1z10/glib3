import mopy
from mopy.actions import Walk, Turn, ChangeRoom
import mopy.scumm.shortcut as sc
from mopy.scumm.actionlib import update_item

script_factories = dict()


# walk to item
def wti(item_id, args, s, current):
    # if you own the item, no need to walk
    # you can override the item via 2nd argument
    item_id = args[1] if len(args) >= 2 else item_id
    if item_id in mopy.monkey.engine.data.globals.inventory:
        return current
    item = sc.get_item(item_id)
    pos = item.get('walk_to')
    wdir = item.get('wdir', None)
    iid = s.add_action(Walk(pos, 'player'))
    if wdir:
        iid = s.add_action(Turn(wdir, 'player'), after=[iid])
    return iid


def chr(item_id, args, s, current):
    pos_id =int(args[1])
    game_vars = mopy.monkey.engine.data.game
    if pos_id not in game_vars.positions:
        print ('unknown position: ' + str(pos_id))
        exit(1)
    p = game_vars.positions[pos_id]

    iid = s.add_action(update_item(mopy.monkey.engine.data.globals.current_player,
        {'room': p[0], 'pos': p[1], 'dir': p[2], 'parent': p[3]}))
    iid = s.add_action(ChangeRoom(p[0]), after=[iid])
    return iid


script_factories['wti'] = wti
script_factories['chr'] = chr

