import mopy.monkey
import mopy.engine
from mopy.entity import Entity, Sprite
from mopy.components import HotSpot, Collider, Follow
from mopy.shapes import Rect
from mopy.factories.interface import hover_on, hover_off, run_action, run_action_sci
from mopy.scumm import get_item
import example


def add_collision_box(entity, desc):
    size = desc.get('size')
    entity.add_component(Collider(shape=Rect(size[0], size[1], offset=desc.get('offset', (0, 0))), flag=desc.get('flag'), mask=desc.get('mask'), tag=desc.get('tag'), debug=True))




def character(key, desc):
    gl = mopy.monkey.engine.data.globals
    is_player = key == gl.current_player
    model = desc.get('model', None)
    text_color = desc.get('text_color', [255, 255, 255, 255])
    text_offset = desc.get('text_offset', gl.default_text_offset)
    pos = desc.get('pos')
    tag = desc.get('tag', key)
    speed = desc.get('speed', gl.default_speed)
    s = None
    dir = desc.get('dir', 's')

    if model:
        s = Sprite(model=model, pos=pos, tag='player' if is_player else tag)
        # s.add_component(Collider(debug=True, flag=data.Collision.Flags.player, mask=data.Collision.Flags.other,
        #                                tag=data.Collision.Tags.player,
        #                                shape=shapes.Rect(width=8, height=2, offset=[-4, 0])))
        if is_player:
            s.add_component(Follow())
    else:
        s = Entity(pos=pos, tag='player' if is_player else tag)
    s.add_component({
        'type': 'components.character_controller',
        'dir': dir,
        'speed': speed,
        'text_offset': text_offset,
        'text_color': text_color,
        'use_keyboard': gl.use_keyboard if is_player else False
    })
    if is_player and gl.use_keyboard:
        s.add_component({ 'type': 'components.keyinput'})

      #cumm.components.CharacterController(dir=dir, speed=speed, text_color=text_color, text_offset=text_offset))
    # if a size is provided, add a hotspot
    size = desc.get('size', None)
    if size:
        s.add_component(HotSpot(shape=Rect(width=size[0], height=size[1], offset=[-0.5 * size[0], 0]),
                                      onenter=hover_on(key),
                                      onleave=hover_off(key),
                                      onclick=run_action()))
    cbox = desc.get('collision', None)
    if cbox:
        add_collision_box(s, cbox)
    return s

def item(key, desc):
    eng = mopy.monkey.engine
    data = eng.data
    cio = desc.get('create_if_owned', False)
    if (not cio) and key in data.globals.inventory:
        # item is in inventory. don't create it
        return None
    pos = desc.get('pos')
    model = desc.get('model', None)
    #text = monkey.engine.read(desc.get('text'))
    s = None
    if model:
        anim = desc.get('anim', None)
        print('the animation is ' + str(anim))
        s = Sprite(model=model, pos=pos, anim=anim)
    else:
        s = Entity(pos=pos)
    s.tag = key
    # if a size is provided, add a hotspot
    size = desc.get('size', None)
    if size:
        print('size is ' + str(size))
        s.add_component(HotSpot(shape=Rect(width=size[0], height=size[1]),
            onenter=hover_on(key),
            onleave=hover_off(key),
            onclick=run_action()))
    cbox = desc.get('collision', None)
    if cbox:
        add_collision_box(s, cbox)

    return s

# item for sierra game. Nothing happens when hovering
def sitem(key, desc):
    eng = mopy.monkey.engine
    data = eng.data
    cio = desc.get('create_if_owned', False)
    if (not cio) and key in data.globals.inventory:
        # item is in inventory. don't create it
        return None
    pos = desc.get('pos')
    model = desc.get('model', None)
    s = None
    if model:
        anim = desc.get('anim', None)
        s = Sprite(model=model, pos=pos, anim=anim)
    else:
        s = Entity(pos=pos)
    s.tag = key
    # if a size is provided, add a hotspot
    size = desc.get('size', None)
    if size:
        print('size is ' + str(size))
        s.add_component(HotSpot(shape=Rect(width=size[0], height=size[1]), onclick=run_action_sci()))
    cbox = desc.get('collision', None)
    if cbox:
        add_collision_box(s, cbox)

    return s

item_maps = {
    'scumm.item': item,
    'sierra.item': sitem,
    'scumm.character': character
}

def create_dynamic(key):
    data = mopy.monkey.engine.data
    print (' ### creating dynamic item: ' + key)
    item =  get_item(key)
    print ('HERE IS THETHING: ' + str(item))
    if item:
        type = item['type']
        print(' ### item type: ' + type)
        return item_maps[type](key, item)
