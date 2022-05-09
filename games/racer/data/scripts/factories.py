



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