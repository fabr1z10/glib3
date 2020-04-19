from typing import Callable

class Gfx:
    def __init__(self, image, width: float = None, height: float = None, repeat: list = None):
        self.type = 'components.gfx'
        self.image = image
        self.width = width
        self.height = height
        self.rep = repeat
        self.cls = 0

class TiledGfx:
    def __init__(self, tilesheet : str, sheetSize, tileData : list, width: int, height: int, size: float):
        self.type = 'components.gfx'
        self.image = tilesheet
        self.sheetSize = sheetSize
        self.tileData = tileData
        self.width = width
        self.height = height
        self.size = size
        self.cls = 1

class HotSpot:
    def __init__(self, shape, priority:int=0,onenter: Callable = None, onleave: Callable = None, onclick: Callable = None):
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

class Follow:
    def __init__(self, cam = 'maincam', relpos = [0, 0, 5], up = [0, 1, 0]):
        self.type = 'components.follow'
        self.cam = cam
        self.relativepos = relpos
        self.up = up

class Collider:
    def __init__(self, flag: int, mask: int, tag: int, shape):
        self.type = 'components.collider'
        self.flag = flag
        self.mask = mask
        self.tag = tag
        self.shape = shape

class SmartCollider(Collider):
    def __init__(self, flag: int, mask: int, tag: int):
        super().__init__(flag, mask, tag, None)
        self.type = 'components.smartcollider'

class Controller2D:
    def __init__(self, maskUp: int, maskDown: int, maxClimbAngle : float, maxDescendAngle, horRays : int = 4, vertRays: int = 4):
        self.type = 'components.controller2D'
        self.maxClimbAngle = maxClimbAngle
        self.maxDescendAngle = maxDescendAngle
        self.horRays = horRays
        self.vertRays = vertRays
        self.maskUp = maskUp
        self.maskDown = maskDown

class Dynamics2D:
    def __init__(self, gravity):
        self.type = 'components.dynamics2D'
        self.gravity = gravity

class StateMachine:
    def __init__(self, initialState:str):
        self.type = 'components.statemachine'
        self.initialState = initialState
        self.states = []

class KeyInput:
    def __init__(self):
        self.type = 'components.keyinput'

class State:
    def __init__(self, id: str):
        self.id = id
        self.keys = []

class NullState(State):
    def __init__(self, id: str):
        super().__init__(id)
        self.type = 'state.null'

class SimpleState (State):
    def __init__(self, id: str, anim: str):
        super().__init__(id)
        self.type = 'state.simple'
        self.anim = anim

class Info():
    #def __init__(self, text_color : list, text_offset : list):
    def __init__(self, **kwargs):
        self.type = 'components.info'
        self.stuff = kwargs
