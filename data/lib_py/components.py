from typing import Callable

class Gfx:
    def __init__(self, image):
        self.type = 'components.gfx'
        self.image = image

class HotSpot:
    def __init__(self, onenter: Callable = None, onleave: Callable = None, onclick: Callable = None):
        self.type = 'components.hotspot'
        self.onenter = onenter
        self.onleave = onleave
        self.onclick = onclick
