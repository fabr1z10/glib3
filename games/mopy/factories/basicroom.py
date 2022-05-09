from mopy.room import Room, build_entity
from mopy.entity import Entity
from mopy.camera import OrthoCamera, PerspectiveCamera
import mopy.monkey as monkey
from mopy.runners import KeyListener
import example
import mopy

def restart():
    print('suca')
    example.restart()


def play_script(s):
    def f(n):

        scr = mopy.monkey.engine.get_script(s).make()
        example.play(scr)
    return f



class BasicRoom(Room):
    def add_items(self, desc):
        for item in desc.get('items', []):
            p = item.get('pos', [0, 0, 0])
            pos = [ [p[i], p[i+1], p[i+2]] for i in range(0, len(p), 3)]
            parent = item.get('parent', self.default_item)
            # check if it's a reference to an asset
            condition = item.get('if', None)
            if condition:
                if not eval(str(condition[0]) + condition[1]):
                    continue
            entity_desc = monkey.engine.get_asset(item['ref'], item.get('args', None)) if 'ref' in item else item
            for position in pos:
                a = build_entity(entity_desc, position)
                self.add(a, parent)


    def __init__(self, desc):
        self.id = desc['id']
        aa = desc.get('vars', None)
        room_info = monkey.engine.repl_vars(desc, aa)
        super().__init__(room_info['id'])
        device_size = monkey.engine.device_size
        on_preload = room_info.get('on_preload', None)
        on_load = room_info.get('on_load', None)
        scripts = room_info.get('scripts', None)
        self.tile_size = getattr(monkey.engine.data.globals, 'tile_size', [1, 1])# monkey.engine.room_vars.get('tile_size', [1, 1])
        monkey.engine.data.globals.room_scaling = desc.get('scaling')
        if on_preload:
            on_preload(room_info)
        if on_load:
            func = on_load['func'] # operator.attrgetter(on_load['func'])(monkey.engine.scripts)
            args = on_load.get('args', None)
            self.init.append([func, args] if args else [func])
        if scripts:
            for s in scripts:
                self.init.append([play_script(s), None])
        cams = room_info.get('cam')
        self.main = None
        self.default_item = None
        if cams:
            for cam in cams:
                cam_type = cam['type']
                id = cam['id']
                main = Entity(tag=id)
                if self.default_item is None:
                    self.default_item = id
                camera = None
                if cam_type == 'ortho':
                    world_size = cam['world_size']
                    cam_size = cam['cam_size']
                    viewport = cam.get('viewport', [0, 0, monkey.engine.device_size[0], monkey.engine.device_size[1]])
                    camera = OrthoCamera(world_size[0], world_size[1], cam_size[0], cam_size[1],
                                  viewport, tag='maincam')
                    camera.pos = cam.get('pos', [0,0,5])
                    bounds = cam.get('bounds', {'x': [0, world_size[0]], 'y': [0, world_size[1]], 'z': [0, 100]})
                    camera.boundsz = bounds['z']
                    camera.bounds = [bounds['x'][0], bounds['y'][0], bounds['x'][1], bounds['y'][1]]
                elif cam_type == 'perspective':
                    world_size = cam['world_size']
                    camera = PerspectiveCamera(viewport=[0, 0, device_size[0], device_size[1]])
                    camera.pos = cam.get('pos', [0, 1, 5])
                    bounds = cam.get('bounds', {'x': [0, world_size[0]], 'y': [0, world_size[1]], 'z': [0, 100]})
                    camera.boundsz = bounds['z']
                    camera.bounds = [bounds['x'][0], bounds['y'][0], bounds['x'][1], bounds['y'][1]]
                else:
                    print('Unknown camera type: ' + cam_type)
                    exit(1)
                camera.tag = id + 'cam'
                main.camera = camera
                if not self.main:
                    self.main = main
                self.add(main)
        self.engines = room_info.get('engines', [])
        keyl = KeyListener()
        keyl.add_key(key=299, func=restart)
        self.add_runner(keyl)

                #self.add(im, 'main')
                # factory_id = item['factory']
                # factory = monkey.engine.get_item_factory(factory_id[0])
                # if factory is None:
                #     print('Unable to find factory for item: ' + factory_id[0])
                #     exit(1)
                # else:
                #     props = {} if len(factory_id) == 1 else factory_id[1]
                #     f = factory(**props)
                #     parent = item.get('parent', 'main')
                #     for a in item['d']:
                #         e = f(*a)
                #         self.add(e, parent)
    @staticmethod
    def make(room_info):
        b = BasicRoom(room_info)
        b.add_items(room_info)
        return b


