import mopy
import example
from mopy.entity import Text, TextAlignment
from mopy.components import HotSpot
from mopy.script import Script
from mopy.actions import RunScript
from mopy.scumm.actionlib import enable_controls, start_dialogue

def change_color(color):
    def f(e: example.Wrap1):
        e.setColor(color, (0, 0, 0, 0))
    return f


def update_current_action():
    items = mopy.monkey.engine.data.items
    gl = mopy.monkey.engine.data.globals
    a = example.get('current_verb')
    verb = gl.verbs[gl.current_verb]
    text = mopy.monkey.engine.read(verb['text'])
    if gl.current_item_1:
        item = items[gl.current_item_1]
        text += ' ' + mopy.monkey.engine.read(item['text'])
    if verb['items'] == 2:
        if gl.wait_for_second_item:
            text += ' ' + mopy.monkey.engine.read(verb['prep'])
            if gl.current_item_2:
                item2 = items[gl.current_item_2]
                text += ' ' + mopy.monkey.engine.read(item2['text'])
    a.setText(text)


def set_verb_2(verb_id, item_id):
    gl = mopy.monkey.engine.data.globals
    gl.current_verb = verb_id
    gl.current_item_1 = item_id
    gl.current_item_2 = ''
    gl.wait_for_second_item = False
    update_current_action()

# called when hovering over an item
def hover_on(obj):
    def f(item):
        gl = mopy.monkey.engine.data.globals
        if not gl.current_item_1:
            gl.current_item_1 = obj
        else:
            # if this verb takes 2 objects...
            if gl.verbs[gl.current_verb]['items'] > 1 and gl.current_item_1 != obj:
                gl.current_item_2 = obj
        update_current_action()
    return f


def hover_off(obj):
    def f(item):
        gl = mopy.monkey.engine.data.globals
        if gl.current_item_2:
            gl.current_item_2 = ''
        else:
            # set obj1 to nil unless we are waiting for 2nd object
            if gl.verbs[gl.current_verb]['items'] == 1:
                gl.current_item_1 = ''
        update_current_action()
    return f


def hover_on_inventory_button(item):
    def f(e: example.Wrap1):
        gl = mopy.monkey.engine.data.globals
        e.setColor(gl.Colors.inv_selected, (0, 0, 0, 0))
        hover_on(item)(e)
    return f


def hover_off_inventory_button(item):
    def f(e: example.Wrap1):
        gl = mopy.monkey.engine.data.globals
        e.setColor(gl.Colors.inv_unselected, (0, 0, 0, 0))
        hover_off(e)(None)
    return f


def on_verb_click(verb_id):
    def f(e: example.Wrap1, x, y):
        gl = mopy.monkey.engine.data.globals
        verb = gl.verbs[verb_id]
        callback = verb.get('callback', None)
        if not callback:
            gl.current_verb = verb_id
            gl.current_item_1 = ''
            gl.current_item_2 = ''
            gl.wait_for_second_item = False
            update_current_action()
        else:
            pass
            #getattr(sys.modules[__name__], callback)(verb_id)
    return f

# executes a dialogue script
def exec_script(s):
    def f(x, y, z):
        scr = s.script
        if 'activate' in s.line:
            for node in s.line['activate']:
                s.dialogue['lines'][node]['active'] = True
        if 'deactivate' in s.line:
            for node in s.line['deactivate']:
                s.dialogue['lines'][node]['active'] = False
        persist = s.line.get('persist', False)
        if not persist:
            s.line['active'] = False
        s1 = Script()
        s1.add(enable_controls(False))
        example.get('dialogue').clearText()
        s.line["clicked"] = s.line.get("clicked", 0) + 1
        if isinstance(scr, str):
            fc = getattr(mopy.monkey.engine.data.scripts, scr, None)
            if fc:
                args = s.line.get('args', [])
                s1.add_action(RunScript(fc(args)))
        next = s.line.get('next')
        if next:
            s1.add_action(start_dialogue(s.dialogue_id, True, next))
        else:
            # check if dialogue has a on_exit script
            on_exit = s.dialogue.get('on_exit')
            if on_exit:
                on_exit_script = getattr(mopy.monkey.engine.data.scripts, on_exit)()
                if on_exit_script:
                    s1.add(RunScript(on_exit_script))
            else:
                pass
                #s.add_action(scumm.actions.ExitDialogue())
        example.play(s1)
    return f

