from mopy.room import Room
from mopy.entity import Entity
from mopy.camera import OrthoCamera, PerspectiveCamera
import mopy.monkey as monkey



class BasicRoom(Room):
    def __init__(self, room_info):
        super().__init__(room_info['id'])
        main = Entity(tag='main')
        cam_type = room_info.get('cam', 'ortho')
        device_size = monkey.engine.device_size
        cam = None
        bounds = room_info['bounds']
        if cam_type == 'perspective':
            cam = PerspectiveCamera(viewport=[0, 0, device_size[0], device_size[1]])
            cam.pos = (5, 5, 15)
            cam.boundsz = bounds['z']
        else:
            exit(1)
        cam.bounds = [bounds['x'][0], bounds['y'][0], bounds['x'][1], bounds['y'][1]]
        cam.tag = 'maincam'
        main.cam = cam
        self.main = main
        self.add(main)
        # now add all items
        if 'items' in room_info:
            for item in room_info['items']:
                factory_id = item['factory']
                factory = monkey.engine.get_item_factory(factory_id[0])
                if factory is None:
                    print('Unable to find factory for item: ' + factory_id[0])
                    exit(1)
                else:
                    props = {} if len(factory_id) == 1 else factory_id[1]
                    f = factory(**props)
                    parent = item.get('parent', 'main')
                    for a in item['d']:
                        e = f(*a)
                        self.add(e, parent)
    @staticmethod
    def make(room_info):
        return BasicRoom(room_info)


