import example
import vars
import sys
import monkey
import script
import scumm.actions
import scripts.actions

def set_item_pos(item_id, room, pos, dir = None):
    item = vars.items[item_id]
    old_room = item['room']
    item['room'] = room
    item['pos'] = pos
    if dir:
        item['dir'] = dir
    if old_room != room:
        vars.items_in_room[old_room].remove(item_id)
        if room not in vars.items_in_room:
            vars.items_in_room[room] = set()
        vars.items_in_room[room].add(item_id)

def get_script(str):
    return getattr(scripts.actions, str, None)


def change_color(color):
    def f(e: example.Wrap1):
        e.setColor([0, 0, 0, 0], color)
    return f


def on_verb_click(verb_id):
    def f(e: example.Wrap1, x, y):
        print('clicked on ' + verb_id)
        verb = vars.verbs[verb_id]
        callback = verb.get('callback', 'set_verb')
        getattr(sys.modules[__name__], callback)(verb_id)
    return f


def set_verb(verb_id):
    vars.current_verb = verb_id
    vars.current_item_1 = ''
    vars.current_item_2 = ''
    vars.wait_for_second_item = False
    update_current_action()


def update_current_action():
    print ('IPDDAA')
    a = example.get('current_verb')
    verb = vars.verbs[vars.current_verb]
    text = monkey.engine.read(verb['text'])
    if vars.current_item_1:
        item = vars.items[vars.current_item_1]
        text += ' ' + monkey.engine.read(item['text'])
    if verb['items'] == 2:
        if vars.wait_for_second_item:
            text += ' ' + monkey.engine.read(verb['prep'])
            if vars.current_item_2:
                item2 = vars.items[vars.current_item_2]
                text += ' ' + monkey.engine.read(item2['text'])
    a.setText(text)


def walkto(x, y):
    s = script.Script(uid='_main')
    s.add_action(scumm.actions.Walk(pos=[x, y], tag='player'))
    example.play(s)


def hover_on_inventory_button(item):
    def f(e: example.Wrap1):
        e.setColor([0, 0, 0, 0], vars.Colors.inv_selected)
        hover_on(item)(e)
    return f


def hover_off_inventory_button(item):
    def f(e: example.Wrap1):
        e.setColor([0, 0, 0, 0], vars.Colors.inv_unselected)
        hover_off(e)(None)
    return f


def hover_on(obj):
    def f(item):
        print (obj)
        if not vars.current_item_1:
            vars.current_item_1 = obj
        else:
            # if this verb takes 2 objects...
            if vars.verbs[vars.current_verb]['items'] > 1 and vars.current_item_1 != obj:
                vars.current_item_2 = obj
        update_current_action()
    return f

def prova():
    def f(x, y, item):
        print('current verb: ' + str(vars.current_verb))
        print('object      : ' + vars.current_item_1)
        print('second obj  : ' + vars.current_item_2)
        if vars.current_item_2 == '':
            # see if I have a callback of form <verb>_<object>
            f1 = vars.current_verb + '_' + vars.current_item_1
            fc = getattr(scripts.actions, f1, None)
            if fc is None:
                # if verb takes two objects, wait for 2nd object
                if vars.verbs[vars.current_verb]['items'] == 2:
                    print ('xxx')
                    vars.wait_for_second_item = True
                    update_current_action()
                else:
                    f2 = vars.current_verb + '_'
                    fc = getattr(scripts.actions, f2, None)
            if fc:
                fc(vars.current_item_1, item)
        else:
            f1 = vars.current_verb + '_' + vars.current_item_1 + '_' + vars.current_item_2
            fc = getattr(scripts.actions, f1, None)
            if fc is None:
                # try flipping the objects
                f1 = vars.current_verb + '_' + vars.current_item_2 + '_' + vars.current_item_1
                fc = getattr(scripts.actions, f1, None)
                if fc:
                    fc(vars.current_item_2, vars.current_item_1)
                else:
                    f2 = vars.current_verb + '_'
                    fc = getattr(scripts.actions, f2, None)
                    if fc:
                        fc(vars.current_item_2, item)
            else:
                fc(vars.current_item_1, vars.current_item_2)

    return f


def refresh_inventory():
    p = example.get('inventory')
    if p.valid:
        p.clearText()
        for k, v in vars.inventory.items():
            print (k + ' --- ' +str(v))
            p.appendText((k, v))
            print ('fmerda')

    #
    # if p.valid:
    #     inv = State.getCurrentInventory()
    #     p.clearText()
    #     for key, value in inv.items():
    #         p.appendText ((key, value))

def hover_off(obj):
    def f(item):
        if vars.current_item_2:
            vars.current_item_2 = ''
        else:
            # set obj1 to nil unless we are waiting for 2nd object
            if vars.verbs[vars.current_verb]['items'] == 1:
                vars.current_item_1 = ''
        update_current_action()
    return f

def on_enter_trap(player, trap, dx, dy):
    f = trap.getInfo().get('func')
    print('ciappo!' + str(f))
    if f:
        getattr(scripts.actions, f)(trap)
