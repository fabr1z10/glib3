import lib_py.room as room
import lib_py.engine as engine
import lib_py.shape as sh
# import lib_py.components as compo

import lib_py.scumm.scumm as scumm
import lib_py.scumm.room as room
# import lib_py.entity as entity

def builder():
    r =  room.RoomUI(id='lookout', width = 320, height = 200)

    #r = scumm.RoomUI(width=320, height=200)
    # sfondo = entity.Entity()
    # sfondo.addComponent (compo.Gfx(image='gfx/lookout_1.png'))
	# 	{ pos = {81, 16, 3}, components = { { type="gfx", image="lookout_2.png" }}},
    #     { pos = {294, 33, 3}, components = { { type="gfx", image ="lookout_3.png" }}},
    #     { pos = {226, 0, 3}, components = { { type="gfx", image="lookout_4.png" }}},

    # r.add(sfondo, 'main')
    r.add (scumm.entity.BackgroundItem(image='gfx/lookout_1.png', pos = [0,0,-1]), 'main')
    r.add (scumm.entity.BackgroundItem(image='gfx/lookout_2.png', pos = [81, 16, 3]), 'main')
    r.add (scumm.entity.BackgroundItem(image='gfx/lookout_3.png', pos = [294, 33, 3]), 'main')
    r.add (scumm.entity.BackgroundItem(image='gfx/lookout_4.png', pos = [226, 0, 3]), 'main')
    r.add (scumm.entity.WalkArea (tag='walkarea', shape = sh.Polygon (
        outline = [203,51,315,62,315,40,293,40,260,10,260,0,260,-20,234,-20,234,0,234,10,221,26,152,33,152,51]
    )), 'main')
    r.add (scumm.entity.Sprite (model = 'fire', pos = [126, 52, 0]), 'walkarea')
    r.addDynamicItems()

    #r.add()
    return r

engine.addRoom (id = 'lookout', f=builder)
#settings.monkey.rooms['lookout'] = builder
#settings.engine['rooms']['lookout'] = builder