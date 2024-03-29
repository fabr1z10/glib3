import mopy.room as room
#import mopy.engine as engine
import mopy.monkey as monkey
import mopy.entity as entity
import mopy.camera as cam
import data




import factories.items
import mopy.components as compo
import func
import mopy.runners as runners

import scripts


def map_room(desc: dict):
    id = desc['id']
    width = desc['width']
    height = desc['height']
    r = room.Room(id)#, width, height)
    r.add_runner(runners.Scheduler())

    # setup collision engine
    ce = runners.CollisionEngine(80, 80)
    ce.add_response(data.Collision.Tags.player, data.Collision.Tags.trap,
                    runners.CollisionResponse(on_enter=func.on_enter_trap))
    r.add_runner(ce)
    device_size = monkey.engine.device_size
    cam_width = device_size[0]
    cam_height = device_size[1]
    # # add the main node
    main = entity.Entity(tag='main')
    main.camera = cam.OrthoCamera(width, height, cam_width, cam_height, [0, 0, cam_width, cam_height],
                                  tag='maincam')
    main.add_component(compo.HotSpotManager(lmbclick=func.walkto))
    r.add(main)
    # # main.add (e.Text(font='ui', text='ciao', color = [255, 255, 255, 255], align = e.TextAlignment.bottom, pos = [camWidth/2, 16, 0]))
    on_load = desc.get('on_load', None)
    if on_load:
        r.init.append(getattr(scripts, on_load))

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

    cursor = entity.Text(font='monkey', size=8, text='', color=(255,255,255,255), tag='_cursor')
    cursor.add_component(compo.Cursor())

    main.add(cursor)
    # add dynamic items
    if id in data.items_in_room:
        for key in data.items_in_room[id]:
            item_desc = data.items[key]
            tp = item_desc.get('type', None)
            if tp is None:
                print('item ' + key + ' does not have type!')
                exit(1)
            print('ciao ' + key)
            factory = getattr(factories.items, tp)
            e = factory()(key, item_desc)
            if e is not None:
                parent = item_desc.get('parent', 'main')
                print('adding ' + key)
                r.add(e, parent)
    return r


def default_room(desc: dict):
    id = desc['id']
    width = desc['width']
    height = desc['height']
    r = room.Room(id)#, width, height)
    r.add_runner(runners.Scheduler())

    if 'on_start' in desc:
        r.on_start = getattr(scripts, desc['on_start'])

    # setup collision engine
    ce = runners.CollisionEngine(80, 80)
    ce.add_response(data.Collision.Tags.player, data.Collision.Tags.trap, runners.CollisionResponse(on_enter=func.on_enter_trap))
    r.add_runner(ce)
    print('uisize is ' + str(data.ui_height))
    device_size = monkey.engine.device_size
    cam_width = device_size[0]
    cam_height = device_size[1] - data.ui_height
    print ('device size is ' + str(monkey.engine.device_size))
    # # add the main node
    main = entity.Entity(tag='main')
    main.camera = cam.OrthoCamera(width, height, cam_width, cam_height, [0, data.ui_height, cam_width, cam_height], tag='maincam')
    main.add_component(compo.HotSpotManager(lmbclick=func.walkto))
    r.add(main)
    # # main.add (e.Text(font='ui', text='ciao', color = [255, 255, 255, 255], align = e.TextAlignment.bottom, pos = [camWidth/2, 16, 0]))
    verb_set = desc.get('verb_set', 0)
    # get current verb set
    vset = data.verb_sets[verb_set]
    dv = data.verbs[vset['default_verb']]
    data.current_verb = vset['default_verb']
    data.current_item_1 = ''
    data.current_item_2 = ''

    ui = entity.Entity(tag='ui')
    ui.camera = cam.OrthoCamera(cam_width, data.ui_height, cam_width, data.ui_height, [0, 0, cam_width, data.ui_height], tag='uicam')
    #monkey.engine.read(dv['text']
    ui.add(entity.Text(font='ui', size=8, text='mierda', color=data.Colors.current_action,
      align=entity.TextAlignment.bottom, tag='current_verb', pos=(cam_width / 2, 48, 0)))
    ui.add_component(compo.HotSpotManager())
    r.init.append(func.refresh_inventory)
    on_load = desc.get('on_load', None)
    if on_load:
        r.init.append(getattr(scripts, on_load))

    r.add(ui)
    cy = data.ui_height - 2 * data.font_size
    count = 0
    shift = 0
    shift_applied = 46
    for i in vset['verbs']:
        cx = (count // 4) * shift_applied
        cy = data.ui_height - (2 + count % 4) * data.font_size
        e = factories.items.make_verb_button(i, (cx, cy, 0))
        shift = max(shift, 1 + len(monkey.engine.read(data.verbs[i]['text'])))
        ui.add(e)
        count += 1
    # inventory node
    inventory_node = entity.TextView(factory=factories.items.make_inventory_button, pos=(160, 0), size=(160, 48),
                                     font_size=8, lines=6, delta_x=26, tag='inventory')
    inventory_node.add_component(compo.HotSpotManager())
    ui.add(inventory_node)

    # dialogue node
    dialogue_node = entity.TextView(factory=factories.items.make_dialogue_button, pos=(0, 0), size=(320, 56),
                                    font_size=8, lines=7, delta_x=26, tag='dialogue')
    dialogue_node.add_component(compo.HotSpotManager())
    r.add(dialogue_node)


#     inventory_node.addComponent(compo.HotSpotManager())


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
    if id in data.items_in_room:
        for key in data.items_in_room[id]:
            item_desc = data.items[key]
            tp = item_desc.get('type', None)
            if tp is None:
                print ('item ' + key + ' does not have type!')
                exit(1)
            print ('ciao ' + key)
            factory = getattr(factories.items, tp)
            e = factory()(key, item_desc)
            if e is not None:
                parent = item_desc.get('parent', 'main')
                print('adding ' + key)
                r.add(e, parent)
    return r

