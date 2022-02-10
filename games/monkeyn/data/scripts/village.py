import mopy.scumm.scriptlib as sl
import mopy.scumm.actionlib as al
import mopy.actions as actions
from mopy.script import Script
import mopy
import example


def lookat_poster(item_id, entity):
    return sl.walk_and_say(item_id, ['$lines/1', '$lines/2'])


def walkto_cliffside(item_id, entity):
    return sl.walk_and_change_room(item_id, 'lookout', mopy.monkey.engine.data.game.pos.lookout_stairs, 'n', 'walkarea_0')


def walkto_archway1(item_id, entity):
    return sl.walk_and_change_room(item_id, 'village2', mopy.monkey.engine.data.game.pos.village2_archway, 's', 'walkarea_0')

def walkto_archway2(item_id, entity):
    return sl.walk_and_change_room(item_id, 'village1', mopy.monkey.engine.data.game.pos.village1_archway, 'w', 'walkarea_0')

def walkto_archway3(item_id, entity):
    return sl.walk_and_change_room(item_id, 'village3', mopy.monkey.engine.data.game.pos.village3_archway, 'w', 'walkarea_0')

def walkto_archway4(item_id, entity):
    return sl.walk_and_change_room(item_id, 'village2', mopy.monkey.engine.data.game.pos.village2_archway3, 's', 'walkarea_0')

def open_door_village_scummbar(item_id, entity):
    return sl.walk_and_open_door(item_id, 'scummbar')

def open_door_village_voodoolady(item_id, entity):
    return sl.walk_and_open_door(item_id, 'voodoolady')

def close_door_village_scummbar(item_id, entity):
    return sl.walk_and_close_door(item_id, 'scummbar')

def close_door_village_voodoolady(item_id, entity):
    return sl.walk_and_close_door(item_id, 'voodoolady')

def walkto_door_village_scummbar(item_id, entity):
    return sl.walk_to_door(item_id, 'scummbar', 'scummbar', mopy.monkey.engine.data.game.pos.scummbar_main_door, 'e')

def open_door_scummbar_village(item_id, entity):
    return sl.walk_and_open_door(item_id, 'scummbar')

def open_door_kitchen_scummbar(item_id, entity):
    return sl.walk_and_open_door(item_id, 'kitchen')

def close_door_kitchen_scummbar(item_id, entity):
    return sl.walk_and_close_door(item_id, 'kitchen')

def walkto_door_kitchen_scummbar(item_id, entity):
    return sl.walk_to_door(item_id, 'kitchen', 'scummbar', mopy.monkey.engine.data.game.pos.scummbar_kitchen_door, 'w')

def open_door_pier(item_id, entity):
    s = sl.walk_and_open_door(item_id, 'pier')
    s.add_action(actions.SetWall('walkarea_0', 0, False))
    return s

def close_door_pier(item_id, entity):
    s = sl.walk_and_close_door(item_id, 'pier')
    s.add_action(actions.SetWall('walkarea_0', 0, True))
    return s

def open_door_scummbar_kitchen(item_id, entity):
    cook: example.Wrap1 = example.get('cook')
    s = sl.walk_and_open_door(item_id, 'kitchen')
    if not cook.valid:
        s.add_action(actions.Msg(text=mopy.monkey.engine.read('$lines/32'), font='fonts.monkey', pos=(609, 78), color=mopy.monkey.engine.data.game.colors.cook_text))
        s.add_action(actions.Msg(text=mopy.monkey.engine.read('$lines/33'), font='fonts.monkey', pos=(609, 78), color=mopy.monkey.engine.data.game.colors.cook_text))
        s.add_action(actions.RunScript(sl.walk_and_close_door(item_id, 'kitchen')))
    else:
        # cook is in the kitchen
        if cook.x > 320:
            cook_upset(cook, s)
    return s

