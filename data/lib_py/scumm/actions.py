import example
import lib_py.actions as actions
import lib_py.scumm.scumm as s
import lib_py.scumm.helper as func
from lib_py.scumm.scumm import Config
from lib_py.scumm.dialogue import Dialogue, Line

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
    def __init__(self, lines: list, font:str ='monkey', id = None, tag = None):
        self.type = 'scumm.action.say'
        self.font = font
        self.id = id
        self.tag = tag
        self.lines = lines

class ResetVerb(actions.CallFunc):
    @staticmethod
    def pippo():
        Config.verb = Config.verbSets[0].defaultVerb
        Config.item1 = ''
        Config.item2 = ''
        func.update_current_action()
    def __init__(self):
        super().__init__(f = ResetVerb.pippo)
    

class EndDialogue(actions.CallFunc):
    @staticmethod
    def pippo(dialogueId: str):
        def f():
            d : Dialogue = s.State.getDialogue(dialogueId)
            if d.onEnd:
                d.onEnd()            
            main : example.Wrap1 = example.get('main')
            ui : example.Wrap1 = example.get('ui')
            dial : example.Wrap1 = example.get('dialogue')
            ui.setActive(True)
            dial.setActive(False)
            main.enableControls(True)
        return f
    def __init__(self, dialogueId: str):
        super().__init__(f = EndDialogue.pippo(dialogueId))


class StartDialogue(actions.CallFunc):
    @staticmethod
    def pippo(dialogueId: str, group: int):
        def f():
            main : example.Wrap1 = example.get('main')
            ui : example.Wrap1 = example.get('ui')
            dial : example.Wrap1 = example.get('dialogue')
            ui.setActive(False)
            dial.setActive(True)
            main.enableControls(False)
            # get the dialogue
            print ('opening dialogue: ' + dialogueId)
            d : Dialogue = s.State.getDialogue(dialogueId)
            if d.onStart:
                d.onStart()
            d.reset()
            lines = d.getLines()
            for line in lines:
                dial.appendText(line)
        return f

    def __init__(self, dialogueId : str, group: int = 0):
        super().__init__(f = StartDialogue.pippo(dialogueId, group))

class ResumeDialogue(actions.CallFunc):
    @staticmethod
    def pippo(dialogueId: str, group: int):
        def f():
            dial : example.Wrap1 = example.get('dialogue')
            d : Dialogue = s.State.getDialogue(dialogueId)
            actlines = d.getLines()
            for line in actlines:
                dial.appendText(line)
        return f

    def __init__(self, dialogueId : str, group: int = 0):
        super().__init__(f = ResumeDialogue.pippo(dialogueId, group))
