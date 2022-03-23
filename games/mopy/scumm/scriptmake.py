import mopy
from mopy.actions import Walk, Turn, ChangeRoom, Say, Turn
import mopy.scumm.shortcut as sc
from mopy.scumm.actionlib import update_item, start_dialogue, set_variable, set_text, open_door, close_door

script_factories = dict()


def proc_arg(arg, script_vars):
    if len(arg) == 0:
        return arg
    a = arg
    done = False
    while not done:
        expr = a.find('{{')
        if expr != -1:
            # found an expression to evaluate
            fi = a.find('}}')
            ev = eval(a[expr+2:fi])
            a = a[:5] + ev + a[fi+2:]
            continue
        if a[0] == '@' and a[1] != '@':
            a = script_vars[int(a[1:])]
            continue
        if a[0] == '$' and a[1] != '$':
            a = mopy.monkey.engine.read(a)
            continue
        done = True
    return a






def proc_args(args, script_vars):
    # process arguments
    return [proc_arg(x, script_vars) for x in args]



# walk to item
def wti(args, s, current,sa):
    # if you own the item, no need to walk
    # you can override the item via 2nd argument
    item_id = args[1] if len(args) >= 2 else sa[0]
    if item_id in mopy.monkey.engine.data.globals.inventory:
        return current
    item = sc.get_item(item_id)
    pos = item.get('walk_to')
    wdir = item.get('wdir', None)
    iid = s.add_action(Walk(pos, 'player'))
    if wdir:
        iid = s.add_action(Turn(wdir, 'player'), after=[iid])
    return iid


def chr(args, s, current, sa):
    pos_id = int(args[0])
    game_vars = mopy.monkey.engine.data.game
    if pos_id not in game_vars.positions:
        print ('unknown position: ' + str(pos_id))
        exit(1)
    p = game_vars.positions[pos_id]

    iid = s.add_action(update_item(mopy.monkey.engine.data.globals.current_player,
        {'room': p[0], 'pos': p[1], 'dir': p[2], 'parent': p[3]}))
    iid = s.add_action(ChangeRoom(p[0]), after=[iid])
    return iid


def say(args, s, current, sa):
    tag = args[0] if len(args[0]) > 0 else 'player'
    print('lines= ' + str(args[1:]))
    iid = s.add_action(Say(lines=args[1:], tag=tag))
    return iid


def tur(args, s, current, sa):
    tag = args[0] if len(args[0]) > 0 else 'player'
    print('lines= ' + str(args[1:]))
    iid = s.add_action(Turn(tag=tag, dir=args[1]))
    return iid


def dia(args, s, current, sa):
    iid = s.add_action(start_dialogue(args[0], False))
    return iid


def set(args, s, current, sa):
    iid = s.add_action(set_variable(args[0], args[1]))
    return iid

def txt(args, s, current, sa):
    iid = s.add_action(set_text(args[0], args[1]))
    return iid

def ope(args, s, current, sa):
    door_id = sc.get_item(sa[0])['door']
    iid = s.add_action(open_door(sa[0], door_id))
    return iid

def clo(args, s, current, sa):
    door_id = sc.get_item(sa[0])['door']
    iid = s.add_action(close_door(sa[0], door_id))
    return iid

script_factories['wti'] = wti
script_factories['chr'] = chr
script_factories['say'] = say
script_factories['tur'] = tur
script_factories['dia'] = dia
script_factories['set'] = set
script_factories['txt'] = txt
script_factories['ope'] = ope
script_factories['clo'] = clo

