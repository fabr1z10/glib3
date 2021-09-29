from script import Script

import example
import entity
import vars
import scumm.actions
import actions
import monkey
import func
import engine
import factories
import time
import status
import time

def make_lines(lines):
    return [monkey.engine.read(x) for x in lines]

def f_goto_room(room_id, pos, dir):
    def f():
        func.set_item_pos('guybrush', room_id, pos, dir)
    return f


def goto_room(s : Script, room_id, pos, dir):
    print(dir)
    s.add_action(actions.CallFunc(f=f_goto_room(room_id, pos, dir)))
    s.add_action(actions.ChangeRoom(room=room_id))


class GotoRoom(actions.CallFunc):
    def __init__(self, room_id, pos, dir):
        super().__init__(f=goto_room(room_id, pos, dir))

class Callbacks:
    def enable_controls(value):
        def f():
            main = example.get('main')
            ui = example.get('ui')
            if ui.valid:
                ui.setActive(value)
            main.enableControls(value)
        return f


    def set_pos(item_id, room, pos, dir):
        def f():
            func.set_item_pos(item_id, room, pos, dir)
        return f

    def set_door(id, var, value):
        def f():
            e = example.getById(id)
            e.setAnim(value)
            monkey.engine.set(var, value)
        return f

    def set_var(var, value):
        def f():
            monkey.engine.set(var, value)
        return f

    # add item dynamically
    def add_item(item_id, args):
        def f():
            dic = vars.items[item_id].copy()
            dic.update(args)
            tp = dic.get('type', None)
            if tp is None:
                print('item ' + item_id + ' does not have type!')
                exit(1)
            factory = getattr(factories.items, tp)
            e = factory()(item_id, dic)
            if e is not None:
                parent = dic.get('parent', 'main')
                example.get(parent).add(e)
        return f



    def pickup(id, entity_id):
        def f():
            #example.remove(entity_id)
            example.getById(entity_id).setActive(False)
            vars.inventory[id] = 1
            func.refresh_inventory()
        return f

    def pickup_no_remove(id, entity_id):
        def f():
            vars.inventory[id] = 1
            func.refresh_inventory()
        return f

    def rm_from_inventory(id):
        def f():
            print ('FOOOOSOODODOD')
            if id in vars.inventory:
                del vars.inventory[id]
                func.refresh_inventory()
        return f

    def add_to_inventory(id, qty):
        def f():
            if id not in vars.inventory:
                vars.inventory[id] = 0
            print('HEY ADDING '  + str(qty) + ' TO INV')
            vars.inventory[id] += qty
            func.refresh_inventory()

        return f

    def goto_room(room, pos, dir):
        def f():
            func.set_item_pos(vars.current_player, room, pos, dir)
        return f

    def set_item_text(item, text):
        def f():
            vars.items[item]['text']= text
        return f

