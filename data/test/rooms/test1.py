import lib_py.room as room
import lib_py.engine as engine
import lib_py.entity as e

import example

def builder():
    
    r =  room.Room(id='test1', width = 320, height = 200)

    r.add(e.Skeleton(model='prova'))



    return r

engine.addRoom (id = 'test1', f=builder)
#settings.monkey.rooms['lookout'] = builder
#settings.engine['rooms']['lookout'] = builder

