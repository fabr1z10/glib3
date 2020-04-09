import example
import lib_py.script as script
import lib_py.scumm.actions as sa

def say(lines : list, tag: str = 'player'):
    def f():
        s = script.Script()
        s.addAction (sa.Say (lines = lines, tag = tag, font = 'monkey'))
        return s
    return f

def startDialogue (character : str):
    def f():
        s = script.Script()
        s.addAction (sa.StartDialogue(character))
        return s
    return f


