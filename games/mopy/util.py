import glm
import mopy.monkey as monkey
import mopy.engine
import example
import operator



def tiles_to_world(tile_pos, tile_size):
    if len(tile_pos) == 2:
        return tile_pos[0] * tile_size[0], tile_pos[1] * tile_size[1]
    else:
        return tile_pos[0] * tile_size[0], tile_pos[1] * tile_size[1], tile_pos[2]


def mat_to_list(m):
    return [ m[0][0], m[0][1], m[0][2], m[0][3],
             m[1][0], m[1][1], m[1][2], m[1][3],
             m[2][0], m[2][1], m[2][2], m[2][3],
             m[3][0], m[3][1], m[3][2], m[3][3]]


# compute gravity and initial jump vel from jump height
# and time to jump apex
def compute_gravity(jump_height, time_to_jump_apex):
    gravity = (2.0 * jump_height) / (time_to_jump_apex * time_to_jump_apex)
    jump_speed = abs(gravity) * time_to_jump_apex
    return gravity, jump_speed


# id = string which is the name of the factory
def create_entity(id, pos, args=None, parent='main', use_tile=True):
    factory_func = operator.attrgetter(id)(monkey.engine.data)
    entity = factory_func(args)
    if use_tile:
        tile_size = getattr(monkey.engine.data.globals, 'tile_size', [1, 1])
        entity.pos = tiles_to_world(pos, tile_size)
    else:
        entity.pos = pos
    parent_node = example.get(parent)
    new_id = parent_node.add(entity)

    #
    #
    # entity_desc = monkey.engine.get_asset(id, args)
    # factory = monkey.engine.get_item_factory(entity_desc['type'])
    # if not factory:
    #     print('Don''t have factory for item: ' + entity_desc['type'])
    #     exit(1)
    # tile_size = getattr(monkey.engine.data.globals, 'tile_size', [1, 1])# monkey.engine.room_vars.get('tile_size', [1, 1])
    # parent_node = example.get(parent)
    # on_create = entity_desc.get('on_create', None)
    # for p in pos:
    #     print(entity_desc)
    #     e = factory(entity_desc)
    #     if use_tile:
    #         e.pos = tiles_to_world(p, tile_size)
    #     else:
    #         e.pos = p
    #     eid = parent_node.add(e)
    #     if on_create:
    #         f = operator.attrgetter(on_create)(monkey.engine.data)
    #         f(eid, p)

def rgb(r, g, b):
    return (r/255.0, g/255.0, b/255.0, 1.0)


def hex_to_rgb(value):
    value = value.lstrip('#')
    lv = len(value)
    return tuple(int(value[i:i + lv // 3], 16)/255.0 for i in range(0, lv, lv // 3))