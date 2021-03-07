import example
import vars
import sys
import monkey
import script
import scumm.actions

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
    a = example.get('current_verb')
    verb = vars.verbs[vars.current_verb]
    text = monkey.engine.read(verb['text'])
    if vars.current_item_1:
        item = vars.items[vars.current_item_1]
        text += ' ' + monkey.engine.read(item['text'])
    a.setText(text)


def walkto(x, y):
    s = script.Script(uid='_main')
    s.add_action(scumm.actions.Walk(pos=[x, y], tag='player'))
    example.play(s)


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

def prova(e,x,y):
    print ('clicked here> ' + str(x) + ', ' + str(y))

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