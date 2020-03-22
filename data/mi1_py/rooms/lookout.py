import settings

import lib_py.room as room
import lib_py.entity as entity

def builder():
    r = room.RoomUI(width=320, height=200)
    #r.add()
    return r


settings.monkey.rooms['lookout'] = builder
#settings.engine['rooms']['lookout'] = builder