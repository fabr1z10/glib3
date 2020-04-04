from typing import Callable
from typing import List, Tuple

import enum
import yaml

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


# contains engine related infos.
# All games require these infos.
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
    'entities': {}
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
    with open('/home/fabrizio/glib3/data/mi1_py/sprites/01.yaml') as f:
        data['assets']['spritemodels'] = yaml.load(f, Loader=yaml.FullLoader)
    print(data)

def loadText(lang: str):
    with open('/home/fabrizio/glib3/data/mi1_py/text/eng/text.yaml') as f:
        data['strings']= yaml.load(f, Loader=yaml.FullLoader)
    print(data)

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

        


        