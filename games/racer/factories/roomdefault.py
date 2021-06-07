import room
from entity import Entity, Text, TextAlignment, Sprite
import runners
import camera
import vars
import func
import monkey
import components as comp

class Road:
    def __init__(self):
        self.type = 'racer.components.road'


def make_platformer_room(room: dict):
    vars.disable_update_on_start = dict()
    room_d = room['id']
    visible_name = room['label']
    width = room['width']
    height = room['height']
    vars.time = room['time']
    # the world size (in tiles)
    world_width = room['world_width']
    world_height = room['world_height']
    start = room['start'][vars.start_pos]
    start_pos = start['pos']
    r = PlatformerRoom(visible_name, width, height, world_width, world_height, start_pos)
    if 'items' in room:
        for item in room['items']:
            factory_id = item['factory']
            dynamic = item.get('dynamic', True)
            factory = monkey.engine.get_item_factory(factory_id[0])
            if factory is None:
                print('Unable to find factory for item: ' + factory_id[0])
                exit(1)
            else:
                props = {} if len(factory_id) == 1 else factory_id[1]
                f = factory(**props)
                for a in item['d']:
                    e = f(*a)
                    if dynamic:
                        r.addToDynamicWorld(e)
                    else:
                        r.main.add(e)
    if 'script' in start:
        r.init.append(getattr(func, start['script']))
    return r
    return r


class PlatformerRoom(room.Room):
    def __init__(self, uid: str, width, height, world_width: int, world_height: int, start_pos):
        super().__init__(uid, width, height)

        keyl = runners.KeyListener()
        # adding pause button
        keyl.add_key(key=32, func=func.toggle_pause)
        # restart on F10
        keyl.add_key(key=299, func=func.restart)
        self.add_runner(keyl)

        # self.keyl.addKey(key=264, func = checkWarp)

        main = Entity(tag='main')
        main.camera = camera.OrthoCamera(world_width=world_width * vars.tile_size,
                                         world_height=world_height * vars.tile_size,
                                         cam_width=width, cam_height=height, viewport=[0, 0, width, height],
                                         tag='maincam')
        self.main = main
        self.add(main)

        # create the collision engine
        ce = runners.CollisionEngine(85, 85)
        self.add_runner(ce)

        self.add_runner(runners.Scheduler())

        self.dw = runners.DynamicWorld(256, 256, 'maincam')
        self.add_runner(self.dw)

        diag = Entity(tag='diag')
        diag.camera = camera.OrthoCamera(world_width=width, world_height=height,
                                         cam_width=width, cam_height=height, viewport=[0, 0, width, height], tag='diagcam')

        fps_count = Text('main', 8, '0', [255, 255, 255, 255], align=TextAlignment.top_left, tag='fps', pos=(0, 256, 2))
        fps_count.add_component(comp.FPSCounter())
        diag.add(fps_count)

        self.add(diag)
        e = Entity()
        e.add_component(Road())
        main.add(e)
        # add player
        # mario = monkey.engine.get_item_factory('player')()(start_pos[0], start_pos[1], 0)
        # #mario = build.makePlayer(vars.stateInfo[vars.state], startPos[0], startPos[1])
        # main.add(mario)

    def addToDynamicWorld(self, e):
        self.dw.items.append(e)
