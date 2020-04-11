import lib_py.script as script


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