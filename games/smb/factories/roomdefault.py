import room
from entity import Entity, Text, TextAlignment, Sprite
import runners
import camera
import vars
import func
from engine import engine


def make_platformer_room(room: dict):
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
    print('ok')
    exit(1)


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
                                         world_height=world_width * vars.tile_size,
                                         cam_width=width, cam_height=height, viewport=[0, 0, width, height],
                                         tag='maincam')
        self.main = main
        self.add(main)

        # create the collision engine
        ce = runners.CollisionEngine(80, 80)
        ce.add_response(vars.tags.player, vars.tags.brick_sensor, runners.CollisionResponse(on_enter=func.brick_response))
        ce.add_response(vars.tags.player, vars.tags.bonus_brick_sensor, runners.CollisionResponse(on_enter=func.bonus_brick_response))
        ce.add_response(vars.tags.player, vars.tags.mushroom, runners.CollisionResponse(on_enter=func.mushroom_response))
        ce.add_response(vars.tags.player, vars.tags.warp, runners.CollisionResponse(on_enter=func.on_warp_enter, on_leave=func.on_warp_exit))
        ce.add_response(vars.tags.player, vars.tags.hotspot, runners.CollisionResponse(on_enter=func.hotspotEnter))
        ce.add_response(vars.tags.player, vars.tags.coin, runners.CollisionResponse(on_enter=func.coin_response))
        ce.add_response(vars.tags.player, vars.tags.goomba, runners.CollisionResponse(on_enter=func.goombaResponse))
        ce.add_response(vars.tags.player, vars.tags.koopa, runners.CollisionResponse(on_enter=func.koopaResponse))
        ce.add_response(vars.tags.player, vars.tags.spawn, runners.CollisionResponse(on_enter=func.onSpawn))
        ce.add_response(vars.tags.player, vars.tags.key, runners.CollisionResponse(on_enter=func.onCollectItem))
        ce.add_response(vars.tags.goomba, vars.tags.player_fire, runners.CollisionResponse(on_enter=func.fireHitsFoe))
        self.add_runner(ce)

        self.add_runner(runners.Scheduler())

        self.dw = runners.DynamicWorld(256, 256, 'maincam')
        self.add_runner(self.dw)

        diag = Entity(tag='diag')
        diag.camera = camera.OrthoCamera(world_width=width, world_height=height,
                                         cam_width=width, cam_height=height, viewport=[0, 0, width, height], tag='diagcam')
        diag.add(Text('main', 8, engine.getString('mario'), [255, 255, 255, 255], TextAlignment.topleft, pos=(24, 248, 2)))
        diag.add(Text('main', 8, '{:06d}'.format(vars.score), [255, 255, 255, 255], TextAlignment.topleft, tag='score_label', pos=(24, 240, 2)))
        diag.add(Text('main', 8, engine.getString('world'), [255, 255, 255, 255], TextAlignment.topleft, pos=(144, 248, 2)))
        diag.add(Text('main', 8, uid, [255, 255, 255, 255], TextAlignment.top, pos=(164, 240, 2)))
        diag.add(Text('main', 8, engine.getString('time'), [255, 255, 255, 255], TextAlignment.topright, pos=(232, 248, 2)))
        diag.add(Text('main', 8, str(vars.time), [255, 255, 255, 255], TextAlignment.topright, tag='score_label', pos=(232, 240, 2)))
        diag.add(Sprite(model='coin_counter', pos=(96, 232, 2)))
        diag.add(Text('main', 8, 'x', [255, 255, 255, 255], pos=(108, 240, 2)))
        diag.add(Text('main', 8, '{:02d}'.format(vars.coins), [255, 255, 255, 255], TextAlignment.topleft, tag='coin_label', pos=(116, 240, 2)))
        fps_count = Text('main', 8, '0', [255, 255, 255, 255], align=TextAlignment.topleft, tag='fps', pos=(0, 256, 2))
        fps_count.add_component(FPSCounter())
        diag.add(fps_count)

        self.add(diag)

        # add player
        mario = build.makePlayer(vars.stateInfo[vars.state], startPos[0], startPos[1])
        main.add(mario)

    def addToDynamicWorld(self, e):
        self.dw.items.append(e)
