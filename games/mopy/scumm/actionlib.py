import example
import mopy
from mopy.script import Script
from mopy.scumm.shortcut import get_item





class DialogueLine:
    def __init__(self, line, dialogue, dialogue_id):
        self.order = line.get('order', 0)
        self.text_set = dialogue['text_set']
        self.line = line
        self.script = line.get('script')
        self.dialogue_id = dialogue_id
        self.dialogue = dialogue
        #self.current_node = current_node

    def __lt__(self, other):
        return self.order < other.order

    def get_text(self):
        a = str(self.line['text'])
        line = mopy.monkey.engine.read(a if a[0]=='$' else self.text_set + '/' + a)
        return line

    def get_script(self):
        return self.script


def _helper(f):
    return {
        'type': 'action.callfunc',
        'func': f
    }


def _enable_controls(value):
    def f():
        example.get('main').enableControls(value)
        example.get('ui').setActive(value)
        example.get('inventory').setActive(value)
        example.get('dialogue').setActive(value)
    return f


def _sierra_enable_controls(value):
    def f():
        example.get('main').enableControls(value)
    return f


def log(msg):
    def _print():
        print(msg)
    return _helper(_print)


def enable_controls(value):
    return _helper(_enable_controls(value))

def sierra_enable_controls(value):
    return _helper(_sierra_enable_controls(value))

def _display_dialogue(did, dialogue, start_node):
    def f():
        node = dialogue['nodes'][start_node]
        lines = dialogue['lines']
        ll = []
        for l in node['lines']:
            line = lines[l]
            active = mopy.monkey.engine.read(line.get('active', True))
            if active:
                ll.append(DialogueLine(line, dialogue, did))
        ll.sort()
        dial = example.get('dialogue')
        dial.setActive(True)
        dial.clearText()
        for dl in ll:
            dial.appendText(dl)
    return f


def exit_dialogue():
    def _exit_dialogue():
        _enable_controls(True)()
    return _helper(_exit_dialogue)


def set_variable(variable, value):
    def _set_variable():
        setattr(mopy.monkey.engine.data.game, variable, value)
    return _helper(_set_variable)

def set_text(entity, txt):
    def _set_text():
        example.get(entity).setText(txt)

    return _helper(_set_text)



def start_dialogue(dialogue_id, continue_dialogue, start_node = 'root'):
    def _start_dialogue():
        _enable_controls(False)()
        dialogue = mopy.monkey.engine.data.dialogues.get(dialogue_id)
        if not dialogue:
            print('## warning! dialogue ' + dialogue_id + ' does not exist')
            return
        s = Script()
        if (not continue_dialogue) and 'on_entry' in dialogue:
            s = getattr(mopy.monkey.engine.data.scripts, dialogue['on_entry'])()
        s.add_action({'type': 'action.callfunc', 'func': _display_dialogue(dialogue_id, dialogue, start_node)})
        example.play(s)
        # start_node = node_id if node_id is not None else dialogue.get('root', 'root')
        # #tset = dialogue['text_set']
        # node = dialogue['nodes'][start_node]
        # lines = dialogue['lines']
        # ll = []
        # for l in node['lines']:
        #     active = monkey.engine.read(lines[l].get('active', True))
        #     #active = lines[l].get('active', True)
        #     if active:
        #         order = lines[l].get('order', 0)
        #         ll.append(DialogueLine(node, order, dialogue_id, lines[l]))
        # ll.sort()
        # for dl in ll:
        #     dial.appendText(dl)
        # # what if ll is empty?
        # if not ll and 'on_empty' in dialogue:
        #     getattr(monkey.engine.scripts, dialogue['on_empty'])()
    return _helper(_start_dialogue)


def create_item(item_id, args=dict(), parent='main'):
    def _create_item():
        from mopy.factories.scumm_item import create_dynamic_wa
        pippo = create_dynamic_wa(item_id, args)
        pa = example.get(parent)
        pa.add(pippo)
    return _helper(_create_item)

def remove_item(item_id):
    def _remove_item():
        example.removeByTag(item_id)
    return _helper(_remove_item)



def open_door(item_id, door_id):
    def _open_door():
        setattr(mopy.monkey.engine.data.game.doors, door_id, 'open')
        example.get(item_id).setAnim('open')
    return _helper(_open_door)

def close_door(item_id, door_id):
    def _close_door():
        setattr(mopy.monkey.engine.data.game.doors, door_id, 'closed')
        example.get(item_id).setAnim('closed')
    return _helper(_close_door)


def update_item(item_id, d: dict):
    def _set_item_pos():
        data = mopy.monkey.engine.data
        item = data.items[item_id]
        if 'room' in d and d['room'] != item.get('room'):
            old_room = item.get('room')
            if old_room:
                data.r2i[old_room].remove(item_id)
            data.r2i[d['room']].append(item_id)
            data.i2r[item_id] = d['room']
            print('scopami')
            print(data.r2i)
        item.update(d)

    return _helper(_set_item_pos)


def pickup_item(item_id, id):
    from mopy.factories.interface import refresh_inventory
    def _pickup_item():
        example.getById(id).setActive(False)
        data = mopy.monkey.engine.data.globals
        data.inventory[item_id] = 1
        refresh_inventory()
    return _helper(_pickup_item)