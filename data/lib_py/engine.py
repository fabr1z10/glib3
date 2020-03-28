from typing import Callable

import enum
import lib_py.components as components
import lib_py.assets as assets
import lib_py.entity as entity
import lib_py.camera as camera
import lib_py.runner as runner

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


        