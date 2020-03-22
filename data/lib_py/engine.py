from typing import Callable

class Engine:
    def __init__(self, deviceSize, windowSize, uiHeight : int, startRoom = None):
        self.deviceSize = deviceSize
        self.windowSize = windowSize
        self.uiHeight = uiHeight
        self.title = 'Untitled project'
        self.currentRoom = startRoom
        self.previousRome = None
        self.rooms = {}
        self.state = {
            

        }
        self.assets = {}
        self.assets['fonts'] = {}
        
    def addFont (font):
        self.assets['fonts'][font.id] = font


class KeyListener:
    def __init__(self):
        self.type = 'runner.keylistener'
        self.keys = []
    
    def addKey (self, key : int, func : Callable):
        self.keys.append ({ 'key': key, 'func': func })