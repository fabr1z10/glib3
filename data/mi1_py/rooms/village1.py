import lib_py.engine as engine
import lib_py.scumm.room as room
import lib_py.scumm.actions as act
import lib_py.scumm.entity as se
import lib_py.shape as sh
from lib_py.script import Script
from lib_py.scumm.scumm import State
import example

def init():
    if engine.previous_room == 'lookout':
        sc = Script(id = '_main')
        sc.addAction (act.Walk(pos = [280,10], tag='player'))
        example.play(sc)        

def builder():
    r =  room.RoomUI(id='village1', width = 1008, height = 144)
    r.add (se.BackgroundItem(image='gfx/village1_1.png', pos = [0, 0, -1]), 'main')
    r.add (se.BackgroundItem(image='gfx/village1_2.png', pos = [73, 0, 1]), 'main')
    r.add (se.BackgroundItem(image='gfx/village1_3.png', pos = [229, 0, 1]), 'main')
    r.add (se.BackgroundItem(image='gfx/village1_4.png', pos = [606, 0, 1]), 'main')
    r.add (se.WalkArea (tag='walkarea', shape = sh.Graph(
        nodes = [ [8, 71], [23, 63], [49, 49], [40, 37], [56, 24], [84, 13], [770, 13], [780,34], [1000,34]],
        edges = [ [0, 1], [1, 2], [2, 3], [3, 4], [4, 5], [5, 6], [6, 7], [7, 8]]),
        scale = sh.LinY(y0=0, z0=0.8, y1 = 144, z1 = 0.1),
        depth = sh.LinY(y0=0,z0=1,y1=144,z1=0)), 'main')
    r.add (se.Sprite (item='village1.poster', pos = [259, 27, 0]), 'main')
    r.add (se.Sprite (item='village1.door', anim = State.variables['door.village.scummbar'], model='door_village_scummbar', pos = [699, 7, 0]), 'main')
    r.addDynamicItems()
    r.init.append(init)
    print (State.items['scummbar.door.out'].walkto)
    return r

engine.addRoom (id = 'village1', f=builder)
