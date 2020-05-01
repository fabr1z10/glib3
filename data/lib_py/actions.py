import lib_py.script as script
import lib_py.engine as engine
import example
import random

class Animate:
    def __init__(self, anim: str, id = None, tag = None, fwd: bool = True, sync: bool = False):
        self.type = 'action.animate'
        self.id = id
        self.tag = tag
        self.anim = anim
        self.fwd = fwd
        self.sync = sync


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

class DelayRandom:
    def __init__(self, min: float, max: float):
        self.type = 'action.delaydynamic'
        self.func = lambda : random.uniform(min, max)


class MoveAccelerated:
    def __init__(self, v0, a, yStop, id = None, tag = None):
        self.type = 'action.moveaccelerated'
        self.id = id
        self.tag = tag
        self.initialVelocity = v0
        self.acceleration = a
        self.yStop = yStop


class AddEntity(CallFunc):
    @staticmethod
    def pippo(entity, parent):
        def f():
            m : example.Wrap1 = example.get(parent)
            m.add (entity)
        return f

    def __init__(self, entity, parent = 'main'):
        super().__init__(f = AddEntity.pippo(entity, parent))

class RemoveEntity(CallFunc):
    @staticmethod
    def pippo(id = None, tag = None):
        def f():
            if id is not None:
                example.remove(id)
            else:
                example.removeByTag(tag)
        return f

    def __init__(self, id : int = None, tag: str = None):
        super().__init__(f = RemoveEntity.pippo(id, tag))


class ChangeCamBounds():
    def __init__(self, camId: str, xmin: float, xmax: float, ymin: float, ymax: float):
        self.type = 'action.changecambounds'
        self.cam = camId
        self.xmin = xmin
        self.xmax = xmax
        self.ymin = ymin
        self.ymax = ymax
