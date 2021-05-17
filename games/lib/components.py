class FPSCounter:
    def __init__(self):
        self.type = 'components.fpscounter'


class Gfx:
    def __init__(self, image, width: float = None, height: float = None, repeat: list = None, offset = (0, 0), blend = 0,
                 multcolor = (1,1,1,1)):
        self.type = 'components.gfx'
        self.image = image
        self.width = width
        self.height = height
        self.rep = repeat
        self.offset = offset
        self.cls = 0
        self.blend = blend
        self.multcolor = multcolor


class AnimGfx:
    def __init__(self):
        self.type = 'components.animgfx'
        self.frames = []
    def add_frame(self, image: str, duration: float, disp = [0, 0]):
        self.frames.append({'image': image, 'disp': disp, 'duration': duration})



class Info:
    def __init__(self, **kwargs):
        self.type = 'components.info'
        self.stuff = kwargs


class Collider:
    def __init__(self, flag: int, mask: int, tag: int, shape, debug = False):
        self.type = 'components.collider'
        self.flag = flag
        self.mask = mask
        self.tag = tag
        self.shape = shape
        self.debug = debug


class SmartCollider(Collider):
    def __init__(self, flag: int, mask: int, tag: int, cast_tag: int = 0, cast_mask: int = 0, debug = False):
        super().__init__(flag, mask, tag, None, debug)
        self.type = 'components.smartcollider'
        self.cast_tag = cast_tag
        self.cast_mask = cast_mask


class SkeletalCollider(Collider):
    def __init__(self, flag: int, mask: int, tag: int, cast_tag: int = 0, cast_mask: int = 0):
        super().__init__(flag, mask, tag, None)
        self.type = 'components.skeletalcollider'
        self.cast_tag = cast_tag
        self.cast_mask = cast_mask


class Controller2D:
    def __init__(self, mask_up: int, mask_down: int, max_climb_angle: float, max_descend_angle, size, shift = None, debug = False, hor_rays : int = 4, vert_rays: int = 4):
        self.type = 'components.controller2D'
        self.maxClimbAngle = max_climb_angle
        self.maxDescendAngle = max_descend_angle
        self.horRays = hor_rays
        self.vertRays = vert_rays
        self.maskUp = mask_up
        self.maskDown = mask_down
        self.size = size
        self.shift = shift
        self.debug = debug

class Controller3D:
    def __init__(self, mask_up: int, mask_down: int, max_climb_angle: float, max_descend_angle, size, shift = (0, 0, 0), debug=False):
        self.type = 'components.controller3D'
        self.maxClimbAngle = max_climb_angle
        self.maxDescendAngle = max_descend_angle
        self.maskUp = mask_up
        self.maskDown = mask_down
        self.size = size
        self.shift = shift
        self.debug = debug

class ControllerFlat:
    def __init__(self, mask: int, size, hor_rays : int = 4, vert_rays: int = 4):
        self.type = 'components.controller_flat'
        self.horRays = hor_rays
        self.vertRays = vert_rays
        self.mask = mask
        self.size = size


class Dynamics2D:
    def __init__(self, gravity):
        self.type = 'components.dynamics2D'
        self.gravity = gravity

class ShadowRenderer:
    def __init__(self, angle = 0.0, scale_length = 1.0, translate = (0,0,0), shear = 0):
        self.type = 'components.shadowrenderer'
        self.angle = angle
        self.translate = translate
        self.shear = shear
        self.scale_length = scale_length

class StateMachine:
    def __init__(self, initial_state: str):
        self.type = 'components.statemachine'
        self.initialState = initial_state
        self.states = []

class MarkovStateMachine(StateMachine):
    def __init__(self, initial_state: str):
        super().__init__(initial_state)
        self.type = 'components.markov_state_machine'
        self.probs = None



class KeyInput:
    def __init__(self):
        self.type = 'components.keyinput'


class KeyListener:
    def __init__(self):
        self.type = 'runner.'


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


class TiledGfx:
    def __init__(self, tile_sheet: str, sheet_size, tile_data: list, width: int, height: int, size: float = 1.0,
                 repx: int = None, repy: int = None, angle: float = None):
        self.type = 'components.gfx'
        self.image = tile_sheet
        self.sheetSize = sheet_size
        self.tileData = tile_data
        self.width = width
        self.height = height
        self.size = size
        self.repx = repx
        self.repy = repy
        self.angle = angle
        self.cls = 1


# create a colored shape
class ShapeGfxColor:
    def __init__(self, shape, color):
        self.type ='components.gfx'
        self.cls = 3
        self.shape = shape
        self.color = color



class Parallax:
    def __init__(self, cam: str, factor, campos0, pos0):
        self.type = 'components.parallax'
        self.factor = factor
        self.cam = cam
        self.cam0 = campos0
        self.pos0 = pos0


class PolygonalMover:
    def __init__(self, origin, loop, moves, pct=0, sinx = None, siny=None):
        self.type ='components.polymover'
        self.moves = moves
        self.origin = origin
        self.loop = loop
        self.pct = pct
        self.sinx = sinx
        self.siny = siny

class AcceleratedMover:
    def __init__(self, v0, acceleration, angular_speed = None):
        self.type ='components.accelerated_mover'
        self.v0 = v0
        self.acceleration = acceleration
        self.angular_speed = angular_speed


class Platform:
    def __init__(self):
        self.type = 'components.platform'


class ColliderManager:
    def __init__(self):
        self.type = 'components.collidermanager'
        self.colliders = []

class SkColl:
    def __init__ (self, flag: int, mask: int, tag: int, width, P0,j0,w0,P1,j1,w1):
        self.type = 'components.skc'
        self.flag = flag
        self.mask = mask
        self.tag = tag
        self.width = width
        self.P0 = P0
        self.j0 = j0
        self.w0 = w0
        self.P1 = P1
        self.j1 = j1
        self.w1 = w1

class HotSpot:
    def __init__(self, shape, priority:int=0,onenter = None, onleave = None, onclick = None):
        self.type = 'components.hotspot'
        self.shape = shape
        self.onenter = onenter
        self.onleave = onleave
        self.onclick = onclick
        self.priority = priority

class HotSpotManager:
    def __init__(self, lmbclick = None):
        self.type = 'components.hotspotmanager'
        self.lmbclick = lmbclick

class Cursor:
    def __init__(self):
        self.type = 'components.cursor'

