import lib_py.engine as engine
import lib_py.scumm.room as room
import lib_py.scumm.actions as act
import lib_py.scumm.entity as se
import lib_py.shape as sh
from lib_py.script import Script
from lib_py.scumm.scumm import State
import mi1_py.variables as var
import example

roomId = 'village3'
width = 800
height = 144

def init():
    # init stuff here
    return

def builder():
    r =  room.RoomUI(id = roomId, width = width, height = height)
    r.add (se.BackgroundItem(image='gfx/village3_1.png', pos = (0, 0, -1)), 'main')
    r.add (se.BackgroundItem(image='gfx/village3_2.png', pos = (166, 0, 2)), 'main')
    r.add (se.WalkArea (
        tag='walkarea', 
        shape = sh.Polygon(outline = [406,49,425,49,436,63,494,63,494,42,594,42,594,71,600,71,638,23,745,23,752,17,770,17,770,10,762,10,775,0,374,0,396,22]),
        depth = sh.LinY (y0=0, z0=1, y1 = 144, z1 = 0)), 'main')

    r.addDynamicItems()
    r.init.append(init)
    return r

engine.addRoom (id = roomId, f=builder)