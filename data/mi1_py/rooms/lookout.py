import settings
import lib_py.components as compo

import lib_py.scumm as scumm
import lib_py.entity as entity

def builder():
    r = scumm.RoomUI(width=320, height=200)
    sfondo = entity.Entity()
    sfondo.addComponent (compo.Gfx(image='gfx/lookout_1.png'))

    r.add(sfondo, 'main')
    #r.add()
    return r


settings.monkey.rooms['lookout'] = builder
#settings.engine['rooms']['lookout'] = builder