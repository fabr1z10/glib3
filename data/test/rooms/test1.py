import lib_py.room as room
import lib_py.engine as engine
import lib_py.entity as entity
import lib_py.components as compo
import lib_py.entity as e

import example

def builder():
    
    r =  room.RoomBasic(id='test1', width = 320, height = 200)

    b = e.Skeleton(model='uomo1', pos =(160,100), anim='walkprova')
    b.scale = 0.5
    r.add(b, 'main')
    #a = entity.Entity(pos=(160,100))
    #a.addComponent(compo.Gfx(image='gfx/block1.png'))
    #r.add(a, 'main')

    return r

engine.addRoom (id = 'test1', f=builder)
#settings.monkey.rooms['lookout'] = builder
#settings.engine['rooms']['lookout'] = builder

