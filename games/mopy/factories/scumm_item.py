import mopy.monkey
import mopy.engine
from mopy.entity import Entity, Sprite
from mopy.components import HotSpot, Collider, Follow
from mopy.shapes import Rect
import example


def update_current_action():
    items = mopy.monkey.engine.data.items
    gl = mopy.monkey.engine.data.globals
    a = example.get('current_verb')
    verb = gl.verbs[gl.current_verb]
    text = mopy.monkey.engine.read(verb['text'])
    if gl.current_item_1:
        item = items[gl.current_item_1]
        text += ' ' + mopy.monkey.engine.read(item['text'])
    if verb['items'] == 2:
        if gl.wait_for_second_item:
            text += ' ' + mopy.monkey.engine.read(verb['prep'])
            if gl.current_item_2:
                item2 = items[gl.current_item_2]
                text += ' ' + mopy.monkey.engine.read(item2['text'])
    a.setText(text)


def set_verb_2(verb_id, item_id):
    gl = mopy.monkey.engine.data.globals
    gl.current_verb = verb_id
    gl.current_item_1 = item_id
    gl.current_item_2 = ''
    gl.wait_for_second_item = False
    update_current_action()


# called when hovering on an item
def hover_on(obj):
    def f(item):
        gl = mopy.monkey.engine.data.globals
        if not gl.current_item_1:
            gl.current_item_1 = obj
        else:
            # if this verb takes 2 objects...
            if gl.verbs[gl.current_verb]['items'] > 1 and gl.current_item_1 != obj:
                gl.current_item_2 = obj
        update_current_action()
    return f


def hover_off(obj):
    def f(item):
        gl = mopy.monkey.engine.data.globals
        if gl.current_item_2:
            gl.current_item_2 = ''
        else:
            # set obj1 to nil unless we are waiting for 2nd object
            if gl.verbs[gl.current_verb]['items'] == 1:
                gl.current_item_1 = ''
        update_current_action()
    return f


def run_action():
    def f(x, y, item):
        scripts = mopy.monkey.engine.data.scripts
        items = mopy.monkey.engine.data.items
        gl = mopy.monkey.engine.data.globals
        print('current verb: ' + str(gl.current_verb))
        print('object      : ' + gl.current_item_1)
        print('second obj  : ' + gl.current_item_2)
        script = None
        if gl.current_item_2 == '':
            # see if I have a callback of form <verb>_<object>
            f1 = gl.current_verb + '_' + gl.current_item_1
            fc = getattr(scripts, f1, None)
            if fc is None:
                print(f1 + ' not found')
                # if verb takes two objects, wait for 2nd object
                if gl.verbs[gl.current_verb]['items'] == 2:
                    gl.wait_for_second_item = True
                    update_current_action()
                else:
                    f2 = gl.current_verb + '_'
                    fc = getattr(scripts, f2, None)
                    if fc is None:
                        print ('not found: ' + f2)
            if fc:
                script = fc(gl.current_item_1, item)
            set_verb_2('walkto', gl.current_item_1)
        else:
            f1 = gl.current_verb + '_' + gl.current_item_1 + '_' + gl.current_item_2
            fc = getattr(scripts, f1, None)
            if fc is None:
                # try flipping the objects
                f1 = gl.current_verb + '_' + gl.current_item_2 + '_' + gl.current_item_1
                fc = getattr(scripts, f1, None)
                if fc:
                    script = fc(gl.current_item_2, gl.current_item_1)
                else:
                    f2 = gl.current_verb + '_'
                    fc = getattr(scripts, f2, None)
                    if fc:
                        script = fc(gl.current_item_2, item)
            else:
                script = fc(gl.current_item_1, gl.current_item_2)
        if script:
            example.play(script)
    return f


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
    })
      #cumm.components.CharacterController(dir=dir, speed=speed, text_color=text_color, text_offset=text_offset))
    # if a size is provided, add a hotspot
    size = desc.get('size', None)
    if size:
        s.add_component(HotSpot(shape=Rect(width=size[0], height=size[1], offset=[-0.5 * size[0], 0]),
                                      onenter=hover_on(key),
                                      onleave=hover_off(key),
                                      onclick=run_action()))
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
        anim = eng.read(desc.get('anim', None))
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
    return s



item_maps = {
    'scumm.item': item,
    'scumm.character': character
}

def create_dynamic(key):
    data = mopy.monkey.engine.data
    print (' ### creating dynamic item: ' + key)
    item = data.items.get(key)
    if item:
        type = item['type']
        print(' ### item type: ' + type)
        return item_maps[type](key, item)