class Scripts:
    # creates a script where player walks to an item and turns towards it
    def walk(id, script_id='_main'):
        s = Script(uid=script_id)
        has_item = vars.inventory.get(id, 0) > 0
        if not has_item:
            item = vars.items[id]
            wt = monkey.engine.read(item.get('walkto', None))
            if wt is not None:
                wdir = item.get('wdir', None)
                s.add_action(scumm.actions.Walk(pos=wt, tag='player'))
                if wdir is not None:
                    s.add_action(scumm.actions.Turn(dir=wdir, tag='player'))
        return s

    # creates a script where player walks towards an item, turns towards it
    # and say some lines
    def say(id, lines):
        s = Scripts.walk(id)
        lt = [monkey.engine.read(x) for x in lines]
        s.add_action(scumm.actions.Say(lines=lt, font='monkey', tag='player'))
        return s

    # creates a script where player walks and turns towards an item, picks it
    # up removing it from scene and adding it to inventory
    def pickup(id, entity_id):
        s = Scripts.walk(id)
        # when you pickup something
        s.add_action(actions.CallFunc(f=Callbacks.pickup(id, entity_id)))
        return s

    # creates a script where player walks and turns towards an item, picks it
    # up and adding it to inventory WITHOUT removing it from scene
    def pickup_no_remove(id, entity_id):
        s = ScriptFactory.walk(id)
        # when you pickup something
        s.add_action(actions.CallFunc(f=cf_pickup_no_remove(id, entity_id)))
        return s

    def set_door(value):
        def f(item_id, entity):
            s = Scripts.walk(item_id)
            aaa = vars.items[item_id]['anim']
            s.add_action(actions.CallFunc(f=Callbacks.set_door(entity.id, aaa, value)))
            return s
        return f

    def use_base(item1, item2):
        s = None
        if item1 in vars.inventory and item2 in vars.inventory:
            return Script('_main')
        if item1 in vars.inventory and item2 not in vars.inventory:
            s = Scripts.walk(item2)
        elif item2 in vars.inventory and item1 not in vars.inventory:
            s = Scripts.walk(item1)
        else:
            # you hold none. So try to see if you can pick up either
            pickup_item = item1
            other_item = item2
            f1 = func.get_script('pickup_' + str(item1))
            if f1 is None:
                pickup_item = item2
                other_item = item1
                f1 = func.get_script('pickup_' + str(item2))
            if f1:
                s = Scripts.pickup(pickup_item, example.get(pickup_item).id)
                s.add_action(actions.RunScript(Scripts.walk(other_item, None)))
        return s

def set_item_variable(item_id, var, value):
    if var in vars.items[item_id] and isinstance(vars.items[item_id][var], str):
        if vars.items[item_id][var][0] == '@':
            monkey.engine.set(vars.items[item_id][var], value)
        else:
            vars.items[item_id][var] = value

def openDoor(item_id, state):
    def f():
        example.get(item_id).setAnim(state)
        set_item_variable(item_id, 'anim', state)
    return f

class Actions:
    @staticmethod
    def walkto():
        def f(item_id, entity):
            s = Scripts.walk(item_id)
            example.play(s)
        return f

    # standard open door func
    @staticmethod
    def open_door():
        def f(item_id, entity):
            s = Scripts.walk(item_id)
            s.add_action(actions.CallFunc(f=openDoor(item_id, 'open')))
            example.play(s)
        return f

    @staticmethod
    def close_door():
        def f(item_id, entity):
            s = Scripts.walk(item_id)
            s.add_action(actions.CallFunc(f=openDoor(item_id, 'closed')))
            example.play(s)
        return f


    @staticmethod
    def say(lines):
        def f(item_id, entity):
            s = Scripts.say(item_id, lines)
            example.play(s)
        return f

    @staticmethod
    def set_door(value):
        def f(itemId, entity):
            s = Scripts.set_door(value)(itemId, entity)
            example.play(s)
        return f

    @staticmethod
    def walk_door(room, pos, dir):
        def f(item_id, entity):
            if example.get(item_id).anim == 'open':
                Actions.goto_room(room, pos, dir)(item_id, entity)
            else:
                s = Scripts.walk(item_id)
                example.play(s)
        return f

    @staticmethod
    def goto_room(room, pos, dir):
        def f(item_id, entity):
            print('HEY item = ' + item_id)
            s = Scripts.walk(item_id) if item_id else Script()
            s.add_action(actions.CallFunc(f=Callbacks.set_pos(vars.current_player, room, pos, dir)))
            s.add_action(actions.ChangeRoom(room=room))
            example.play(s)
        return f

    @staticmethod
    def start_dialogue(dialogue_id):
        def f(item_id, entity):
            s = Scripts.walk(item_id) if item_id else Script()
            s.add_action(scumm.actions.StartDialogue(dialogue_id=dialogue_id))
            example.play(s)
        return f



    @staticmethod
    def change_room(room):
        def f(item_id, entity):
            s = Scripts.walk(item_id) if item_id else Script()
            s.add_action(actions.ChangeRoom(room=room))
            example.play(s)
        return f

    @staticmethod
    def pickup():
        def f(item_id, entity):
            s = Scripts.pickup(item_id, entity.id)
            example.play(s)
        return f


