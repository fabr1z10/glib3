from mopy.room import Room
from mopy.entity import Entity
from mopy.camera import OrthoCamera, PerspectiveCamera
import mopy.monkey as monkey
from mopy.runners import KeyListener
import example
import operator
from mopy.util import tiles_to_world

def restart():
    example.restart()


class BasicRoom(Room):
    def add_items(self, desc):
        if 'items' in desc:
            for item in desc['items']:
                positions = item.get('pos', [0, 0, 0])
                parent = item.get('parent', self.default_item)
                entity_desc = item
                if 'ref' in item:
                    entity_desc = monkey.engine.get_asset(item['ref'], item.get('args', None))
                    print(entity_desc)
                factory = monkey.engine.get_item_factory(entity_desc['type'])
                if not factory:
                    print('Don''t have factory for item: ' + entity_desc['type'])
                    exit(1)
                for ip in range(0, len(positions), 3):
                    print(positions)
                    pos = positions[ip:ip+3]
                    e = factory(entity_desc)
                    if not e.auto_pos:
                        e.pos = tiles_to_world(pos, self.tile_size)
                    self.add(e, parent)

    def __init__(self, desc):
        aa = desc.get('vars', None)
        room_info = monkey.engine.repl_vars(desc, aa)
        super().__init__(room_info['id'])
        device_size = monkey.engine.device_size
        on_preload = room_info.get('on_preload', None)
        on_load = room_info.get('on_load', None)
        self.tile_size = getattr(monkey.engine.data.globals, 'tile_size', [1, 1])# monkey.engine.room_vars.get('tile_size', [1, 1])
        if on_preload:
            on_preload(room_info)
        if on_load:
            func = on_load['func'] # operator.attrgetter(on_load['func'])(monkey.engine.scripts)
            args = on_load.get('args', None)
            self.init.append([func, args] if args else [func])
        cams = room_info.get('cam')
        self.main = None
        self.default_item = None
        if cams:
            for cam in cams:
                cam_type = cam['type']
                id = cam['id']
                main = Entity(tag=id)
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
                    camera.pos = (5, 5, 15)
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


