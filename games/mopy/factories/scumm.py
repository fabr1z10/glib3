from mopy.factories.basicroom import BasicRoom
from mopy.runners import Scheduler
from mopy.entity import Entity, Text, TextAlignment, Sprite, TextView
from mopy.camera import OrthoCamera
from mopy.components import HotSpot, HotSpotManager, Gfx, Cursor
from mopy.shapes import Rect
import mopy.monkey
import mopy.engine
from mopy.script import Script
import example
from mopy.actions import Walk
import mopy.scumm as scumm
from mopy.factories.interface import *
from mopy.factories.scumm_item import create_dynamic
import math




def toggle_cursor(x, y):

    gl = mopy.monkey.engine.data.globals
    gl.current_action += 1
    if gl.current_action >= len(gl.actions):
        gl.current_action = 0
    if gl.actions[gl.current_action] == -1:
        gl.current_action = 0
    example.get('cursor').setAnim(gl.actions[gl.current_action])


class ScummRoom(BasicRoom):
    def __init__(self, desc):
        super().__init__(desc)
        self.add_runner(Scheduler())
        self.add_runner({
            'type': 'runner.collisionengine',
            'size': [80, 80],
            'response': [
                {'tag1': 1, 'tag2': 2, 'on_enter': on_enter_collision_area, 'on_leave': on_leave_collision_area}]
        })

    def load_dynamic_items(self):
        print('loadin dynamic')
        for r in mopy.monkey.engine.data.r2i.get(self.id, []):
            print('okk')
            entity = create_dynamic(r)
            if entity:
                item = mopy.monkey.engine.data.items.get(r)
                self.add(entity, item.get('parent', self.default_item))


def map_room(desc: dict):
    room = ScummRoom(desc)
    room.add_runner(Scheduler())
    # read world size
    width = desc['width']
    height = desc['height']

    device_size = mopy.monkey.engine.device_size
    cam_width = device_size[0]
    cam_height = device_size[1]
    # # add the main node
    room.default_item = 'main'
    main = Entity(tag='main')
    main.camera = OrthoCamera(width, height, cam_width, cam_height, [0, 0, cam_width, cam_height], tag='maincam')
    main.add_component(HotSpotManager(lmbclick=walk_to))
    room.add(main)
    # add static items
    room.add_items(desc)
    # add dynamic items
    room.load_dynamic_items()
    return room


def dialogue_room(desc: dict):
    gl = mopy.monkey.engine.data.globals
    room = ScummRoom(desc)
    room.add_runner(Scheduler())
    room.init.append([refresh_inventory])
    # read world size
    width = desc['width']
    height = desc['height']

    device_size = mopy.monkey.engine.device_size
    cam_width = device_size[0]
    cam_height = device_size[1] - gl.ui_height

    # add the main node
    room.default_item = 'main'
    main = Entity(tag='main')
    main.camera = OrthoCamera(width, height, cam_width, cam_height, [0, gl.ui_height, cam_width, cam_height], tag='maincam')
    room.add(main)

    # add the ui node
    ui = Entity(tag='ui')
    ui.camera = OrthoCamera(cam_width, gl.ui_height, cam_width, gl.ui_height, [0, 0, cam_width, gl.ui_height], tag='uicam')
    room.add(ui)

    # dialogue node
    dialogue_node = TextView(factory=make_dialogue_button, pos=(0, 0), size=(320, 56),
        font_size=8, lines=7, delta_x=26, tag='dialogue')
    dialogue_node.add_component(HotSpotManager())
    room.add(dialogue_node)

    inventory_node = Entity(tag='inventory')
    ui.add(inventory_node)

    # add static items
    room.add_items(desc)
    room.load_dynamic_items()
    return room



def sierra_room(desc: dict):
    gl = mopy.monkey.engine.data.globals
    room = ScummRoom(desc)




    # read world size
    width = desc['width']
    height = desc['height']

    device_size = mopy.monkey.engine.device_size
    cam_width = device_size[0]
    cam_height = device_size[1]

    # add the main node
    room.default_item = 'main'
    main = Entity(tag='main')
    main.camera = OrthoCamera(width, height, gl.sci_viewport[2], gl.sci_viewport[3], gl.sci_viewport, tag='maincam')
    print('fottimi ' + str(width) +'  ' + str(height) )
    print('fottimi ' + str(cam_width) +'  ' + str(cam_height) )

    main.add_component(HotSpotManager(lmbclick=sierra_walk_to, rmbclick=toggle_cursor))
    room.add(main)

    a = Sprite(model='01.cursor', tag='cursor')
    a.add_component(Cursor())
    a.pos = (0, 0, 5)
    main.add(a)
    # add static items
    room.add_items(desc)
    # add dynamic items
    room.load_dynamic_items()
    return room


def map_room(desc: dict):
    gl = mopy.monkey.engine.data.globals
    room = ScummRoom(desc)
    room.add_runner(Scheduler())
    width = desc['width']
    height = desc['height']
    device_size = mopy.monkey.engine.device_size
    cam_width = device_size[0]
    cam_height = device_size[1]
    # add the main node
    room.default_item = 'main'
    main = Entity(tag='main')
    main.camera = OrthoCamera(width, height, cam_width, cam_height, [0, 0, cam_width, cam_height], tag='maincam')
    main.add_component(HotSpotManager(lmbclick=walk_to))
    room.add(main)
    cursor = Text(font=gl.default_font, size=8, text='#', color=(255, 255, 255, 255), tag='_cursor')
    cursor.add_component(Cursor())
    main.add(cursor)
    # add static items
    room.add_items(desc)
    # add dynamic items
    room.load_dynamic_items()
    return room


