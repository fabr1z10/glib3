from mopy.factories.basicroom import BasicRoom
from mopy.runners import Scheduler
from mopy.entity import Entity, Text, TextAlignment, Sprite, TextView
from mopy.camera import OrthoCamera
from mopy.components import HotSpot, HotSpotManager, Gfx
from mopy.shapes import Rect
import mopy.monkey
import mopy.engine
from mopy.script import Script
import example
from mopy.actions import Walk

from mopy.factories.interface import update_current_action, make_inventory_button,  make_dialogue_button, make_verb_button
from mopy.factories.scumm_item import create_dynamic


def walk_to(x, y):
    s = Script(uid='_main')
    s.add_action(Walk((x, y), 'player'))
    example.play(s)











def default_room(desc: dict):
    gl = mopy.monkey.engine.data.globals
    room = BasicRoom(desc)
    room.add_runner(Scheduler())

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
    print (' ### looking up for dynamic items in room ' + desc['id'])
    for r in mopy.monkey.engine.data.r2i.get(desc['id'], []):
        print('QUI')
        entity = create_dynamic(r)
        item = mopy.monkey.engine.data.items.get(r)
        print(item.get('parent', room.default_item) +' facomi')
        room.add(entity, item.get('parent', room.default_item))
    return room

def walkarea(data):
    e = Entity()
    e.tag = 'walkarea_' + str(data.get('id', 0))
    e.add_component({
        'type': 'components.walkarea',
        'shape': {
            'type': 'shape.polygon',
            'outline': data['poly']
        }
    })
    return e

def bg(data):
    e = Entity()
    e.model = {
        'type': 'model.rect',
        'tex': data['image']

    }
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



