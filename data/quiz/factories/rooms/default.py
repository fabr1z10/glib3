#from smb_py.factories.rooms.room import PlatformerRoom
from lib_py.room import Room
from lib_py.engine import data
import lib_py.components as compo
import lib_py.runner as run
import lib_py.entity as entity
import lib_py.camera as cam
import smb_py.vars as vars
import smb_py.scripts as scripts


def defaultRoom (room):
    roomId = room['id']   
    visibleName = room['label'] 
    width = room['width']
    height = room['height']

    r = Room(
        id = visibleName,
        width = width,
        height = height)
    r.addRunner (run.Scheduler())

    camWidth = 320
    camHeight = 144
    
    main = entity.Entity (tag='main')
    main.camera = cam.OrthoCamera(320, 144, 320, 144, [0, 56, 320, 144], tag='maincam')
    r.add(main)
    ui = entity.Entity (tag='ui')
    ui.camera = cam.OrthoCamera(320, 56, 320, 56, [0, 0, 320, 56], tag = 'uicam')
    r.add(ui)     
    b = entity.Entity()
    b.addComponent ( compo.Gfx(image='gfx/raftrasf.jpg', height=144))
    r.add(b, 'main')
    return r