import room
from entity import Entity, Text, TextAlignment, Sprite
import runners
import camera
import vars
import func
import monkey



def make_platformer_room_3d(room: dict):
    room_d = room['id']
    vars.room_3d = True
    visible_name = room['label']
    world_width = room['world_width']
    world_height = room['world_height']
    vars.world_size = [world_width, world_height]
    #vars.z = room['z']
    r = PlatformerRoom3D(visible_name,(0, 10, 0, 10))
    if 'items' in room:
        for item in room['items']:
            factory_id = item['factory']
            factory = monkey.engine.get_item_factory(factory_id[0])
            if factory is None:
                print('Unable to find factory for item: ' + factory_id[0])
                exit(1)
            else:
                props = {} if len(factory_id) == 1 else factory_id[1]
                f = factory(**props)
                for a in item['d']:
                    e = f(*a)
                    r.main.add(e)
    if 'start_script' in room:
        r.init.append(getattr(func, room['start_script']))
    #r.init.append(func.compute_height)

    vars.max_enemies = room['max_enemies']
    #vars.foes = room['foes']
    #vars.prob_new_enemy = room['prob_new_enemy']
    #vars.enemies_to_kill = room['enemies_to_kill']
    #vars.next_room = room['next_room']
    vars.enemy_count = 0
    vars.enemy_killed = 0

    # TODO load models dynamically

    return r

# world_bounds is a tuple of 4 numbers xmin, ymin, xmax, ymax

class PlatformerRoom3D(room.Room):
    def __init__(self, uid: str, world_bounds):
        super().__init__(uid, 384, 224)
        #width =
        #height = 240
        keyl = runners.KeyListener()
        # adding pause button
        #keyl.add_key(key=32, func=func.toggle_pause)
        # restart on F10
        keyl.add_key(key=299, func=func.restart)
        self.add_runner(keyl)

        main = Entity(tag='main')
        cam = camera.Camera25(5216, 736, 384, 224, [0,0,384,224])
        #cam = camera.PerspectiveCamera(viewport=[0, 0, 320, 240])
        cam.tag = 'maincam'
        cam.pos = (5, 0, 1)
        #cam.bounds = world_bounds
        #cam.boundsz = [-100, 22]
        main.camera = cam

        self.main = main
        self.add(main)

        ce = runners.CollisionEngine3D(80, 80, 80)            # this will be a 3d engine
        #ce.add_response(vars.tags.foe_attack, vars.tags.player, runners.CollisionResponse(on_enter=func.foe_hits_player))
        #ce.add_response(vars.tags.player_attack, vars.tags.foe, runners.CollisionResponse(on_enter=func.player_hits_foe))
        # ce.add_response(vars.tags.foe_attack, vars.tags.player, runners.CollisionResponse(on_enter=func.foe_hits_player))
        # ce.add_response(vars.tags.player, vars.tags.foe, runners.CollisionResponse(on_enter=func.stomp_enemy))
        # ce.add_response(vars.tags.player, vars.tags.bonus, runners.CollisionResponse(on_enter=func.collect_bonus))
        # ce.add_response(vars.tags.player_attack, vars.tags.foe, runners.CollisionResponse(on_enter=func.player_hits_foe))
        # ce.add_response(vars.tags.player_attack, vars.tags.platform_destructible, runners.CollisionResponse(on_enter=func.player_hits_block))
        # ce.add_response(vars.tags.gib, vars.tags.platform, runners.CollisionResponse(on_enter=func.gib_lands))
        # ce.add_response(vars.tags.gib, vars.tags.platform_destructible, runners.CollisionResponse(on_enter=func.gib_lands))
        #
        # ce.add_response(vars.tags.fire, vars.tags.foe, runners.CollisionResponse(on_enter=func.fire_hits_foe))
        # ce.add_response(vars.tags.crusher, vars.tags.player, runners.CollisionResponse(on_enter=func.on_crusher_hit))

        self.add_runner(ce)
        self.add_runner(runners.Scheduler())

        diag = Entity(tag='diag')
        fsize = 8
        pad = 3 * fsize
        w = 320
        h = 240
        diag.camera = camera.OrthoCamera(world_width=w, world_height=h,
                                          cam_width=w, cam_height=h, viewport=[0, 0, w, h], tag='diagcam')
        #diag.add(Text('main', fsize, monkey.engine.read('$energy'), [255, 255, 255, 255], TextAlignment.top_left, pos=(pad, h-fsize, 2)))
        #diag.add(Text('main', fsize, str(vars.energy), [255, 255, 255, 255], TextAlignment.top_left, tag='energy_label', pos=(pad, h-fsize*2, 2)))
        # diag.add(Text('main', fsize, monkey.engine.read('$world'), [255, 255, 255, 255], TextAlignment.top_left, pos=(fsize*10, height-fsize, 2)))
        # diag.add(Text('main', fsize, uid, [255, 255, 255, 255], TextAlignment.top_left, pos=(fsize*10, height-2*fsize, 2)))
        #diag.add(Text('main', fsize, monkey.engine.read('$height'), [255, 255, 255, 255], TextAlignment.top_right, pos=(width-pad, height-fsize, 2)))
        #diag.add(Text('main', fsize, str(vars.height), [255, 255, 255, 255], TextAlignment.top_right, tag='height_label', pos=(width-pad, height-fsize*2, 2)))
        # fps_count = Text('main', fsize, '0', [255, 255, 255, 255], align=TextAlignment.top_left, tag='fps', pos=(0, height, 2))
        # fps_count.add_component(comp.FPSCounter())
        # diag.add(fps_count)

        self.add(diag)

    def addToDynamicWorld(self, e):
        self.dw.items.append(e)