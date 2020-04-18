import lib_py.script as script
import example

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

class Move:
    def __init__(self, speed: float, to = None, by = None, immediate: bool = False, id = None, tag = None):
        self.type = 'action.move'
        self.id = id
        self.tag = tag        
        self.speed = speed
        self.to = to
        self.by = by
        self.immediate = immediate

class SetState:
    def __init__(self, state: str, id = None, tag = None):
        self.type = 'action.setstate'
        self.id = id
        self.tag = tag
        self.state = state

class MoveAccelerated:
    def __init__(self, v0, a, yStop, id = None, tag = None):
        self.type = 'action.moveaccelerated'
        self.id = id
        self.tag = tag
        self.initialVelocity = v0
        self.acceleration = a
        self.yStop = yStop


class RemoveEntity(CallFunc):
    @staticmethod
    def pippo(id):
        def f():
            example.remove(id)
        return f

    def __init__(self, id : int):
        super().__init__(f = RemoveEntity.pippo(id))
