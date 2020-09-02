import example
import lib_py.actions as actions
import lib_py.scumm.scumm as s
import lib_py.scumm.helper as func
from lib_py.scumm.scumm import Config
from lib_py.scumm.dialogue import Dialogue
import lib_py.engine as engine

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
    def __init__(self, lines: list, font:str ='monkey', id = None, tag = None, animate = True):
        self.type = 'scumm.action.say'
        self.font = font
        self.id = id
        self.tag = tag
        self.lines = lines
        self.animate = animate

class EnableBlock:
    def __init__(self, walkarea: str, wall: int, active: bool):
        self.type = 'scumm.action.enable_block'
        self.walkarea = walkarea
        self.wall = wall
        self.active = active

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
            d : Dialogue = s.Data.dialogues[dialogueId]
            # check if this dialogue has an onend script associated
            onEnd = func.addCustomScript (engine.scripts.dialogues, 'onend_' + dialogueId)
            if onEnd:
                print ('found script')
                example.play(onEnd)
            else:
                print ('not found end!')
            #if d.onEnd:
            #    d.onEnd()            
            main : example.Wrap1 = example.get('main')
            ui : example.Wrap1 = example.get('ui')
            if ui.valid:
                ui.setActive(True)
            dial : example.Wrap1 = example.get('dialogue')
            dial.setActive(False)
            main.enableControls(True)
        return f
    def __init__(self, dialogueId: str):
        super().__init__(f = EndDialogue.pippo(dialogueId))


class EnableControls(actions.CallFunc):
    @staticmethod
    def pippo(value: bool):
        def f():
            main : example.Wrap1 = example.get('main')
            ui : example.Wrap1 = example.get('ui')
            if ui.valid:
                ui.setActive(value)
            main.enableControls(value)
        return f

    def __init__(self, value: bool):
        super().__init__(f = EnableControls.pippo(value))


class StartDialogue(actions.CallFunc):
    @staticmethod
    def pippo(dialogueId: str, group: int):
        def f():
            print ('opening dialogue: ' + dialogueId)            
            d : Dialogue = s.Data.dialogues[dialogueId]
            # check if this dialogue has an onstart script associated
            onStart = func.addCustomScript (engine.scripts.dialogues, 'onstart_' + dialogueId)
            if onStart:
                print ('found script')
                example.play(onStart)
            d.reset()
            if d.onStart:
                d.onStart()
            lines = d.getLines()
            if lines:
                main : example.Wrap1 = example.get('main')
                ui : example.Wrap1 = example.get('ui')
                if ui.valid:
                    ui.setActive(False)
                dial : example.Wrap1 = example.get('dialogue')
                dial.setActive(True)
                main.enableControls(False)
                # get the dialogue
                for line in lines:
                    dial.appendText(line)
            else:
                # no lines, just exit dialogue
                return EndDialogue.pippo(dialogueId)()
        return f

    def __init__(self, dialogueId : str, group: int = 0):
        super().__init__(f = StartDialogue.pippo(dialogueId, group))

class ResumeDialogue(actions.CallFunc):
    @staticmethod
    def pippo(dialogueId: str, group: int):
        def f():
            print ('resuming')
            dial : example.Wrap1 = example.get('dialogue')
            d : Dialogue = s.Data.dialogues[dialogueId]
            print ('current node ' + d.current)
            actlines = d.getLines()
            for line in actlines:
                print ('APPENDIG ' + line.id)
                dial.appendText(line)
        return f

    def __init__(self, dialogueId : str, group: int = 0):
        super().__init__(f = ResumeDialogue.pippo(dialogueId, group))

class AddToInventory(actions.CallFunc):
    @staticmethod
    def pippo(id:str, qty: int):
        def f():
            print ('eccocococococo')
            inv = s.State.getCurrentInventory()
            if id in inv:
                inv[id]+=qty
            else:
                inv[id] = qty
            func.refresh_inventory()
        return f

    def __init__(self, id : str, qty: int = 1):
        super().__init__(f = AddToInventory.pippo(id,qty))

