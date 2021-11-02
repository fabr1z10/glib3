from mopy.room import Room
from mopy.entity import Entity
from mopy.camera import OrthoCamera, PerspectiveCamera
import mopy.monkey as monkey


class BasicRoom(Room):
    def __init__(self, room_info):
        super().__init__(room_info['id'])
        main = Entity(tag='main')
        cam = room_info.get('cam', None)
        device_size = monkey.engine.device_size
        if cam:
            cam_type = cam['type']
            camera = None
            if cam_type == 'ortho':
                world_size = cam['world_size']
                cam_size = cam['cam_size']

                viewport = cam.get('viewport', [0, 0, monkey.engine.device_size[0], monkey.engine.device_size[1]])
                camera = OrthoCamera(world_size[0], world_size[1], cam_size[0], cam_size[1],
                                  viewport, tag='maincam')
                camera.pos = (160, 120, 5)
            elif cam_type == 'perspective':
                cam = PerspectiveCamera(viewport=[0, 0, device_size[0], device_size[1]])
                cam.pos = (5, 5, 15)
                bounds = cam['bounds']
                cam.boundsz = bounds['z']
                cam.bounds = [bounds['x'][0], bounds['y'][0], bounds['x'][1], bounds['y'][1]]
            else:
                print('Unknown camera type: ' + cam_type)
                exit(1)
            camera.tag = 'maincam'
            main.camera = camera
        self.main = main
        self.add(main)
        # now add all items
        if 'items' in room_info:
            for item in room_info['items']:
                entity_desc = item['entity']
                factory = monkey.engine.get_item_factory(entity_desc['type'])
                if not factory:
                    print('Don''t have factory for item: ' + item['type'])
                    exit(1)
                e = factory(entity_desc)
                self.add(e, 'main')
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
        return BasicRoom(room_info)


