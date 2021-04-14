from script import Script
import engine
import example
import random
import actions
import vars

def start_dialogue(dialogue_id):
    def f():
        example.get('main').enableControls(False)
        example.get('ui').setActive(False)
        example.get('inventory').setActive(False)
        dial = example.get('dialogue')
        dial.setActive(True)
        dial.clearText()
        start_node = 'root'
        dialogue = vars.dialogues[dialogue_id]
        #tset = dialogue['text_set']
        node = dialogue['nodes'][start_node]
        lines = dialogue['lines']
        for l in node['lines']:
            dial.appendText([dialogue_id, lines[l]])
    return f

def restart_dialogue(dialogue_id, node_id):
    def f():
        dial = example.get('dialogue')
        dial.setActive(True)
        dial.clearText()
        dialogue = vars.dialogues[dialogue_id]
        node = dialogue['nodes'][node_id]
        lines = dialogue['lines']
        for l in node['lines']:
            dial.appendText([dialogue_id, lines[l]])
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

class StartDialogue(actions.CallFunc):
    def __init__(self, dialogue_id):
        super().__init__(f=start_dialogue(dialogue_id))

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
    def __init__(self, pos : list, id = None, tag = None):
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

