import lib_py.room as room
import lib_py.engine as engine
# import lib_py.components as compo

import lib_py.scumm.scumm as scumm
# import lib_py.entity as entity

def builder():
    r = scumm.room.RoomUI(width=320, height=200)

    #r = scumm.RoomUI(width=320, height=200)
    # sfondo = entity.Entity()
    # sfondo.addComponent (compo.Gfx(image='gfx/lookout_1.png'))
	# 	{ pos = {81, 16, 3}, components = { { type="gfx", image="lookout_2.png" }}},
    #     { pos = {294, 33, 3}, components = { { type="gfx", image ="lookout_3.png" }}},
    #     { pos = {226, 0, 3}, components = { { type="gfx", image="lookout_4.png" }}},

    # r.add(sfondo, 'main')
    r.add (scumm.entity.BackgroundItem(image='gfx/lookout_1.png'), 'main')
    r.add (scumm.entity.BackgroundItem(image='gfx/lookout_2.png', pos = [81, 16, 3]), 'main')
    r.add (scumm.entity.BackgroundItem(image='gfx/lookout_3.png', pos = [294, 33, 3]), 'main')
    r.add (scumm.entity.BackgroundItem(image='gfx/lookout_4.png', pos = [226, 0, 3]), 'main')
    #r.add (scumm.Sprite (sprite = 'lookout.fire'), 'main')


    #r.add()
    return r

engine.addRoom (id = 'lookout', f=builder)
#settings.monkey.rooms['lookout'] = builder
#settings.engine['rooms']['lookout'] = builder