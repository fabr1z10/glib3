from mopy.script import Script
import mopy.engine as engine
import mopy.monkey as monkey
import mopy
from mopy.entity import TextAlignment
import example
import random
import mopy.util as utils
from mopy.room import add_entity

class NoOp:
    def __init__(self):
        self.type = 'action.noop'


class Animate:
    def __init__(self, anim: str, entity_id=None, tag=None, fwd: bool = True, sync: bool = False, flipx: bool = False):
        self.type = 'action.animate'
        self.id = entity_id
        self.tag = tag
        self.anim = anim
        self.fwd = fwd
        self.sync = sync
        self.flipx = flipx


class RunScript:
    def __init__(self, s: Script = None, func = None):
        self.type = 'action.runscript'
        self.script = s
        self.func = func


class SuspendScript:
    def __init__(self, s: str):
        self.type = 'action.suspendscript'
        self.script = s


class ResumeScript:
    def __init__(self, s: str):
        self.type = 'action.resumescript'
        self.script = s

class KillScript:
    def __init__(self, s: str):
        self.type = 'action.killscript'
        self.script = s


class ChangeRoom:
    def __init__(self, room: str, args=None):
        self.type = 'action.changeroom'
        self.room = room
        self.args = args


class RestartRoom:
    def __init__(self):
        self.type = 'action.changeroom'
        self.room = monkey.engine.room

class Scale:
    def __init__(self, scale, duration, entity_id=None, tag=None):
        self.type = 'action.scale'
        self.scale= scale
        self.duration = duration
        self.id = entity_id
        self.tag = tag

class Scroll:
    def __init__(self, pos, relative, speed, cam):
        self.type = 'action.scroll'
        self.pos = pos
        self.relative = relative
        self.speed = speed
        self.cam = cam


class CallFunc:
    def __init__(self, f: callable):
        self.type = 'action.callfunc'
        self.func = f


class SetActive(CallFunc):
    @staticmethod
    def pippo(tag, value):
        def f():
            m: example.Wrap1 = example.get(tag)
            m.setActive(value)

        return f

    def __init__(self, tag: str, value: bool):
        super().__init__(f=SetActive.pippo(tag, value))


class SetVisible(CallFunc):
    @staticmethod
    def pippo(tag, value):
        def f():
            m: example.Wrap1 = example.get(tag)
            m.setVisible(value)
        return f

    def __init__(self, tag: str, value: bool):
        super().__init__(f=SetVisible.pippo(tag, value))


class Move:
    def __init__(self, speed: float = None, to=None, by=None, immediate: bool = False, entity_id=None, tag=None):
        self.type = 'action.move'
        self.id = entity_id
        self.tag = tag
        self.speed = speed
        self.to = to
        self.by = by
        self.immediate = immediate


class SetState:
    def __init__(self, state: str, entity_id=None, tag=None, args=None):
        self.type = 'action.setstate'
        self.id = entity_id
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
        self.func = lambda: random.uniform(min, max)


class MoveAccelerated:
    def __init__(self, v0, a, yStop, entity_id=None, tag=None):
        self.type = 'action.moveaccelerated'
        self.id = entity_id
        self.tag = tag
        self.initialVelocity = v0
        self.acceleration = a
        self.yStop = yStop


class AddEntity(CallFunc):
    @staticmethod
    def pippo(entity, pos, parent):
        def f():
            add_entity(entity, pos, parent)
            # m: example.Wrap1 = example.get(parent)
            # m.add(entity)

        return f

    def __init__(self, entity_id, pos, parent='main'):
        super().__init__(f=AddEntity.pippo(entity_id, pos, parent))


class CreateEntity(CallFunc):
    @staticmethod
    def pippo(func_id, pos, args, use_tile, parent):
        def f():
            utils.create_entity(func_id, pos, args=args, use_tile=use_tile, parent=parent)
        return f

    def __init__(self, func_id: str, pos, args=None, use_tile = True, parent='main'):
        super().__init__(f=CreateEntity.pippo(func_id, pos, args, use_tile, parent))


class SetText(CallFunc):
    @staticmethod
    def pippo(tag, text):
        def f():
            example.get(tag).setText(text)
        return f

    def __init__(self, tag, text):
        super().__init__(f=SetText.pippo(tag, text))




class RemoveEntity(CallFunc):
    @staticmethod
    def pippo(entity_id=None, tag=None):
        def f():
            if entity_id is not None:
                example.remove(entity_id)
            else:
                example.removeByTag(tag)

        return f

    def __init__(self, entity_id: int = None, tag: str = None):
        super().__init__(f=RemoveEntity.pippo(entity_id, tag))


class Msg:
    def __init__(self, text: str, font: str = None, pos: tuple = (0, 0, 0), color: tuple = (1, 1, 1, 1), eoc=False, timeout=1, outline_color=None, outline=False, box=False, padding = 0,
                 inner_texture='', border_texture='', align=TextAlignment.top_left, max_width=1000.0, thickness=1.0):
        self.type = 'action.msg'
        self.font = font if font else mopy.monkey.engine.data.globals.default_font
        self.text = mopy.monkey.engine.read(text)
        self.pos = pos
        self.color = color
        self.outline_color = outline_color
        self.end_on_click = eoc
        self.time = timeout
        self.outline = outline
        self.box = box
        self.padding = padding
        self.inner_texture = inner_texture
        self.border_texture = border_texture
        self.align = align
        self.max_width = max_width
        self.thickness = thickness


class Blink:
    def __init__(self, duration: float, blink_duration: float, entity_id=None, tag=None):
        self.type = 'action.blink'
        self.duration = duration
        self.blink_duration = blink_duration
        self.id = entity_id
        self.tag = tag


class Repeat:
    def __init__(self, func: callable, interval: float):
        self.type = 'action.repeat'
        self.func = func
        self.every = interval


class SetVariable(CallFunc):
    @staticmethod
    def set(name, value):
        def f():
            monkey.engine.set(name, value)
        return f

    def __init__(self, name, value):
        super().__init__(f=SetVariable.set(name, value))


class Sequence:
    def __init__(self):
        self.type = 'action.sequence'
        self.activities = []


class Walk:
    def __init__(self, pos, tag=None, id=None):
        self.type ='action.walk'
        self.pos = pos
        self.tag = tag
        self.id = id

class WaitForKey:
    def __init__(self, key = None):
        self.type = 'action.wait_for_key'
        self.key = key


class Turn:
    def __init__(self, dir, tag=None, id=None):
        self.type ='action.turn'
        self.dir = dir
        self.tag = tag
        self.id = id


class Say:
    def __init__(self, lines, tag=None, font=None, id=None):
        self.type = 'action.say'
        self.lines = lines # [mopy.monkey.engine.read(x) for x in lines]
        self.tag = tag
        self.font = font if font else mopy.monkey.engine.data.globals.default_font
        self.id = id


class Sayd:
    def __init__(self, lines, tag=None, font=None, id=None):
        self.type = 'action.say'
        self.lines = lines
        self.tag = tag
        self.font = font if font else mopy.monkey.engine.data.globals.default_font
        self.id = id

class SetWall:
    def __init__(self, walkarea: str, wall_id: int, enabled: bool):
        self.type = 'action.enable_block'
        self.walkarea = walkarea
        self.wall = wall_id
        self.active = enabled
