import example
from lib_py.engine import read, fetch
import lib_py.script as script
import lib_py.scumm.actions as sa
from lib_py.scumm.scumm import State, Data
import lib_py.actions as act
from lib_py.scumm.helper import gt

def say(lines : list, tag: str = 'player'):
    def f():
        s = script.Script()
        l = [gt(line) for line in lines]
        s.addAction (sa.Say (lines = l, tag = tag, font = 'monkey'))
        return s
    return f

def goto(room, pos, dir = None, node = 'walkarea' ):
    def f():
        s = script.Script()
        if pos is not None:
            Data.putItem (State.player, room, fetch(pos), node)
            if dir is not None:
                Data.items[State.player]['dir'] = dir
        s = script.Script()
        s.addAction (act.ChangeRoom(room = room))
        return s
    return f

def gotoDoor(doorId: str, room, pos, dir = None, node = 'walkarea' ):
    def f():
        a = read (Data.items[doorId], 'anim')
        print ('JIKKO= '  + a)
        if a == 'open':
            return goto(room, pos, dir, node)()
    return f


def pickup(id: str):
    def f():
        s = script.Script()
        print ('REMOVE ' + id)
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