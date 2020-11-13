from wboy.factories.rooms.room import PlatformerRoom
from lib_py.engine import data
import wboy.vars as vars
#import wboy.scripts as scripts


def defaultRoom (room):
    roomId = room['id']   
    width = room['width']
    height = room['height']
    vars.time = room['time']
    world_width = room['world_width']
    world_height = room['world_height']
    start = room['start'][vars.start_pos]
    start_pos = start['pos']

    r = PlatformerRoom(
        id = roomId,
        width = width,
        height = height,
        worldWidth = world_width, 
        worldHeight = world_height, 
        startPos = start_pos)

    if 'items' in room:
        for item in room['items']:
            print (item)
            factoryId = item['factory']
            dynamic = item.get('dynamic', True)
            factory = data['factories']['items'].get(factoryId[0], None)
            if factory is None:
                print ('Unable to find factory for item: ' + factoryId[0])
                exit(1)
            else:
                f = factory(factoryId)
                for a in item['d']:
                    e = f (a)
                    if dynamic:
                        r.addToDynamicWorld(e)
                    else:
                        r.main.add(e)
    if 'script' in start:
        r.init.append(getattr(scripts, start['script']))
    return r