def cook_upset(cook, s):
    f = cook.flipx
    s.add_action(actions.SuspendScript(s='cook'))
    s.add_action(actions.Turn(tag='cook', dir='e'))
    s.add_action(actions.Say(lines=['$lines/32', '$lines/33'], tag='cook'))
    s.add_action(actions.Turn(tag='cook', dir='w'))
    s.add_action(actions.Animate(tag='cook', anim='walk_e', flipx=f))
    s.add_action(actions.ResumeScript(s='cook'))

def walkto_door_scummbar_kitchen(item_id, entity):
    cook: example.Wrap1 = example.get('cook')
    if cook.valid and cook.x > 320:
        s = sl.walk_to(item_id)
        cook_upset(cook, s)
        return s
    else:
        return sl.walk_to_door(item_id, 'kitchen', 'kitchen', mopy.monkey.engine.data.game.pos.kitchen_door, 'e')

def close_door_scummbar_village(item_id, entity):
    return sl.walk_and_close_door(item_id, 'scummbar')

def close_door_scummbar_kitchen(item_id, entity):
    return sl.walk_and_close_door(item_id, 'kitchen')

def walkto_door_scummbar_village(item_id, entity):
    return sl.walk_to_door(item_id, 'scummbar', 'village1', mopy.monkey.engine.data.game.pos.village_scummbar_door, 's')

def lookat_fireplace(item_id, entity):
    return sl.walk_and_say(item_id, ['$lines/3'])

def lookat_meat(item_id, e): return sl.walk_and_say(item_id, ['$lines/35'])
def lookat_pot(item_id, e): return sl.walk_and_say(item_id, ['$lines/36'])
def lookat_fish(item_id, e): return sl.walk_and_say(item_id, ['$lines/37'])
def lookat_barrel(item_id, e): return sl.walk_and_say(item_id, ['$lines/39'])
def lookat_scummbar_pirate_1(item_id, e): return sl.walk_and_say(item_id, ['$lines/5'])
def lookat_scummbar_pirate_4(item_id, e): return sl.walk_and_say(item_id, ['$lines/6'])
talkto_scummbar_pirate_4 = lookat_scummbar_pirate_4

def lookat_scummbar_mancomb(item_id, e):
    return sl.walk_and_change_room(item_id, 'mancomb')

talkto_scummbar_mancomb = lookat_scummbar_mancomb

def pickup_meat(item_id, e): return sl.walk_and_pickup(item_id, e)
def pickup_pot(item_id, e): return sl.walk_and_pickup(item_id, e)
def pickup_fish(item_id, e):
    data = mopy.monkey.engine.data
    if item_id in data.globals.inventory:
        return
    s = sl.walk_to(item_id)
    s.add_action(actions.Animate(tag='player', anim='kneel_s'))
    s.add_action(actions.Delay(sec=0.5))
    if data.game.seagull_on_plank:
        s.add_action(actions.Say(lines=['$lines/38'], tag='player'))
    else:
        s.add_action(actions.Animate(tag='player', anim='idle_s'))
        s.add_action(al.pickup_item(item_id, e.id))
        s.add_action(actions.SetVariable('game.fish_not_taken', False))
    example.play(s)


def on_kitchen_trap(player, entity, x ,y):
    example.remove(entity.id)
    s = Script()
    s.add_action(al.create_item('seagull'))
    s.add_action(actions.Animate(tag='seagull', anim='fly', sync=True))
    s.add_action(actions.Animate(tag='seagull', anim='eat'))
    s.add_action(actions.SetVariable("game.seagull_on_plank", True))
    example.play(s)

