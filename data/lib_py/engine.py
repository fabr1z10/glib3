from typing import Callable
from typing import List, Tuple

import example
import enum
import yaml
import os

import lib_py.assets as assets
import lib_py.runner as runner
from lib_py.skeletalmodel import SkeletalModel


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
        'skeletalanimations': {}
    },
    'rooms': {},
    'strings': {},
    'entities': {},
    'factories': {}
}

def identity(x): 
    return x

from lib_py.geom import vec2,vec3
from PIL import Image
from itertools import zip_longest

def grouper(iterable, n, fillvalue=None):
    args = [iter(iterable)] * n
    return zip_longest(*args, fillvalue=fillvalue)

def ms1(x):
    im = Image.open(example.dir+'/'+x['texture'])
    tex_height = im.size[1]
    o = vec2(l = x['origin'])
    o.y = tex_height - o.y
    origin = vec3(o.x, o.y, 0)
    print ('origin is ' +str(o))
    out = {
        'type': 'asset.skeletalmodel',
        'texture': x['texture'],
        'joints': [],
        'polygons': [],
        'animations': x['animations']
    }

    # adjust position so that each one refers to parent
    joint_data = {}
    root = ''
    for k in x['joints']:
        joint_data[k['id']] = {}
        joint_data[k['id']]['root'] = k.get('root', False)
        joint_data[k['id']]['pos'] = k['pos']
        joint_data[k['id']]['parent'] =  k.get('parent',None)
        joint_data[k['id']]['children'] = []
        
    for key, value in joint_data.items():
        if value['parent'] is not None:
            joint_data[value['parent']]['children'].append(key)
        if value['root']==True:
            root = key
    l = [root]
    while l:
        currentJoint = l.pop(0)
        joint = joint_data[currentJoint]
        pos = vec3(l=joint['pos'])
        pos.y = tex_height - pos.y
        ppos = None
        if joint['parent'] is not None:
            ppos = vec3(l=joint_data[joint['parent']]['pos'])
            ppos.y = tex_height - ppos.y
        else:
            ppos = origin
        print(str(pos))
        print(str(ppos))
        joint_data[currentJoint]['relpos'] = (pos - ppos)
        for child in joint['children']:
            l.append(child)

    for k,v in joint_data.items():
        p = v['relpos']
        j = {
            'id': k,
            'pos': [p.x,p.y,p.z],
            'root': v['root']
        }
        if v['parent'] is not None:
            j['parent'] = v['parent']
        out['joints'].append(j)
        


    # prepare skin
    for k in x['polygons']:
        id = k['id']
        po = {
            'id': id,
            'points': []
        }
        for vertex in grouper(k['points'], 9, 0):
            print(vertex)
            po['points'].extend( [
                vertex[0] - origin.x,
                (tex_height - vertex[1]) - origin.z,
                vertex[2],
                vertex[0],
                vertex[1],
                vertex[3],
                vertex[4],
                vertex[5],
                vertex[6],
                vertex[7],
                vertex[8]
            ])
        out['polygons'].append(po)
    print(out)

    return out
        








asset_fac = {
    'asset.sprite': identity,
    'asset.skeletalmodel': identity,
    'asset.skeletalanimation': identity,
    'custom.model1': ms1
}
asset_loc = {
    'asset.sprite': 'models',
    'asset.skeletalmodel': 'models',
    'asset.skeletalanimation': 'skeletalanimations',
    'custom.model1': 'models'

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
                    print ('stored ' + key)
                    


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

        


        
