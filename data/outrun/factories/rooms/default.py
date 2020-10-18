#from smb_py.factories.rooms.room import PlatformerRoom
from lib_py.room import Room
from lib_py.engine import data
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

    return r
