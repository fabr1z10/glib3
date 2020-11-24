class FPSCounter:
    def __init__(self):
        self.type = 'components.fpscounter'


class Gfx:
    def __init__(self, image, width: float = None, height: float = None, repeat: list = None):
        self.type = 'components.gfx'
        self.image = image
        self.width = width
        self.height = height
        self.rep = repeat
        self.cls = 0


class Info:
    def __init__(self, **kwargs):
        self.type = 'components.info'
        self.stuff = kwargs


class Collider:
    def __init__(self, flag: int, mask: int, tag: int, shape):
        self.type = 'components.collider'
        self.flag = flag
        self.mask = mask
        self.tag = tag
        self.shape = shape


class SmartCollider(Collider):
    def __init__(self, flag: int, mask: int, tag: int, cast_tag: int = 0, cast_mask: int = 0):
        super().__init__(flag, mask, tag, None)
        self.type = 'components.smartcollider'
        self.cast_tag = cast_tag
        self.cast_mask = cast_mask


class Controller2D:
    def __init__(self, mask_up: int, mask_down: int, max_climb_angle: float, max_descend_angle, hor_rays : int = 4, vert_rays: int = 4):
        self.type = 'components.controller2D'
        self.maxClimbAngle = max_climb_angle
        self.maxDescendAngle = max_descend_angle
        self.horRays = hor_rays
        self.vertRays = vert_rays
        self.maskUp = mask_up
        self.maskDown = mask_down


class Dynamics2D:
    def __init__(self, gravity):
        self.type = 'components.dynamics2D'
        self.gravity = gravity


class StateMachine:
    def __init__(self, initial_state: str):
        self.type = 'components.statemachine'
        self.initialState = initial_state
        self.states = []


class KeyInput:
    def __init__(self):
        self.type = 'components.keyinput'


class Follow:
    def __init__(self, cam='maincam', relpos=[0, 0, 5], up=[0, 1, 0]):
        self.type = 'components.follow'
        self.cam = cam
        self.relativepos = relpos
        self.up = up


class GarbageCollect:
    def __init__(self, timeout):
        self.type = 'components.garbagecollect'
        self.timeout = timeout

