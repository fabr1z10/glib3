import scripts.actions.shared as a
import scumm.actions
import example
import entity
from script import Script
import actions
import status
import monkey
import vars

# one-object actions
lookat_meat = a.Actions.say(['$lines/35'])
lookat_pot = a.Actions.say(['$lines/36'])
lookat_fish = a.Actions.say(['$lines/37'])
lookat_barrel = a.Actions.say(['$lines/39'])


def lookat_potostew(item, id):
    lines = ['$lines/' + ('41' if status.meat_in_pot else '40')]
    a.Actions.say(lines)(item, id)


def pickup_potostew(item, id):
    if status.meat_in_pot:
        vars.items['meat']['text'] = '$objects/stewed_meat_2'
        vars.items['potostew']['text'] = '$objects/potostew'
        s = a.Scripts.walk(item)
        s.add_action(actions.CallFunc(f=a.Callbacks.pickup_no_remove('meat', id)))
        example.play(s)
    else:
        a.pickup_(item, id)

pickup_meat = a.Actions.pickup()
pickup_pot = a.Actions.pickup()


def use_meat_potostew(item1, item2):
    s = a.Scripts.use_base(item1, item2)
    # do whatever else u need to do
    s.add_action(actions.CallFunc(f=a.Callbacks.rm_from_inventory(item1)))
    s.add_action(actions.CallFunc(f=a.Callbacks.set_item_text(item2, '$objects/stewed_meat')))
    s.add_action(actions.CallFunc(f=a.Callbacks.set_var('@meat_in_pot', True)))
    example.play(s)



def on_click_plank(x, y, pippo):
    s = a.Scripts.walk('plank')
    s2 = Script()
    s2.add_action(actions.Animate(tag='player', anim='push_plank'))
    s2.add_action(actions.Delay(sec=0.3), id=1)
    s2.add_action(actions.Animate(tag='player', anim='idle_s'), after=[1])
    s2.add_action(actions.Animate(tag='plank', anim='pushed', sync=True), after=[1])
    s2.add_action(actions.Animate(tag='plank', anim='idle'))
    s2.add_action(actions.CallFunc(f=a.Callbacks.set_var("@seagull_on_plank", False)), after=[1])
    s2.add_action(actions.Animate(tag='seagull', anim='jump' + str(status.seagull_jump), sync=True))
    s2.add_action(actions.CallFunc(f=a.Callbacks.set_var("@seagull_on_plank", True)))
    s2.add_action(actions.Animate(tag='seagull', anim='eat'))
    status.seagull_jump = 2 if status.seagull_jump == 1 else 1
    s.add_action(actions.RunScript(s2))
    example.play(s)


def pickup_fish(item_id, entity):
    if item_id in vars.inventory:
        return
    s = a.Scripts.walk(item_id)
    s.add_action(actions.Animate(tag='player', anim='kneel_s'))
    s.add_action(actions.Delay(sec=0.5))
    if status.seagull_on_plank:
        s.add_action(scumm.actions.Say(lines=[monkey.engine.read(x) for x in ['$lines/38']], font='monkey', tag='player'))
    else:
        s.add_action(actions.Animate(tag='player', anim='idle_s'))
        s.add_action(actions.CallFunc(f=a.Callbacks.pickup(item_id, entity.id)))
    example.play(s)


open_kitchen_door = a.Actions.set_door('open')
close_kitchen_door = a.Actions.set_door('closed')
walkto_kitchen_door = a.Actions.walk_door()

def on_kitchen_trap(trap):
    example.remove(trap.id)
    s = entity.Sprite(model='01/seagull', tag='seagull',pos=[0, 0, 1])
    id = example.get('main').add(s)
    script = Script()
    script.add_action(actions.Animate(entity_id=id, anim='fly', sync=True))
    script.add_action(actions.Animate(entity_id=id, anim='eat'))
    script.add_action(actions.CallFunc(f=a.Callbacks.set_var("@seagull_on_plank", True)))
    example.play(script)


def open_kitchen_door_pier(item_id, entity):
    s = a.Scripts.set_door('open')(item_id, entity)
    s.add_action(scumm.actions.SetWall('walkarea_0', 0, False))
    example.play(s)


def close_kitchen_door_pier(item_id, entity):
    s = a.Scripts.set_door('closed')(item_id, entity)
    s.add_action(scumm.actions.SetWall('walkarea_0', 0, True))
    example.play(s)