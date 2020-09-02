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

########################################################
# this is where all begins ... :-)
########################################################
def startUp():
    print ('# starting up ...')
    example.init(example.what)
    addShader (ShaderType.unlit_textured)
    addShader (ShaderType.unlit_color)
    addShader (ShaderType.text)
    
    global device_size
    global window_size
    global room
    global title

    with open(example.dir+'/main.yaml') as f:
        a = yaml.load(f, Loader = yaml.FullLoader)  
        language = a['lang']
        device_size = tuple(a['device_size'])
        window_size = tuple(a['window_size'])
        room = a['start_room']
        title = a['title']
        print ('# loading assets ...')
        loadAssets()
        print ('# loading strings ...')
        loadText (language)
        # read game variables, and functions
        with open(example.dir+'/variables.yaml') as f:
            data['vars'] = yaml.load(f, Loader = yaml.FullLoader)            
        for f in a['fonts']:
            print ('# loading font ' + f['id'])
            addFont (assets.Font (f['id'], f['file']))
        return a                    


# contains engine related infos.
# All games require these infos.
__dir = ''
device_size = [320, 200]
window_size = [640, 400]
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
    'functions': {},
    'factories': {},
    'vars': {}
}

scripts = None

def identity(x): 
    return x


def getString (s: str):
    if s is None:
        return None
    d = data['strings']
    for a in s.split('/'):
        d = d[a]
    return d

def getVariable (s: str):
    d = data['vars']
    for a in s.split('/'):
        d = d[a]
    return d

def getRef(s: str):
    if s.startswith ('@s:'):
        return getString(s)
    elif s.startswith ('@v:'):
        return getVariable(s)
    return None

def getFunc (f):
    func = f['func']
    d = scripts
    for a in func.split('/'):
        d = getattr (d, a)
    # check if I have args
    args = f.get('args', None)
    if args:
        # convert reference arguments
        real_args = {}
        for key, value in args.items():
            if isinstance(a, str) and a[0] == '@':
                real_args[key] = (getRef(a))
            else:
                real_args[key] = (a)
        return d(**real_args)
    else:
        return d


def write (key: str, value):
    if key[0] == '@':
        c = key[1]
        if c == '&':
            # Set a variable
            cc = data['vars']
            ks = key[2:].split('/')
            for b in ks[:-1]:
                cc = cc[b]
            cc[ks[-1]] = value
        else:
            raise Exception('don''t know how to read ' + key + ' in dict ' + str(d))

def fetch (key: str):
    if isinstance(key, str):
        if key[0] == '@':
            c = key[1]
            if c == '@':
                return key[1:]
            elif c == '$':
                # get a string
                x = data['strings']
                for b in key[2:].split('/'):
                    if b.isnumeric():
                        x = x[int(b)]
                    else:
                        x = x[b]
                return x
            elif c == '&':
                # get a variable
                cc = data['vars']
                for b in key[2:].split('/'):
                    cc = cc[b]
                return cc
            elif c == ')':
                # get a function value
                cc = data['functions']
                for b in key[2:].split('/'):
                    cc = cc[b]
                return cc()
            else:
                raise Exception('don''t know how to read ' + key)
        else:
            return key
    else:
        return key
    

def read(d: dict, key: str, **kwargs):
    if key in d:
        return fetch(d[key])
    else:
        if 'default_value' in kwargs:
            return kwargs['default_value']
        else:
            raise BaseException('Can''t read ' + key + ' in dictionary')
        








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
            #print ('reading ' + fi)
            with open(dir+'/'+fi) as f:
                models = yaml.load(f, Loader = yaml.FullLoader) 
                for key, value in models.items():                    
                    #print ('reading asset: ' + key + ', type: ' + value['type'])
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
        with open(dir+ '/text.yaml', encoding='utf8') as f:
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

        


        
