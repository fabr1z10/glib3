import example
import lib_py.script as script
import lib_py.scumm.actions as sa
from lib_py.scumm.scumm import State
import lib_py.actions as act


def say(lines : list, tag: str = 'player'):
    def f():
        s = script.Script()
        s.addAction (sa.Say (lines = lines, tag = tag, font = 'monkey'))
        return s
    return f

def pickup(id: str):
    def f():
        s = script.Script()
        s.addAction (act.RemoveEntity(tag=id))
        s.addAction (sa.AddToInventory(id, 1))
        return s
    return f

def openDoor (doorId: str, var: str):
    def f():
        def g():
            setattr(State.md.doors, var, 'open')
            #State.variables[var] = 'open'
        s = script.Script()
        s.addAction (act.Animate(anim='open', tag=doorId))
        s.addAction (act.CallFunc(f = g))
        return s
    return f

def closeDoor (doorId: str, var: str):
    def f():
        def g():
            setattr(State.md.doors, var, 'closed')
            #State.variables[var] = 'closed'
        s = script.Script()
        s.addAction (act.Animate(anim='closed', tag=doorId))
        s.addAction (act.CallFunc(f = g))
        return s
    return f

def walkDoor (var: str, room: str, pos, dir):
    def f():
        if getattr(State.md.doors, var) == 'open':
            return changeRoom(room = room, pos = pos, dir=dir)()
        return None
    return f


def startDialogue (character : str):
    def f():
        s = script.Script()
        s.addAction (sa.StartDialogue(character))
        return s
    return f

def changeRoom (room: str, pos = None, dir = None):
    def f():
        # get the current player
        currentPlayer = State.player
        State.setDynamicItem(id = currentPlayer, room = room, pos = pos, chardir =  dir, state = 'idle', parent='walkarea')
        s = script.Script()
        s.addAction(act.ChangeRoom(room=room))
        return s
    return f