import lib_py.engine as engine
import lib_py.scumm.room as room
import lib_py.scumm.actions as act
import lib_py.scumm.entity as se
import lib_py.shape as sh
from lib_py.script import Script
from lib_py.scumm.scumm import State
import mi1_py.variables as var
import example

roomId = 'village2'
width = 480
height = 144

def init():
    # init stuff here
    return

def builder():
    r =  room.RoomUI(id = roomId, width = 480, height = 144)
    r.add (se.BackgroundItem(image='gfx/village2.png', pos = [0, 0, -1]), 'main')

    r.add (se.WalkArea (
        tag='walkarea', 
        shape = sh.Polygon(outline = [0, 24, 123, 63, 199, 63, 299, 30, 377, 30, 385, 35, 454, 35, 470, 0, 0]),
        depth = sh.LinY (y0=0, z0=1, y1 = 144, z1 = 0)), 'main')

    r.addItem (id = 'village2.archway')
    r.addItem (id = 'village2.village3')
    r.addItem (id = 'lmf')
    
    r.addItem (id='citizen', parent='walkarea')
    r.addItem (id='lmf1', parent='walkarea')
    r.addItem (id='lmf2', parent='walkarea')
    r.addItem (id='lmf3', parent='walkarea')
    r.addItem (id='village2.rat', parent='walkarea')

    r.addDynamicItems()
    r.init.append(init)
    #print (State.items['scummbar.door.out'].walkto)
    return r

engine.addRoom (id = roomId, f=builder)