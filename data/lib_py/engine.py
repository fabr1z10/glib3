from typing import Callable

import enum

# creating enumerations using class 
class ShaderType(enum.Enum): 
    unlit_textured = 0,
    unlit_color = 1,
    text = 2

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
        self.strings = {}
        self.assets = {}
        self.config = {}
        self.state = {}
        self.shaders = []
        self.assets['fonts'] = {}

        
    def addFont (self, font):
        self.assets['fonts'][font.id] = font

    def addShader(self, s : ShaderType):
        self.shaders.append(s.name)

class KeyListener:
    def __init__(self):
        self.type = 'runner.keylistener'
        self.keys = []
    
    def addKey (self, key : int, func : Callable):
        self.keys.append ({ 'key': key, 'func': func })

def pippo(x, y):
    print ('clicked at ' + str(x) + ', ' + str(y))

class HotSpotManager:
    def __init__(self):
        self.type = 'runner.hotspotmanager'
        self.lmbclick = pippo
        