import example
import vars
import sys
import monkey
import script
import scumm.actions
import actions
import entity
import scripts.actions
import components as compo


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

def change_player(new_player):
    def f(e,x,y):
        new_model = vars.player_info[new_player]
        if new_model == vars.current_player:
            ui2 = example.get('ui2')
            example.get('ui').setActive(True)
            ui2.clear()
            ui2.setActive(False)
        else:
            # save position of current player
            player = example.get('player')
            vars.items[vars.current_player]['pos'] = [player.x, player.y]
            dir = player.anim[-1]
            if dir == 'e' and player.flipx:
                dir ='w'
            vars.items[vars.current_player]['dir'] = dir
            # get next room
            vars.current_player = new_model
            s = script.Script()
            s.add_action(actions.ChangeRoom(room=vars.items[new_model]['room']))
            example.play(s)
    return f

def on_new_kid_pressed(verb_id):
    example.get('ui').setActive(False)
    ui2 = example.get('ui2')
    ui2.setActive(True)
    dx = 320.0 / (1 + len(vars.players))
    i=1
    for p in vars.players:
        e = entity.Text(font='ui', size=8, text=p, color=vars.Colors.verb_unselected, align=entity.TextAlignment.center, pos=(dx*i, vars.ui_height/2.0))
        e.add_component(compo.HotSpot(shape=None, onenter=change_color(vars.Colors.verb_selected), onleave=change_color(vars.Colors.verb_unselected),
                                    onclick=change_player(p)))
        i += 1
        ui2.add(e)

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
        print(dir(scripts.actions))
        if vars.current_item_2 == '':
            # see if I have a callback of form <verb>_<object>
            f1 = vars.current_verb + '_' + vars.current_item_1
            print('check if I have: ' + f1)

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
                    if fc is None:
                        print ('not found: ' + f2)
            if fc:
                fc(vars.current_item_1, item)
        else:
            f1 = vars.current_verb + '_' + vars.current_item_1 + '_' + vars.current_item_2
            print('check if ' + f1 + ' exists.')
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
        # get inventory of currnet player
        inve = vars.inventory[vars.current_player]
        for k, v in inve.items():
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



def execute_dialogue_script(l):
    def f(x, y, z):
        line = l.line
        dialogue = vars.dialogues[l.dialogue_id]
        set_text = dialogue['text_set']
        if 'activate' in line:
            for node in line['activate']:
                dialogue['lines'][node]['active'] = True
        if 'deactivate' in line:
            for node in line['deactivate']:
                dialogue['lines'][node]['active'] = False
        persist = line.get('persist', False)
        if not persist:
            line['active'] = False
        if 'scr' in line:
            s = script.Script()
            s.add_action(scumm.actions.HideDialogue())
            for a in line['scr']:
                id = a[0]
                after = a[1]
                if id == 0:
                    after = None
                if isinstance(after, int):
                    after = [after]
                action = a[2]
                if action == 'say':
                    ts1 = [str(y) for y in a[4:]]
                    s.add_action(scumm.actions.Say(tag=a[3], font='monkey', lines=[monkey.engine.read(x if x[0]=='$' else set_text+'/'+x) for x in ts1]), id=id, after=after)
                elif action == 'sayn':
                    ts1 = [str(y) for y in a[4:]]
                    s.add_action(scumm.actions.Say(animate=False, tag=a[3], font='monkey', lines=[monkey.engine.read(x if x[0]=='$' else set_text+'/'+x) for x in ts1]), id=id, after=after)
                elif action == 'set':
                    s.add_action(actions.SetVariable(a[3], a[4]))
                elif action == 'set_dialogue_root':
                    s.add_action(scumm.actions.SetDialogueRoot(a[3], a[4]))
            if 'next' in line:
                s.add_action(scumm.actions.StartDialogue(l.dialogue_id, line['next']))
            else:
                # check if dialogue has a on_exit script
                if 'on_exit' in dialogue:
                    s.add_action(actions.CallFunc(f=getattr(scripts.actions, dialogue['on_exit'])))
                else:
                    s.add_action(scumm.actions.ExitDialogue())
            example.play(s)
    return f