def default_room(desc: dict):
    gl = mopy.monkey.engine.data.globals
    room = ScummRoom(desc)
    room.add_runner(Scheduler())
    room.init.append([refresh_inventory])
    # read world size
    width = desc['width']
    height = desc['height']

    device_size = mopy.monkey.engine.device_size
    cam_width = device_size[0]
    cam_height = device_size[1] - gl.ui_height

    # add the main node
    room.default_item = 'main'
    main = Entity(tag='main')
    main.camera = OrthoCamera(width, height, cam_width, cam_height, [0, gl.ui_height, cam_width, cam_height], tag='maincam')
    main.add_component(HotSpotManager(lmbclick=walk_to))
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
    ui.add(Text(font='fonts.ui', size=gl.font_size, text=mopy.monkey.engine.read(dv['text']), color=gl.Colors.current_action,
        align=TextAlignment.bottom, tag='current_verb', pos=(cam_width / 2, 48, 0)))
    ui.add_component(HotSpotManager())
    cy = gl.ui_height - 2 * gl.font_size
    count = 0
    shift = 0
    shift_applied = 46
    for i in vset['verbs']:
        cx = (count // 4) * shift_applied
        cy = gl.ui_height - (2 + count % 4) * gl.font_size
        e = make_verb_button(i, (cx, cy, 0))
        shift = max(shift, 1 + len(mopy.monkey.engine.read(gl.verbs[i]['text'])))
        ui.add(e)
        count += 1
    room.add(ui)
    # inventory node
    inventory_node = TextView(factory=make_inventory_button, pos=(160, 0), size=(160, 48),
        font_size=8, lines=6, delta_x=26, tag='inventory')
    inventory_node.add_component(HotSpotManager())
    ui.add(inventory_node)

    # dialogue node
    dialogue_node = TextView(factory=make_dialogue_button, pos=(0, 0), size=(320, 56),
        font_size=8, lines=7, delta_x=26, tag='dialogue')
    dialogue_node.add_component(HotSpotManager())
    room.add(dialogue_node)

    # add static items
    room.add_items(desc)
    # add dynamic items
    room.load_dynamic_items()
    # print (' ### looking up for dynamic items in room ' + desc['id'])
    # for r in mopy.monkey.engine.data.r2i.get(desc['id'], []):
    #     print('QUI')
    #     entity = create_dynamic(r)
    #     item = mopy.monkey.engine.data.items.get(r)
    #     print(item.get('parent', room.default_item) +' facomi')
    #     room.add(entity, item.get('parent', room.default_item))
    return room

def walkarea(data):
    e = Entity()
    e.tag = 'walkarea_' + str(data.get('id', 0))
    walkarea = {
        'type': 'components.walkarea',
        'depth': data.get('depth', None),
        'scale': data.get('scale', None),
        'walls': data.get('walls', None)
    }

    if 'poly' in data:
        walkarea['shape'] = {
            'type': 'shape.polygon',
            'outline': data['poly'],
            'holes': data.get('holes')
        }
    else:
        walkarea['shape'] = {
            'type': 'shape.polyline',
            'nodes': data['nodes'],
            'edges': data['edges']
        }
    e.add_component(walkarea)
    return e

def bg(data):
    e = Entity()
    if 'image' in data:
        e.model = {
            'type': 'model.rect',
            'tex': data['image'],
            'scale': data.get('scale', (1, 1)),
            'repeat': data.get('repeat', (1, 1)),
        }
    else:
        e.model = data['model']
    e.layer = data.get('layer', 0)
    return e



def bg_ps3D(data):
    e = bg(data)
    # check if epos is set
    # if 'epos' in data:
    #     ep = data['epos']
    #     e.pos = [ep[0], 0, -math.sqrt(2.0) * ep[1]]
    # else:
    #     e.pos = data['pos']
    #
    #     e.pos[1] += e.pos[2] / math.sqrt(2)
    sq = math.sqrt(2) * 0.5
    if 'parallax' in data:
        p0 = data['parallax']['initial_position']
        #p0[1] += sq * e.pos[2]
        device = mopy.monkey.engine.device_size
        e.add_component({
            'type': 'components.parallax',
            'cam': 'maincam',
            'factor': data['parallax']['factor'],
            'cam0': [device[0] * 0.5, device[1] * 0.5],
            'pos0': p0
        })
    return e



    # auto size = t.get<glm::vec2>("size");
    # auto offset = t.get<glm::vec2>("offset", glm::vec2(0.0f));
    # float width = size[0];
    # float height = size[1];
    # auto tex = t.get<std::string>("tex", "");
    # auto render = t.get<std::string>("render", "fill");
    # auto color = t.get<glm::vec4> ("color", glm::vec4(1.0f));
    # auto rtype = (render == "fill" ? RenderType::FILL : RenderType::WIREFRAME);
    # auto repeat = t.get<glm::vec2>("repeat", glm::vec2(1.0f, 1.0f));
    # return rect(width, height, offset, rtype, color, tex, repeat);
    # e.add_component(Gfx(image=data['image']))
    return e



