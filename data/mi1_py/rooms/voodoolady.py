import lib_py.engine as engine
import lib_py.scumm.room as room
import lib_py.scumm.actions as act
import lib_py.scumm.entity as se
import lib_py.shape as sh
from lib_py.script import Script
from lib_py.scumm.scumm import State
import mi1_py.variables as var
import example





roomId = 'voodoolady'
width = 496
height = 144

def init():
    # init stuff here
    # don't follow player!
    example.get('player').follow(False)
    
    return

def builder():
    r =  room.RoomUI(id = roomId, width = width, height = height)
    r.add (se.BackgroundItem(image='gfx/voodoolady1.png', pos = [0, 0, -1]), 'main')

    r.add (se.WalkArea (
        tag='walkarea', 
        shape = sh.Polygon(outline = [78,37,124,47,146,42,320,42,320,40,320,0,156,0,145,22]),
        depth = sh.LinY (y0=0, z0=1, y1 = 144, z1 = 0)), 'main')
    r.addItem (id = 'voodoolady.door', anim = var.doors.village_voodoolady)
    r.addItem (id= 'voodoolady.baskets', parent='walkarea')
    r.addItem (id= 'voodoolady.trunk', parent='walkarea')
    r.addItem (id= 'voodoolady.couch')
    r.addItem (id= 'voodoolady.chalice')
    r.addItem (id= 'voodoolady.knickknacks')
    r.addItem (id= 'voodoolady.statue')
    r.addItem (id= 'rubber.chicken')

    r.addDynamicItems()
    r.init.append(init)
    return r

engine.addRoom (id = roomId, f=builder)