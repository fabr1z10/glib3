from smb_py.factories.rooms.room import PlatformerRoom
from lib_py.engine import data
import smb_py.vars as vars


def defaultRoom (room):
    roomId = room['id']   
    visibleName = room['label'] 
    width = room['width']
    height = room['height']
    vars.time = room['time']
    # the world size (in tiles)
    world_width = room['world_width']
    world_height = room['world_height']

    start_pos = room['start']

    r = PlatformerRoom(
        id = visibleName,
        width = width,
        height = height,
        worldWidth = world_width, 
        worldHeight = world_height, 
        startPos = start_pos)

    if 'items' in room:
        for item in room['items']:
            print (item)
            factoryId = item['factory']
            factory = data['factories']['items'].get(factoryId[0], None)
            if factory is None:
                print ('Unable to find factory for item: ' + factoryId[0])
                exit(1)
            else:
                f = factory(factoryId)
                for a in item['d']:
                    e = f (a)
                    r.addToDynamicWorld(e)
    return r