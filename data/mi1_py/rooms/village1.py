import lib_py.engine as engine
import lib_py.scumm.room as room
import lib_py.scumm.entity as se
import lib_py.shape as sh

def builder():
    r =  room.RoomUI(id='village1', width = 1008, height = 144)
    r.add (se.BackgroundItem(image='gfx/village1_1.png', pos = [0,0,-1]), 'main')
    r.add (se.WalkArea (tag='walkarea', shape = sh.Graph(
        nodes = [ [8, 71], [23, 63], [49, 49], [40, 37], [56, 24], [84, 13], [770, 13], [780,34], [1000,34]],
        edges = [ [0, 1], [1, 2], [2, 3], [3, 4], [4, 5], [5, 6], [6, 7], [7, 8]]),
        scale = sh.LinY(y0=0, z0=0.8, y1 = 144, z1 = 0.1),
        depth = sh.LinY(y0=0,z0=1,y1=144,z1=0)), 'main')
    r.addDynamicItems()

    return r

engine.addRoom (id = 'village1', f=builder)
