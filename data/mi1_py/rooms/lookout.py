import lib_py.room as room
import lib_py.engine as engine
import lib_py.shape as sh
# import lib_py.components as compo

import lib_py.scumm.scumm as scumm
import lib_py.scumm.room as room
import lib_py.scumm.entity as se

import example

def a1():
    #du: example.Wrap1 = example.get('ui')
    #du.setActive(False)
    #dd: example.Wrap1 = example.get('dialogue')
    #print (type(dd.appendText))
    #dd.appendText('Questo ciao nello')    
    print ('LLLLLLLLLLLLLLLLLLLLLLLLOKKO')

def builder():
    r =  room.RoomUI(id='lookout', width = 320, height = 200)

    #r = scumm.RoomUI(width=320, height=200)
    # sfondo = entity.Entity()
    # sfondo.addComponent (compo.Gfx(image='gfx/lookout_1.png'))
	# 	{ pos = {81, 16, 3}, components = { { type="gfx", image="lookout_2.png" }}},
    #     { pos = {294, 33, 3}, components = { { type="gfx", image ="lookout_3.png" }}},
    #     { pos = {226, 0, 3}, components = { { type="gfx", image="lookout_4.png" }}},

    # r.add(sfondo, 'main')
    r.add (se.BackgroundItem(image='gfx/lookout_1.png', pos = [0,0,-1]), 'main')
    r.add (se.BackgroundItem(image='gfx/lookout_2.png', pos = [81, 16, 3]), 'main')
    r.add (se.BackgroundItem(image='gfx/lookout_3.png', pos = [294, 33, 3]), 'main')
    r.add (se.BackgroundItem(image='gfx/lookout_4.png', pos = [226, 0, 3]), 'main')
    r.add (se.WalkArea (tag='walkarea', shape = sh.Polygon (
        outline = [203,51,315,62,315,40,293,40,260,10,260,0,260,-20,234,-20,234,0,234,10,221,26,152,33,152,51]
    ), depth=sh.LinY(y0=0,z0=1,y1=144,z1=0)), 'main')
    r.add (se.Sprite (model = 'fire', pos = [126, 52, 0]), 'walkarea')
    r.add (se.Sprite (item = 'lookout.stairs', pos = [230,0,0]), 'main')
    r.add (se.Character (item='lookout.lookout', model='lookout', speed = 100, dir = 'w', state='idle', text_color=[170, 170, 170, 255], text_offset=[0,60], pos = [114,36,0]), 'walkarea')
    r.addDynamicItems()

    r.init.append(a1)
    #r.add()
    return r

engine.addRoom (id = 'lookout', f=builder)
#settings.monkey.rooms['lookout'] = builder
#settings.engine['rooms']['lookout'] = builder