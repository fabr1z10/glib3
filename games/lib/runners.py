from typing import Callable


class KeyListener:
    def __init__(self):
        self.type = 'runner.keylistener'
        self.keys = []

    def add_key(self, key: int, func: Callable):
        self.keys.append({'key': key, 'func': func})


class CollisionResponse:
    def __init__(self, on_enter: callable = None, on_leave: callable = None):
        self.on_enter = on_enter
        self.on_leave = on_leave


class CollisionEngine:
    def __init__(self, width: int, height: int, depth: int = 0, eps: float = 0.01):
        self.type = 'runner.collisionengine'
        self.size = [width, height, depth]
        self.response = []
        self.eps = eps

    def add_response(self, tag1: int, tag2: int, response: CollisionResponse):
        self.response.append([tag1, tag2, response])


class DynamicWorld:
    def __init__(self, width: int, height: int, cam: str):
        self.type = 'runner.dynamicworld'
        self.width = width
        self.height = height
        self.cam = cam
        self.items = []


class Scheduler:
    def __init__(self):
        self.type = 'runner.scheduler'
        self.lmb_click = None

