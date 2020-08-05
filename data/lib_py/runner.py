from typing import Callable

class KeyListener:
    def __init__(self):
        self.type = 'runner.keylistener'
        self.keys = []
    
    def addKey (self, key : int, func : Callable):
        self.keys.append ({ 'key': key, 'func': func })

class CollisionResponse:
    def __init__(self, onenter: callable = None, onleave:callable = None):
        self.onenter = onenter
        self.onleave = onleave

class CollisionEngine:
    def __init__(self, width: int, height: int, coll25: bool = False, eps:float = 0.01):
        self.type = 'runner.collisionengine'
        self.size = [width, height]
        self.response = []
        self.coll25 = coll25
        self.eps = eps

    def addResponse(self, tag1: int, tag2: int, response: CollisionResponse):
        self.response.append ([tag1, tag2, response])

class DynamicWorld:
    def __init__(self, width: int, height: int, cam: str):
        self.type = 'runner.dynamicworld'
        self.width = width
        self.height = height
        self.cam = cam
        self.items = []


def pippo(x, y):
    print ('clicked at ' + str(x) + ', ' + str(y))




class Scheduler:
    def __init__(self):
        self.type = 'runner.scheduler'
        self.lmbclick = pippo        
