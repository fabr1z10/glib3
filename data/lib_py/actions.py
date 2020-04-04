import lib_py.script as script


class RunScript:
    def __init__(self, s : script.Script):
        self.type = 'action.runscript'
        self.script = s
