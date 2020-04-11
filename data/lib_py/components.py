from typing import Callable

class Gfx:
    def __init__(self, image):
        self.type = 'components.gfx'
        self.image = image

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
