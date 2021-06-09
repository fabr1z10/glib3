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


class Callbacks:
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
            example.remove(entity_id)
            vars.inventory[vars.current_player][id] = 1
            func.refresh_inventory()
        return f

    def pickup_no_remove(id, entity_id):
        def f():
            vars.inventory[id] = 1
            func.refresh_inventory()
        return f

    def rm_from_inventory(id):
        def f():
            if id in vars.inventory:
                del vars.inventory[id]
                func.refresh_inventory()
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

class Actions:
    @staticmethod
    def walkto():
        def f(item_id, entity):
            s = Scripts.walk(item_id)
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
    def walk_door():
        def f(item_id, entity):
            s = Scripts.walk(item_id)
            anim = monkey.engine.read(vars.items[item_id]['anim'])
            print ('CIAO ' + anim)
            if anim == 'open':
                nroom = vars.items[item_id]['next_room']
                next_room = monkey.engine.read(nroom[0])
                new_pos = monkey.engine.read(nroom[1])
                new_dir = nroom[2]
                func.set_item_pos(vars.current_player, next_room, new_pos, new_dir)
                s.add_action(actions.ChangeRoom(room = next_room))
            example.play(s)
        return f

    @staticmethod
    def pickup():
        def f(item_id, entity):
            s = Scripts.pickup(item_id, entity.id)
            example.play(s)
        return f

    @staticmethod
    def goto_room(room, pos, dir):
        def f(item_id, entity):
            s = Scripts.walk(item_id)
            s.add_action(actions.CallFunc(f=Callbacks.set_pos(vars.current_player, room, pos, dir)))
            s.add_action(actions.ChangeRoom(room=room))
            example.play(s)
        return f

######################################
# default actions
######################################
open_ = Actions.say(['$defaultactions/1'])
close_ = Actions.say(['$defaultactions/2'])
push_ = Actions.say(['$defaultactions/3'])
pull_ = Actions.say(['$defaultactions/3'])
lookat_ = Actions.say(['$defaultactions/4'])
pickup_ = Actions.say(['$defaultactions/5'])
read_ = Actions.say(['$defaultactions/6'])
use_ = Actions.say(['$defaultactions/2'])
walkto_ = Actions.walkto()





