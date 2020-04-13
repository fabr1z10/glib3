from typing import Callable
from typing import List, Tuple

import example
import enum
import yaml
import os

import lib_py.assets as assets
import lib_py.runner as runner



# import lib_py.components as components
# import lib_py.assets as assets
# import lib_py.entity as entity
# import lib_py.camera as camera
# import lib_py.runner as runner
class ShaderType(enum.Enum): 
    unlit_textured = 0,
    unlit_color = 1,
    text = 2

def startUp():
    example.init(example.what)
    addShader (ShaderType.unlit_textured)
    addShader (ShaderType.unlit_color)
    addShader (ShaderType.text)

# contains engine related infos.
# All games require these infos.
__dir = ''
device_size : List[int] = [320, 200]
window_size : List[int] = [640, 400]
frame_time = 0.1
title = 'Untitled project'
room = ''
previous_room = ''
shaders = []
data = {
    'assets': {
        'fonts': {},
        'spritemodels': {}
    },
    'rooms': {},
    'strings': {},
    'entities': {},
    'factories': {}
}

def addEntity (id : str, e):
    data['entities'][id] = e

def addFont (font : assets.Font):
    data['assets']['fonts'][font.id] = font

def addRoom (id : str, f : Callable):
    data['rooms'][id] = f

def addShader(s : ShaderType):
    shaders.append(s.name)

def loadSprites():
    print ('dir = ' + example.dir)
    with open(example.dir + '/sprites/01.yaml') as f:
        data['assets']['spritemodels'] = yaml.load(f, Loader=yaml.FullLoader)
    print(data)

def loadText(lang: str):
    with open(example.dir+'/text/eng/text.yaml') as f:
        data['strings']= yaml.load(f, Loader=yaml.FullLoader)
    print(data['strings'])

# # creating enumerations using class 

# class Engine:
#     def __init__(self, deviceSize, windowSize, uiHeight : int, startRoom = None):
#         self.deviceSize = deviceSize
#         self.windowSize = windowSize
#         self.uiHeight = uiHeight
#         self.title = 'Untitled project'
#         self.currentRoom = startRoom
#         self.previousRome = None
#         self.rooms = {}
#         self.state = {
            

#         }
#         self.strings = {}
#         self.assets = {}
#         self.config = {}
#         self.state = {}
#         self.shaders = []
#         self.assets['fonts'] = {}

        


        