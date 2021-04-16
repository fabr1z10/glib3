import room
import vars
import entity
import camera as cam
import monkey
import factories.items
import components as compo
import func
import runners
#import scripts.actions

def default_room(desc: dict):
    id = desc['id']
    width = desc['width']
    height = desc['height']
    r = room.Room(id, width, height)
    r.add_runner(runners.Scheduler())
    # setup collision engine
    #ce = runners.CollisionEngine(80, 80)
    #ce.add_response(vars.Collision.Tags.player, vars.Collision.Tags.trap, runners.CollisionResponse(on_enter=func.on_enter_trap))
    #r.add_runner(ce)


    main = entity.Entity(tag='main')
    main.camera = cam.OrthoCamera(width, height, 316, 166, [2, 24, 316, 166], tag='maincam')
    main.add_component(compo.HotSpotManager(lmbclick=func.walkto))
    r.add(main)

    a = entity.Sprite(model='01/cursor')
    a.add_component(compo.Cursor())
    a.pos=(0,0,5)
    main.add(a)

    # now add all items
    if 'items' in desc:
        for item in desc['items']:
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
                    r.add(e, parent)
    # add dynamic items
    if id in vars.items_in_room:
        for key in vars.items_in_room[id]:
            item_desc = vars.items[key]
            tp = item_desc.get('type', None)
            if tp is None:
                print ('item ' + key + ' does not have type!')
                exit(1)
            print ('ciao ' + tp)
            factory = getattr(factories.items, tp)
            e = factory()(key, item_desc)
            if e is not None:
                parent = item_desc.get('parent', 'main')
                r.add(e, parent)
    return r