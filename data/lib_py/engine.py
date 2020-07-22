from typing import Callable
from typing import List, Tuple

import example
import enum
import yaml
import os

import lib_py.assets as assets
import lib_py.runner as runner
from lib_py.skeletalmodel import SkeletalModel
from lib_py.builder.skeletalmodel import ms1

# import lib_py.components as components
# import lib_py.assets as assets
# import lib_py.entity as entity
# import lib_py.camera as camera
# import lib_py.runner as runner
class ShaderType(enum.Enum): 
    unlit_textured = 0,
    unlit_color = 1,
    text = 2,
    skeletal = 3

def startUp(lang: str):
    example.init(example.what)
    addShader (ShaderType.unlit_textured)
    addShader (ShaderType.unlit_color)
    addShader (ShaderType.text)
    loadAssets()
    loadText (lang)
    for k,v in data['assets']['models'].items():
        print("key: " + k)
        print(v)
    # read game variables
    with open(example.dir+'/variables.yaml') as f:
        data['vars'] = yaml.load(f, Loader = yaml.FullLoader) 


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
        'models': {},            # include sprite + skeletal
        'skeletalanimations': {},
        'mesh': {}
    },
    'rooms': {},
    'strings': {},
    'entities': {},
    'factories': {},
    'vars': {}
}

scripts = None

def identity(x): 
    return x




        








asset_fac = {
    'asset.sprite': identity,
    'asset.boxed': identity,
    'asset.skeletalmodel': identity,
    'asset.skeletalanimation': identity,
    'custom.model1': ms1,
    'mesh': identity
}
asset_loc = {
    'asset.sprite': 'models',
    'asset.boxed': 'models',
    'asset.skeletalmodel': 'models',
    'asset.skeletalanimation': 'skeletalanimations',
    'custom.model1': 'models',
    'mesh': 'mesh'

}

def addEntity (id : str, e):
    data['entities'][id] = e

def addFont (font : assets.Font):
    data['assets']['fonts'][font.id] = font

def addRoom (id : str, f : Callable):
    data['rooms'][id] = f

def addShader(s : ShaderType):
    shaders.append(s.name)



def loadAssets():
    dir = example.dir + '/assets'
    if os.path.exists(dir):
        files = os.listdir(dir)
        for fi in files:
            print ('reading ' + fi)
            with open(dir+'/'+fi) as f:
                models = yaml.load(f, Loader = yaml.FullLoader) 
                for key, value in models.items():                    
                    print ('reading asset: ' + key + ', type: ' + value['type'])
                    tp = value['type']
                    if tp not in asset_fac:
                        raise ValueError("Don't know how to build " + tp)
                    data['assets'][asset_loc[tp]][key] = asset_fac[tp](value)
                    #print ('stored ' + key)
                    


def loadSprites():
    #print ('dir = ' + example.dir)
    dir = example.dir +'/sprites'
    if os.path.exists(dir):
        files = os.listdir(dir)
        for fi in files:
            print ('reading: ' + fi)
            with open(dir+'/'+fi) as f:
                data['assets']['models'] = yaml.load(f, Loader=yaml.FullLoader)

def loadSkeletalModels():
    dir = example.dir +'/skeletons'
    if os.path.exists(dir):
        files = os.listdir(dir)
        for fi in files:
            print ('reading: ' + fi)
            with open(dir+'/'+fi) as f:
                data['assets']['skeletalmodels'] = yaml.load(f, Loader=yaml.FullLoader)
    if 'models' in data['assets']['skeletalmodels']:
        for a, b in data['assets']['skeletalmodels']['models'].items():
            print ("ASSO: " + a)
            print (data['assets']['skeletalmodels'])
            data['assets']['models'][a] = SkeletalModel(b, data)

def loadText(lang: str):
    dir = example.dir +'/text/'+lang;
    if os.path.exists(dir):
        with open(dir+ '/text.yaml') as f:
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

        


        
