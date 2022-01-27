from mopy.factories.basicroom import BasicRoom
import mopy
from mopy.runners import KeyListener, CollisionEngine3D, Scheduler
import example
from mopy.entity import Entity
from mopy.camera import Camera25


def ciao(desc):
    r = PlatformerRoom3D(desc)
    r.add_items(desc)
    return r


def restart():
    example.restart()


class PlatformerRoom3D(BasicRoom):
    def __init__(self, desc):
        super().__init__(desc) #, 384, 224)
        #width =
        #height = 240
        #device_width = monkey.engine.device_size[0]
        #device_height = monkey.engine.device_size[1]
        device_size = mopy.monkey.engine.device_size
        device_width = device_size[0]
        device_height = device_size[1]
        width = desc['width']
        height = desc['height']

        keyl = KeyListener()
        keyl.add_key(key=299, func=restart)
        self.add_runner(keyl)

        main = Entity(tag='main')
        cam = Camera25(width, height, device_width, device_height, [0, 0, device_width, device_height])
        #cam = camera.PerspectiveCamera(viewport=[0, 0, 320, 240])
        cam.tag = 'maincam'
        cam.pos = (5, 0, 1)
        #cam.bounds = world_bounds
        #cam.boundsz = [-100, 22]
        main.camera = cam

        self.main = main
        self.add(main)

        ce = CollisionEngine3D(80, 80, 80)            # this will be a 3d engine
        #ce.add_response(vars.tags.player, vars.tags.ladder, runners.CollisionResponse(on_enter=func.on_enter_ladder_area, on_leave=func.on_leave_ladder_area))
        #ce.add_response(vars.tags.player, vars.tags.spawn, runners.CollisionResponse(on_enter=func.spawn))
        #ce.add_response(vars.tags.player_attack, vars.tags.foe, runners.CollisionResponse(on_enter=func.player_hits_foe))
        #ce.add_response(vars.tags.foe_attack, vars.tags.player, runners.CollisionResponse(on_enter=func.foe_hits_player))

        self.add_runner(ce)
        self.add_runner(Scheduler())

        # diag = Entity(tag='diag')
        # fsize = 8
        # pad = 3 * fsize
        # w = 320
        # h = 240
        # diag.camera = camera.OrthoCamera(world_width=w, world_height=h,
        #                                   cam_width=w, cam_height=h, viewport=[0, 0, w, h], tag='diagcam')
        # self.add(diag)

    def addToDynamicWorld(self, e):
        self.dw.items.append(e)