class custom_actions_meta(type):
    @property
    def disable_controls(cls):
        return actions.CallFunc(f=Callbacks.enable_controls(False))

    @property
    def enable_controls(cls):
        return actions.CallFunc(f=Callbacks.enable_controls(True))

    def _set_timestamp(cls, var):
        def f():
            monkey.engine.set(var, time.time())
        return f


    def _update_item(cls, item_id, **kwargs):
        def f():
            dic = vars.items[item_id]
            if 'room' in kwargs:
                func.set_item_pos(item_id, kwargs.get('room'), kwargs.get('pos'), kwargs.get('dir',None) )
            for key, value in kwargs.items():
                dic[key] = value
        return f

    def _add_item(cls, item_id, args):
        def f():
            dic = vars.items[item_id].copy()
            dic.update(args)
            tp = dic.get('type', None)
            if tp is None:
                print('item ' + item_id + ' does not have type!')
                exit(1)
            factory = getattr(factories.items, tp)
            e = factory()(item_id, dic)
            if e is not None:
                parent = dic.get('parent', 'main')
                example.get(parent).add(e)
        return f

    def _remove_item(cls, item_id):
        def f():
            example.removeByTag(item_id)
        return f

    def add_item(cls, item_id, args=dict()):
        return actions.CallFunc(f=cls._add_item(item_id, args))

    def remove_item(cls, item_id):
        return actions.CallFunc(f=cls._remove_item(item_id))

    def add_to_inventory(cls, item_id, qty):
        return actions.CallFunc(f=Callbacks.add_to_inventory(item_id, qty))

    def rm_from_inventory(cls, item_id):
        return actions.CallFunc(f=Callbacks.rm_from_inventory(item_id))

    def update_item(cls, item_id, **kwargs):
        return actions.CallFunc(f=cls._update_item(item_id, **kwargs))

    def set_timestamp(cls, var):
        return actions.CallFunc(f=cls._set_timestamp(var))

    def goto_room(cls, room, pos, dir):
        return actions.CallFunc(f=Callbacks.goto_room(room, pos, dir))

class custom_actions(metaclass=custom_actions_meta):
    pass


            ######################################
# default actions
######################################
open_ = Actions.say(['$defaultactions/1'])
close_ = Actions.say(['$defaultactions/2'])
push_ = Actions.say(['$defaultactions/3'])
pull_ = Actions.say(['$defaultactions/3'])
lookat_ = Actions.say(['$defaultactions/4'])
pickup_ = Actions.say(['$defaultactions/5'])
use_ = Actions.say(['$defaultactions/2'])
give_ = Actions.say(['$defaultactions/2'])
talkto_ = Actions.say(['$defaultactions/2'])
walkto_ = Actions.walkto()


def chase_storekeeper_func(room):
    if func.is_in_room('storekeeper', room) and status.storekeeper_last_update:
        if time.time() - status.storekeeper_last_update > 10:
            print(' *** 10 sec have elapsed. chase failed.')
            # you have 10 seconds to chase storekeeper to next screen
            # otherwise storekeeper is reset into the store
            func.set_item_pos('storekeeper', 'store', (289, 7), 'w')
            vars.items['storekeeper']['parent'] = 'walkarea_1'
            vars.items['storekeeper']['size'] = (20, 40)
            status.storekeeper_last_update = None

def storekeeper_script(walk_to_pos, next_room, next_room_pos, next_room_dir, parent='walkarea_0'):
    if example.get('storekeeper').valid:
        s = Script()
        s.add_action(scumm.actions.Walk(tag='storekeeper', pos=walk_to_pos))
        s.add_action(actions.SetActive(tag='storekeeper', value=False))
        s.add_action(custom_actions.update_item(item_id='storekeeper', room=next_room, pos=next_room_pos, dir=next_room_dir,
            parent=parent, size=None))
        s.add_action(custom_actions.set_timestamp('@storekeeper_last_update'))
        example.play(s)


