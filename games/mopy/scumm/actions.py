from mopy.script import Script
import mopy.engine as engine
import example
import random
import mopy.actions as actions
import mopy.monkey as monkey

class DialogueLine:
    def __init__(self, current_node, order, dialogue_id, line):
        self.order = order
        self.dialogue_id = dialogue_id
        self.line = line
        self.text_set = monkey.engine.data.dialogues[dialogue_id]['text_set']
        self.current_node = current_node

    def __lt__(self, other):
        return self.order < other.order


    def get_text(self):
        a = str(self.line['text'])
        line = monkey.engine.read(a if a[0]=='$' else self.text_set + '/' + a)
        return line


def enable_ui(value):
    def f():
        example.get('main').enableControls(value)
        example.get('ui').setActive(value)
        example.get('inventory').setActive(value)
    return f


def init_dialogue(dialogue_id, node_id = None):
    def f():
        dialogue = vars.dialogues[dialogue_id]
        start_node = node_id if node_id is not None else dialogue.get('root', 'root')
        #tset = dialogue['text_set']
        node = dialogue['nodes'][start_node]
        lines = dialogue['lines']
        ll = []
        for l in node['lines']:
            active = monkey.engine.read(lines[l].get('active', True))
            #active = lines[l].get('active', True)
            if active:
                order = lines[l].get('order', 0)
                ll.append(DialogueLine(node, order, dialogue_id, lines[l]))
        ll.sort()
        dial = example.get('dialogue')
        for dl in ll:
            dial.appendText(dl)
    return f

def start_dialogue(dialogue_id, node_id = None, continue_dialogue = False):
    def f():
        example.get('main').enableControls(False)
        example.get('ui').setActive(False)
        example.get('inventory').setActive(False)
        dial = example.get('dialogue')
        dial.setActive(True)
        dial.clearText()
        dialogue = monkey.engine.data.dialogues[dialogue_id]
        if (not continue_dialogue) and 'on_entry' in dialogue:
            getattr(monkey.engine.scripts, dialogue['on_entry'])()
            return
        start_node = node_id if node_id is not None else dialogue.get('root', 'root')
        #tset = dialogue['text_set']
        node = dialogue['nodes'][start_node]
        lines = dialogue['lines']
        ll = []
        for l in node['lines']:
            active = monkey.engine.read(lines[l].get('active', True))
            #active = lines[l].get('active', True)
            if active:
                order = lines[l].get('order', 0)
                ll.append(DialogueLine(node, order, dialogue_id, lines[l]))
        ll.sort()
        for dl in ll:
            dial.appendText(dl)
        # what if ll is empty?
        if not ll and 'on_empty' in dialogue:
            getattr(monkey.engine.scripts, dialogue['on_empty'])()

    return f




def hide_dialogue():
    dial = example.get('dialogue')
    dial.setActive(False)

def exit_dialogue():
    example.get('main').enableControls(True)
    example.get('ui').setActive(True)
    example.get('inventory').setActive(True)
    dial = example.get('dialogue')
    dial.clearText()
    dial.setActive(False)
    start_node = 'root'

def set_dialogue_root(dialogue_id, node_id):
    def f():
        vars.dialogues[dialogue_id]['root'] = node_id
    return f


class EnableUI(actions.CallFunc):
    def __init__(self, value):
        super().__init__(f=enable_ui(value))


class SetDialogueRoot(actions.CallFunc):
    def __init__(self, dialogue_id, node_id):
        super().__init__(f=set_dialogue_root(dialogue_id, node_id))

class StartDialogue(actions.CallFunc):
    def __init__(self, dialogue_id, node_id = None, continue_dialogue=False):
        super().__init__(f=start_dialogue(dialogue_id, node_id, continue_dialogue))

class InitDialogue(actions.CallFunc):
    def __init__(self, dialogue_id, node_id = None):
        super().__init__(f=init_dialogue(dialogue_id, node_id))


class HideDialogue(actions.CallFunc):
    def __init__(self):
        super().__init__(f=hide_dialogue)

class ExitDialogue(actions.CallFunc):
    def __init__(self):
        super().__init__(f=exit_dialogue)



class RestartDialogue(actions.CallFunc):
    def __init__(self, dialogue_id, node):
        super().__init__(f=restart_dialogue(dialogue_id, node))

class Walk:
    def __init__(self, pos, id = None, tag = None):
        self.type = 'scumm.action.walk'
        self.id = id
        self.tag = tag
        self.pos = pos

class Turn:
    def __init__(self, dir : str, id = None, tag = None):
        self.type = 'scumm.action.turn'
        self.id = id
        self.tag = tag
        self.dir = dir


class Say:
    def __init__(self, lines: list, font: str, id = None, tag = None, animate = True):
        self.type = 'scumm.action.say'
        self.font = font
        self.id = id
        self.tag = tag
        self.lines = lines
        self.animate = animate

class SetWall:
    def __init__(self, walkarea: str, wall_id: int, enabled: bool):
        self.type = 'scumm.action.enable_block'
        self.walkarea = walkarea
        self.wall = wall_id
        self.active = enabled

