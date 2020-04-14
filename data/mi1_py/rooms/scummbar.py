import lib_py.engine as engine
import lib_py.scumm.room as room
import lib_py.scumm.actions as act
import lib_py.scumm.entity as se
import lib_py.shape as sh
from lib_py.script import Script
from lib_py.scumm.scumm import State
import example    

def builder():
    r =  room.RoomUI(id='scummbar', width = 640, height = 144)
    r.add (se.BackgroundItem(image='gfx/scummbar_1.png', pos = [0, 0, -1]), 'main')
    r.add (se.WalkArea (tag='walkarea', shape = sh.Polygon(
        outline = [32, 16, 70, 24, 128, 19, 251, 18, 311, 10, 321, 10, 345, 32, 467, 41,
 			492, 50, 514, 40, 565, 40, 580, 35, 629, 6, 626, 0, 256, 0, 200, 16, 149, 0, 90, 0, 85, 10]),
        depth = sh.LinY(y0=0,z0=1,y1=144,z1=0)), 'main')
    r.add (se.Sprite (item='scummbar.door.out', anim = State.variables['door.village.scummbar'], model='door_scummbar_village', pos = [32, 24, 0]), 'main')
    print (State.items['scummbar.door.out'].walkto)

    r.addDynamicItems()
    return r

engine.addRoom (id = 'scummbar', f=builder)
