import lib_py.script as script
import lib_py.engine as engine
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

class RestartRoom:
    def __init__(self):
        self.type = 'action.changeroom'
        self.room = engine.room


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
    def __init__(self, state: str, id = None, tag = None, args = None):
        self.type = 'action.setstate'
        self.id = id
        self.tag = tag
        self.state = state
        self.args = args

class Delay:
    def __init__(self, sec: float):
        self.type = 'action.delay'
        self.sec = sec

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


class ChangeCamBounds():
    def __init__(self, camId: str, xmin: float, xmax: float, ymin: float, ymax: float):
        self.type = 'action.changecambounds'
        self.cam = camId
        self.xmin = xmin
        self.xmax = xmax
        self.ymin = ymin
        self.ymax = ymax
