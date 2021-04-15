import room
import vars
import entity
import camera as cam
import engine
import monkey
import factories.items
import components as compo
import func
import runners
import scripts.actions


def default_room(desc: dict):
    id = desc['id']
    width = desc['width']
    height = desc['height']
    r = room.Room(id, width, height)
    r.add_runner(runners.Scheduler())

    # setup collision engine
    ce = runners.CollisionEngine(80, 80)
    ce.add_response(vars.Collision.Tags.player, vars.Collision.Tags.trap, runners.CollisionResponse(on_enter=func.on_enter_trap))
    r.add_runner(ce)
    print('uisize is ' + str(vars.ui_height))
    device_size = monkey.engine.device_size
    cam_width = device_size[0]
    cam_height = device_size[1] - vars.ui_height
    print ('device size is ' + str(monkey.engine.device_size))
    # # add the main node
    main = entity.Entity(tag='main')
    main.camera = cam.OrthoCamera(width, height, cam_width, cam_height, [0, vars.ui_height, cam_width, cam_height], tag='maincam')
    main.add_component(compo.HotSpotManager(lmbclick=func.walkto))
    r.add(main)
    # # main.add (e.Text(font='ui', text='ciao', color = [255, 255, 255, 255], align = e.TextAlignment.bottom, pos = [camWidth/2, 16, 0]))
    verb_set = desc.get('verb_set', 0)
    # get current verb set
    vset = vars.verb_sets[verb_set]
    dv = vars.verbs[vset['default_verb']]
    vars.current_verb = vset['default_verb']
    vars.current_item_1 = ''
    vars.current_item_2 = ''

    ui = entity.Entity(tag='ui')
    ui.camera = cam.OrthoCamera(cam_width, vars.ui_height, cam_width, vars.ui_height, [0, 0, cam_width, vars.ui_height], tag='uicam')
    #monkey.engine.read(dv['text']
    ui.add(entity.Text(font='ui', size=8, text='mierda', color=vars.Colors.current_action,
      align=entity.TextAlignment.bottom, tag='current_verb', pos=(cam_width / 2, 48, 0)))
    ui.add_component(compo.HotSpotManager())
    r.init.append(func.refresh_inventory)
    on_load = desc.get('on_load', None)
    if on_load:
        r.init.append(getattr(scripts.actions, on_load))

    r.add(ui)
    cy = vars.ui_height - 2 * vars.font_size
    count = 0
    shift = 0
    shift_applied = 46
    for i in vset['verbs']:
        cx = (count // 4) * shift_applied
        cy = vars.ui_height - (2 + count % 4) * vars.font_size
        e = factories.items.make_verb_button(i, (cx, cy, 0))
        shift = max(shift, 1 + len(monkey.engine.read(vars.verbs[i]['text'])))
        ui.add(e)
        count += 1
    # inventory node
    inventory_node = entity.TextView(factory=factories.items.make_inventory_button, pos=(160, 0), size=(160, 48),
                                     font_size=8, lines=6, delta_x=26, tag='inventory')
    inventory_node.add_component(compo.HotSpotManager())
    r.add(inventory_node)

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

    # super().__init__(id, width, height)
    # self.collide = collide
    # scumm.State.collision_enabled = collide#
    # uisize = scumm.Config.ui_height
    # camWidth = engine.device_size[0]
    # camHeight = engine.device_size[1] - uisize
    #
    # # get the verbset used in this room
    # verbset: scumm.VerbSet = scumm.Config.verbSets[0]
    # defv: scumm.Verb = scumm.Config.getVerb(verbset.defaultVerb)
    # scumm.Config.verb = verbset.defaultVerb
    # # verbs = settings.monkey.config['verbs']
    # default_verb = scumm.Config.getVerb
    #
    # # add the ui node
    # if addui:
    #     main.addComponent(compo.HotSpotManager(lmbclick=func.walkto))
    #
    #     ui = entity.Entity(tag='ui')
    #     ui.camera = cam.OrthoCamera(camWidth, uisize, camWidth, uisize, [0, 0, camWidth, uisize], tag='uicam')
    #     ui.add(entity.Text(font='ui', text=defv.text, color=scumm.Config.Colors.current_action,
    #                        align=entity.TextAlignment.bottom, tag='current_verb', pos=[camWidth / 2, 48, 0]))
    #     ui.addComponent(compo.HotSpotManager())
    #     inventory_node = entity.TextView(factory=makeInventoryButton, pos=(160, 0), size=(140, 48), fontSize=8, lines=6,
    #                                      deltax=26, tag='inventory')
    #     inventory_node.addComponent(compo.HotSpotManager())
    #
    #     row = 2
    #     count = 0
    #     for a in verbset.verbs:
    #         col = 1 + count // 4
    #         x = 2 + (col - 1) * 46
    #         verb: scumm.Verb = scumm.Config.getVerb(a)
    #         print('here ' + a + ' ' + verb.text)
    #         ui.add(se.VerbButton(
    #             font='ui',
    #             verbId=a,
    #             colorInactive=scumm.Config.Colors.verb_unselected,
    #             colorActive=scumm.Config.Colors.verb_selected,
    #             align=entity.TextAlignment.bottomleft,
    #             pos=[x, uisize - row * 8, 0]
    #         ))
    #         count += 1
    #         row += 1
    #         if (row > 5):
    #             row = 2
    #     self.scene.append(ui)
    #     self.scene.append(inventory_node)
    #
    #     scumm.Config.resetVerb()
    #
    # # add the dialogue node
    # dialogue_node = entity.TextView(factory=makeDialogueButton, size=[320, 56], fontSize=8, lines=6, deltax=26,
    #                                 tag='dialogue')
    # dialogue_node.addComponent(compo.HotSpotManager())
    #
    # pass
