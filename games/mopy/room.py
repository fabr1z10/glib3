import mopy.engine as engine
import mopy.entity as entity
import mopy
import math
import example


def add_entity(itemid, pos, parent):
    item = mopy.monkey.engine.get_asset(itemid)
    a = build_entity(item, pos)
    id = example.get(parent).add(a)
    if 'on_create' in item:
        f = getattr(mopy.monkey.engine.data.scripts, item['on_create'])
        f(id, pos[0], pos[1])
    return id


#########################
# creates one or more entities and add them to given parent
# pos_type:
# 0 --- unchanged
# 1 --- pseudo 3d
# 2 --- pseudo 3d alwyas in bg
#########################
def build_entity(item, pos):
    item_type = item.get('type')
    if not item_type:
        print('Error! Missing <type> field in item descriptor.')
        exit(1)
    factory = mopy.monkey.engine.get_item_factory(item_type)
    if not factory:
        print('Don''t have factory for item: ' + item_type)
        exit(1)
    e = factory(item)
    if not e.auto_pos:
        pos_type = item.get('pos_type', 0)
        real_pos = pos
        if pos_type == 1:
            # this is pseudo 3d coords, pos[2] is the elevation
            real_pos = [pos[0], pos[2], -math.sqrt(2.0) * pos[1]]
            print('real pos = ' +str(real_pos))
        elif pos_type == 2:
            real_pos[2] = pos[2]
            real_pos[1] += real_pos[2] / math.sqrt(2)
        if mopy.monkey.engine.data.globals.tiled_pos:
            tile_size = mopy.monkey.engine.data.globals.tile_size
            real_pos[0] = real_pos[0] *tile_size[0]
            real_pos[1] = real_pos[1] * tile_size[1]
        e.pos = real_pos
    return e


class Room:
    def __init__(self, uid: str):
        self.id = uid
        #self.width = width
        #self.height = height
        self.ref = {}
        self.engines = []
        self.init = []
        self.dims = 2
        # collection of entities
        self.scene = []
        # method to call before room is created
        self.on_start = None

    # add an entity. If you provide a parent, the entity will be added to the parent,
    # otherwise it will be added to the scene
    def add(self, e: entity.Entity, parent: str = None):
        if parent and parent in self.ref:
            self.ref[parent].add(e)
        else:
            if parent:
                print ('WARNING! ' + parent +' + not found!')
            self.scene.append(e)
        if e.tag:
            self.ref[e.tag] = e

    def add_runner(self, r):
        self.engines.append(r)


