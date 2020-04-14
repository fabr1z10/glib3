import lib_py.script as script

class Animate:
    def __init__(self, anim: str, id = None, tag = None):
        self.type = 'action.animate'
        self.id = id
        self.tag = tag
        self.anim = anim


class RunScript:
    def __init__(self, s : script.Script):
        self.type = 'action.runscript'
        self.script = s

class ChangeRoom:
    def __init__(self, room: str):
        self.type = 'action.changeroom'
        self.room = room

class CallFunc:
    def __init__(self, f : callable):
        self.type = 'action.callfunc'
        self.func = f

