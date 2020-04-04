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

    