def cook_init_helper(s, id):
    s.add_action(actions.Delay(sec=5), id=id)
    s.add_action(al.open_door('door_scummbar_kitchen', 'kitchen'))
    s.add_action(al.create_item('cook', {'pos': mopy.monkey.engine.data.game.pos.scummbar_kitchen_door, 'dir': 'w'}, 'walkarea_0'))
    s.add_action(actions.Walk(tag='cook', pos=(115, 18)))
    s.add_action(actions.Turn(tag='cook', dir='n'))
    s.add_action(actions.Delay(sec=2))
    s.add_action(actions.Walk(tag='cook', pos=mopy.monkey.engine.data.game.pos.scummbar_kitchen_door))
    s.add_action(al.remove_item('cook'))
    s.add_action(al.close_door('door_scummbar_kitchen', 'kitchen'))
    # s.add_action(actions.CallFunc(f=a.Callbacks.add_item('cook', {'pos': '@pos/scummbar_kitchen_door', 'parent': 'walkarea_0'})))
    # s.add_action(scumm.actions.Walk(tag='cook', pos=(115, 18)))
    # s.add_action(scumm.actions.Turn(tag='cook', dir='n'))
    # s.add_action(actions.Delay(sec=2))
    # s.add_action(scumm.actions.Walk(tag='cook', pos=vars.pos.scummbar_kitchen_door))
    # s.add_action(actions.RemoveEntity(tag='cook'))
    # s.add_action(actions.Animate(tag='scummbar_kitchen_door', anim='closed'))

def anim_helper(tag):
    s1 = Script(loop=0, uid='_' + tag)
    s1.add_action(actions.DelayRandom(1.0, 5.0))
    s1.add_action(actions.Animate(tag=tag, anim='idle_2', sync=True))
    s1.add_action(actions.Animate(tag=tag, anim='idle_1'))
    example.play(s1)

def init_scummbar():
    if mopy.monkey.engine.previous_room == 'kitchen':
        s = Script(loop=100, uid='cook')
        s.add_action(al.create_item('cook', {'pos': (115, 18), 'dir': 'n'}, 'walkarea_0'))
        s.add_action(actions.Delay(sec=2))
        s.add_action(actions.Walk(tag='cook', pos=mopy.monkey.engine.data.game.pos.scummbar_kitchen_door))
        s.add_action(al.remove_item('cook'))
        s.add_action(al.close_door('door_scummbar_kitchen', 'kitchen'))
        cook_init_helper(s, 100)
        #
        # s.add_action(actions.CallFunc(f=a.Callbacks.add_item('cook', {'pos': (115, 18), 'parent': 'walkarea_0'})))
        # s.add_action(scumm.actions.Turn(tag='cook', dir='n'))
        # s.add_action(actions.Delay(sec=2))
        # s.add_action(scumm.actions.Walk(tag='cook', pos=vars.pos.scummbar_kitchen_door))
        # s.add_action(actions.RemoveEntity(tag='cook'))
        # s.add_action(actions.Animate(tag='scummbar_kitchen_door', anim='closed'))
        example.play(s)
    else:
        s = Script(loop=0, uid='cook')
        cook_init_helper(s, 0)
        example.play(s)

    anim_helper('scummbar_mancomb')
    anim_helper('scummbar_estevan')


def seagull_lands():
    s = Script()
    if 'fish' in mopy.monkey.engine.data.globals.inventory:
        s.add_action(actions.Animate(tag='seagull', anim='leave', sync=True))
        s.add_action(al.remove_item('seagull'))
    else:
        s.add_action(actions.Animate(tag='seagull', anim='eat'))
    example.play(s)

def pane(a,b,c):
    s = sl.walk_to('plank')
    s2 = Script()
    s2.add_action(actions.Animate(tag='player', anim='push_plank'))
    s2.add_action(actions.Delay(sec=0.3), id=1)
    s2.add_action(actions.Animate(tag='player', anim='idle_s'), after=[1])
    s2.add_action(actions.Animate(tag='plank', anim='pushed', sync=True), after=[1])
    s2.add_action(actions.Animate(tag='plank', anim='idle'))
    ss = example.get('seagull')
    if ss.valid:
        s2.add_action(actions.SetVariable("game.seagull_on_plank", False))
        s2.add_action(actions.Animate(tag='seagull', anim='jump' + str(mopy.monkey.engine.data.game.seagull_jump), sync=True))
        s2.add_action(actions.SetVariable("game.seagull_on_plank", True))
        s2.add_action(actions.CallFunc(f=seagull_lands))
        mopy.monkey.engine.data.game.seagull_jump = 2 if mopy.monkey.engine.data.game.seagull_jump == 1 else 1
    s.add_action(actions.RunScript(s2))
    example.play(s)