from smb_py.room import PlatformerRoom
import lib_py.engine as engine
import smb_py.factories as fact
import example
import yaml

def builder():
    r = PlatformerRoom(
        id = 'world1_1', 
        width = 256, 
        height = 256, 
        worldWidth = 224, 
        worldHeight = 16, 
        playerModel = 'mario', 
        startPos = [2, 2])

    with open(example.dir+ '/rooms/world1_1.yaml') as f:
        rooms = yaml.load(f, Loader=yaml.FullLoader)
        for a in rooms['room']:
            f = a['template'][0]
            args = a['template'][1:]
            print (args)
            method_to_call = getattr(fact, f, None)
            if method_to_call:
                template = method_to_call(*args)
                print (f + ' found')
                for im in a['d']:
                    print (im)
                    e = template(*im)
                    r.addToDynamicWorld(e)
            else:
                print (f + ' not found')

    return r

engine.addRoom (id = 'world1_1', f=builder)