def run_action():
    def f(x, y, item):
        scripts = mopy.monkey.engine.data.scripts
        items = mopy.monkey.engine.data.items
        gl = mopy.monkey.engine.data.globals
        print('current verb: ' + str(gl.current_verb))
        print('object      : ' + gl.current_item_1)
        print('second obj  : ' + gl.current_item_2)
        script = None
        if gl.current_item_2 == '':
            # see if I have a callback of form <verb>_<object>
            f1 = (gl.current_verb + '_' + gl.current_item_1).replace('.', '_')
            fc = getattr(scripts, f1, None)
            if fc is None:
                print(f1 + ' not found')
                # if verb takes two objects, wait for 2nd object
                if gl.verbs[gl.current_verb]['items'] == 2:
                    gl.wait_for_second_item = True
                    update_current_action()
                else:
                    f2 = gl.current_verb + '_'
                    fc = getattr(scripts, f2, None)
                    if fc is None:
                        print ('not found: ' + f2)
            if fc:
                script = fc(gl.current_item_1, item)
            set_verb_2('walkto', gl.current_item_1)
        else:
            f1 = gl.current_verb + '_' + gl.current_item_1 + '_' + gl.current_item_2
            fc = getattr(scripts, f1.replace('.', '_'), None)
            if fc is None:
                # try flipping the objects
                f1 = gl.current_verb + '_' + gl.current_item_2 + '_' + gl.current_item_1
                fc = getattr(scripts, f1.replace('.', '_'), None)
                if fc:
                    script = fc(gl.current_item_2, gl.current_item_1)
                else:
                    f2 = gl.current_verb + '_'
                    fc = getattr(scripts, f2, None)
                    if fc:
                        script = fc(gl.current_item_2, item)
            else:
                script = fc(gl.current_item_1, gl.current_item_2)
        if script:
            example.play(script)
    return f

def make_verb_button(verb_id: str, pos):
    gl = mopy.monkey.engine.data.globals
    verb = gl.verbs[verb_id]
    e = Text(font=gl.ui_font, size=gl.font_size, text=mopy.monkey.engine.read(verb['text']),
             color=gl.Colors.verb_unselected, align=TextAlignment.bottom_left, pos=pos)
    e.add_component(HotSpot(shape=None, onenter=change_color(gl.Colors.verb_selected), onleave=change_color(gl.Colors.verb_unselected),
                            onclick=on_verb_click(verb_id)))
    return e


def make_inventory_button(item):
    items = mopy.monkey.engine.data.items
    gl = mopy.monkey.engine.data.globals
    qty = gl.inventory[item]['qty']
    text = mopy.monkey.engine.read(item['text']) if qty == 1 else str(qty) + ' ' + mopy.monkey.engine.read(item['plural'])
    e = Text(font=gl.ui_font, size=gl.font_size, text=text, color=gl.Colors.inv_unselected, align=TextAlignment.bottom_left)
    e.add_component(HotSpot(shape=None, onenter=hover_on_inventory_button(item), onleave=hover_off_inventory_button(item),
                            onclick=run_action()))
    return e


def make_dialogue_button(dialogue_line):
    gl = mopy.monkey.engine.data.globals
    e = Text(font=gl.ui_font, size=gl.font_size, text=dialogue_line.get_text(), color=gl.Colors.verb_unselected,
             align=TextAlignment.bottom_left)
    e.add_component(HotSpot(shape=None, onenter=change_color(gl.Colors.verb_selected), onleave=change_color(gl.Colors.verb_unselected),
                            onclick=exec_script(dialogue_line)))
    return e
