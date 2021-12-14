from mopy.factories.basicroom import BasicRoom
import mopy.runners as runners
import data.globals as gl
import mopy.monkey as monkey
from mopy.entity import Entity, Text, TextAlignment
from mopy.camera import OrthoCamera
from mopy.components import HotSpotManager
import data.scripts.ui as uis

def default_room(desc: dict):
    room = BasicRoom.make(desc)
    room.add_runner(runners.Scheduler())
    # read world sizse
    width = desc['width']
    height = desc['height']
    #print(gl.ui_height)
    device_size = monkey.engine.device_size
    cam_width = device_size[0]
    cam_height = device_size[1] - gl.ui_height
    #print ('device size is ' + str(monkey.engine.device_size))
    # add the main node
    main = Entity(tag='main')
    main.camera = OrthoCamera(width, height, cam_width, cam_height, [0, gl.ui_height, cam_width, cam_height], tag='maincam')
    main.add_component(HotSpotManager(lmbclick=uis.walkto))
    room.add(main)
    # get the verb set from the description. If not specified, verb set 0 will be used
    verb_set = desc.get('verb_set', 0)
    vset = gl.verb_sets[verb_set]
    dv = gl.verbs[vset['default_verb']]
    gl.current_verb = vset['default_verb']
    gl.current_item_1 = ''
    gl.current_item_2 = ''

    # add the ui node
    ui = Entity(tag='ui')
    ui.camera = OrthoCamera(cam_width, gl.ui_height, cam_width, gl.ui_height, [0, 0, cam_width, gl.ui_height], tag='uicam')
    ui.add(Text(font='ui', size=gl.font_size, text='mierda', color=gl.Colors.current_action,
        align=TextAlignment.bottom, tag='current_verb', pos=(cam_width / 2, 48, 0)))
    ui.add_component(HotSpotManager())
    room.add(ui)
    return room
#     id = desc['id']
#     width = desc['width']
#     height = desc['height']
#     r = room.Room(id)#, width, height)
#     r.add_runner(runners.Scheduler())
#
#     if 'on_start' in desc:
#         r.on_start = getattr(scripts, desc['on_start'])
#
#     # setup collision engine
#     ce = runners.CollisionEngine(80, 80)
#     ce.add_response(data.Collision.Tags.player, data.Collision.Tags.trap, runners.CollisionResponse(on_enter=func.on_enter_trap))
#     r.add_runner(ce)
#     print('uisize is ' + str(data.ui_height))
#     device_size = monkey.engine.device_size
#     cam_width = device_size[0]
#     cam_height = device_size[1] - data.ui_height
#     print ('device size is ' + str(monkey.engine.device_size))
#     # # add the main node
#     main = entity.Entity(tag='main')
#     main.camera = cam.OrthoCamera(width, height, cam_width, cam_height, [0, data.ui_height, cam_width, cam_height], tag='maincam')
#     main.add_component(compo.HotSpotManager(lmbclick=func.walkto))
#     r.add(main)
#     # # main.add (e.Text(font='ui', text='ciao', color = [255, 255, 255, 255], align = e.TextAlignment.bottom, pos = [camWidth/2, 16, 0]))
#     verb_set = desc.get('verb_set', 0)
#     # get current verb set
#     vset = data.verb_sets[verb_set]
#     dv = data.verbs[vset['default_verb']]
#     data.current_verb = vset['default_verb']
#     data.current_item_1 = ''
#     data.current_item_2 = ''
#
#     ui = entity.Entity(tag='ui')
#     ui.camera = cam.OrthoCamera(cam_width, data.ui_height, cam_width, data.ui_height, [0, 0, cam_width, data.ui_height], tag='uicam')
#     #monkey.engine.read(dv['text']
#     ui.add(entity.Text(font='ui', size=8, text='mierda', color=data.Colors.current_action,
#       align=entity.TextAlignment.bottom, tag='current_verb', pos=(cam_width / 2, 48, 0)))
#     ui.add_component(compo.HotSpotManager())
#     r.init.append(func.refresh_inventory)
#     on_load = desc.get('on_load', None)
#     if on_load:
#         r.init.append(getattr(scripts, on_load))
#
#     r.add(ui)
#     cy = data.ui_height - 2 * data.font_size
#     count = 0
#     shift = 0
#     shift_applied = 46
#     for i in vset['verbs']:
#         cx = (count // 4) * shift_applied
#         cy = data.ui_height - (2 + count % 4) * data.font_size
#         e = factories.items.make_verb_button(i, (cx, cy, 0))
#         shift = max(shift, 1 + len(monkey.engine.read(data.verbs[i]['text'])))
#         ui.add(e)
#         count += 1
#     # inventory node
#     inventory_node = entity.TextView(factory=factories.items.make_inventory_button, pos=(160, 0), size=(160, 48),
#                                      font_size=8, lines=6, delta_x=26, tag='inventory')
#     inventory_node.add_component(compo.HotSpotManager())
#     ui.add(inventory_node)
#
#     # dialogue node
#     dialogue_node = entity.TextView(factory=factories.items.make_dialogue_button, pos=(0, 0), size=(320, 56),
#                                     font_size=8, lines=7, delta_x=26, tag='dialogue')
#     dialogue_node.add_component(compo.HotSpotManager())
#     r.add(dialogue_node)
#
#
# #     inventory_node.addComponent(compo.HotSpotManager())
#
#
#     # now add all items
#     if 'items' in desc:
#         for item in desc['items']:
#             factory_id = item['factory']
#             factory = monkey.engine.get_item_factory(factory_id[0])
#             if factory is None:
#                 print('Unable to find factory for item: ' + factory_id[0])
#                 exit(1)
#             else:
#                 props = {} if len(factory_id) == 1 else factory_id[1]
#                 f = factory(**props)
#                 parent = item.get('parent', 'main')
#                 for a in item['d']:
#                     e = f(*a)
#                     r.add(e, parent)
#
#     # add dynamic items
#     if id in data.items_in_room:
#         for key in data.items_in_room[id]:
#             item_desc = data.items[key]
#             tp = item_desc.get('type', None)
#             if tp is None:
#                 print ('item ' + key + ' does not have type!')
#                 exit(1)
#             print ('ciao ' + key)
#             factory = getattr(factories.items, tp)
#             e = factory()(key, item_desc)
#             if e is not None:
#                 parent = item_desc.get('parent', 'main')
#                 print('adding ' + key)
#                 r.add(e, parent)
#     return r