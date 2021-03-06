import example
import yaml
import sys

from lib_py.scumm.entity import WalkArea, BackgroundItem
from lib_py.shape import Polygon, LinY, Graph
from lib_py.scumm.scumm import Data, State
from lib_py.scumm.builder.item import buildItem
from lib_py.builder.build import make_object
from lib_py.entity import Text, TextAlignment
from lib_py.components import Cursor


def addBackground(room, r):
    if 'bg' in room:
        for bg in room['bg']:
            image = bg['image']
            pos = bg.get('pos', [0,0,0])
            r.add (BackgroundItem(image = image, pos = pos), 'main')

def addWalkareas(room, r):
    if 'walkareas' in room:
        for wa in room['walkareas']:                        
            shape = None
            if wa['type'] == 'poly':
                shape = Polygon(outline = wa['outline'])
            elif wa['type'] == 'polyline':
                shape = Graph(nodes = wa['nodes'], edges=wa['edges'])  
            d = wa.get('depth', None)
            depth = None
            if d == 'auto':
                depth = LinY (0,1,room['height'],0)                        
            sc = wa.get('scale', None)
            scale = None
            bl = wa.get('blocked_lines',None)
            if sc:
                scale = make_object(sc)
            r.add (WalkArea(tag = 'walkarea', shape = shape, depth = depth, scale = scale, blocked_lines = bl), 'main')

def addDynamicEntities(roomid, r):
    if roomid in Data.locator:
        for key, value in Data.locator[roomid].items():
            print ('found item: ' + key)
            d = Data.items[key]
            node = d.get('node', 'main')
            # check if item is owned
            if not State.has(key):
                e = buildItem (key)
                r.add(e, node)



def makeStandardRoom(roomid, room):
    from lib_py.scumm.room import RoomUI
    collide = room.get ('collide', False)
    r = RoomUI(id= room['id'], width = room['width'], height = room['height'], collide=collide)
    # add background
    addBackground (room, r)
    addWalkareas (room, r)
    addDynamicEntities (roomid, r)    
    return r

def makeDialogueRoom(roomid, room):
    from lib_py.scumm.room import RoomUI
    r = RoomUI(id= room['id'], width = room['width'], height = room['height'], addui=False)
    # add background
    addBackground (room, r)
    #addWalkareas (room, r)
    addDynamicEntities (roomid, r)    
    return r

def makeFullscreenRoom(roomid, room):
    from lib_py.scumm.room import RoomFullscreen
    r = RoomFullscreen(id= room['id'], width = room['width'], height = room['height'])
    # add background
    addBackground (room, r)
    addWalkareas (room, r)
    addDynamicEntities (roomid, r)

    # add cursor to highlight map locations
    e = Text(font='monkey', text='', color = [255,255,255,255], align = TextAlignment.bottom, tag='cursor')
    e.addComponent (Cursor())
    r.add(e, 'main')
    return r


roomFactories = {
    'standard': makeStandardRoom,
    'full': makeFullscreenRoom,
    'dialogue': makeDialogueRoom
}

def makeRoom (roomid: str):
    filename = example.dir +'/rooms/'+ roomid+ '.yaml'
    try:
        with open(filename) as f:
            room = yaml.load(f, Loader=yaml.FullLoader)
            rtype = room.get('type', 'standard')
            if rtype in roomFactories:
                return roomFactories[rtype](roomid, room)
            else:
                raise BaseException("Don't know how to build room " + roomid + " because of unknwon type " + rtype)
    except EnvironmentError as error:
        print (error)
        sys.exit(1)