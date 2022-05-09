import mopy
from mopy.actions import Walk, Turn, ChangeRoom, Say, Turn, Delay, DelayRandom, SuspendScript, ResumeScript, Msg, SetWall, Animate, NoOp
import mopy.scumm.shortcut as sc
from mopy.entity import TextAlignment
from mopy.scumm.actionlib import update_item, start_dialogue, set_variable, set_text, open_door, close_door, \
    create_item, remove_item, enable_controls, sierra_enable_controls, pickup_item
import operator
import types

script_factories = dict()

def vecf(a):
    if isinstance(a, tuple) or isinstance(a, list):
        return a
    return [float(x) for x in a.split(';')]

def veci(a):
    if isinstance(a, tuple) or isinstance(a, list):
        return a
    return [int(x) for x in a.split(';')]

def proc_arg(arg, script_vars):
    if len(arg) == 0:
        return arg
    a = arg
    done = False
    while not done:
        print('proc: ' + str(a))
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
        if a[0] == '#' and a[1] != '#':
            f = operator.attrgetter(a[1:])(mopy.monkey.engine.data)
            if isinstance(f, types.FunctionType):
                a = f()
            else:
                a = f
        done = True
    return a






def proc_args(args, script_vars):
    # process arguments
    return [proc_arg(x, script_vars) for x in args]


def anim(args,s,current,sa):
    sync = False if (len(args) < 3 or args[2] == 0) else True
    iid = s.add_action(Animate(anim=args[1],tag=args[0],sync=sync))
    return iid

# walk to item
def wti(args, s, current,sa):
    # if you own the item, no need to walk
    # you can override the item via 2nd argument
    item_id = args[0] if len(args) >= 1 else sa[0]
    if item_id in mopy.monkey.engine.data.globals.inventory:
        iid = s.add_action(NoOp())
        return iid
    item = sc.get_item(item_id)
    pos = item.get('walk_to')
    wdir = item.get('wdir', None)
    iid = s.add_action(Walk(pos, 'player'))
    if wdir:
        iid = s.add_action(Turn(wdir, 'player'), after=[iid])
    return iid

# walk to position
def wtp(args, s, current,sa):
    # if you own the item, no need to walk
    # you can override the item via 2nd argument
    tag = args[0] if args[0] != '' else 'player'
    iid = s.add_action(Walk(pos=args[1], tag=tag))
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
    iid = s.add_action(Say(lines=args[1:], tag=tag))
    return iid


def tur(args, s, current, sa):
    tag = args[0] if len(args[0]) > 0 else 'player'
    iid = s.add_action(Turn(tag=tag, dir=args[1]))
    return iid


def dia(args, s, current, sa):
    iid = s.add_action(start_dialogue(args[0], False))
    return iid


def set(args, s, current, sa):
    iid = s.add_action(set_variable(args[0], args[1]))
    return iid

def setbool(args, s, current, sa):
    iid = s.add_action(set_variable(args[0], False if args[1]=='f' else True))
    return iid

def txt(args, s, current, sa):
    iid = s.add_action(set_text(args[0], args[1]))
    return iid

def ope(args, s, current, sa):
    item_id = args[0] if len(args) > 0 else sa[0]
    door_id = sc.get_item(item_id)['door']
    iid = s.add_action(open_door(item_id, door_id))
    return iid

def clo(args, s, current, sa):
    item_id = args[0] if len(args) > 0 else sa[0]
    door_id = sc.get_item(item_id)['door']
    iid = s.add_action(close_door(item_id, door_id))
    return iid

def dly(args, s, current, sa):
    iid = s.add_action(Delay(sec=float(args[0])))
    return iid

def new(args, s, current, sa):
    iid = s.add_action(create_item(args[0], {'pos': vecf(args[1])}, parent='walkarea_0'))
    return iid

def del_item(args, s, current, sa):
    iid = s.add_action(remove_item(args[0]))
    return iid

def eui(args, s, current, sa):
    iid = s.add_action(enable_controls(True))
    return iid

def dui(args, s, current, sa):
    iid = s.add_action(enable_controls(False))
    return iid

def sus(args, s, current, sa):
    iid = s.add_action(SuspendScript(args[0]))
    return iid

def res(args, s, current, sa):
    iid = s.add_action(ResumeScript(args[0]))
    return iid


def msg(args, s, current, sa):
    gl = mopy.scumm.gl #mopy.monkey.engine.data.globals
    iid = s.add_action(sierra_enable_controls(False))
    iid = s.add_action(Msg(
        font=gl.msg_font,
        color=(127/255.0, 83/255.0, 30/255.0, 255/255.0),
        align=TextAlignment.center,
        text=args[0],
        pos=(gl.sci_viewport[2] * 0.5, gl.sci_viewport[3] * 0.5, 1),
        inner_texture=gl.msg_inner_texture,
        border_texture=gl.msg_border_texture,
        eoc=True,
        timeout=1000,
        box=True,
        padding=(4, 5)), after=iid)
    iid = s.add_action(sierra_enable_controls(True), after=iid)
    return iid

def prn(args, s, current, sa):
    iid = s.add_action(Msg(font=mopy.monkey.engine.data.globals.default_font,
                           color=args[1],align=TextAlignment.bottom,text=args[0],
                           pos=(int(args[2]),int(args[3]), 1)))
    return iid

def set_wall(args,s,current,sa):
    wall_id = args[0]
    active = True if args[1]=='1' else False
    iid = s.add_action(SetWall('walkarea_0', 0, active))
    return iid

def get(args, s, current, sa):
    item_id = sa[0]
    iid = s.add_action(pickup_item(args[0], item_id))
    return iid




script_factories['wti'] = wti
script_factories['wtp'] = wtp
script_factories['chr'] = chr
script_factories['say'] = say
script_factories['tur'] = tur
script_factories['dia'] = dia
script_factories['set'] = set
script_factories['setbool'] = setbool
script_factories['txt'] = txt
script_factories['ope'] = ope
script_factories['clo'] = clo
script_factories['dly'] = dly
script_factories['new'] = new
script_factories['del'] = del_item
script_factories['eui'] = eui
script_factories['dui'] = dui
script_factories['sus'] = sus
script_factories['res'] = res
script_factories['smsg'] = msg
script_factories['msg'] = prn
script_factories['set_wall'] = set_wall
script_factories['anim'] = anim
script_factories['get'] = get