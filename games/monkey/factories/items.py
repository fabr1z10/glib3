import mopy.entity as entity
import mopy.monkey as monkey
import data
import data.vars as vars
import mopy.components as compo
import example
import func
import mopy.scumm as scumm
import mopy.shapes as shapes
import scripts



def bg(**kwargs):
    def f(*args):
        e = entity.Entity(pos=(args[0], args[1], args[2]))
        e.add_component(compo.Gfx(image = kwargs['image']))
        return e
    return f




def walkarea(**kwargs):
    def f(*args):
        e = entity.Entity(pos=(args[0], args[1], args[2]))
        e.tag = kwargs.get('id')
        shape = None
        if 'outline' in kwargs:
            # shape is a polygon
            shape = shapes.Poly(kwargs.get('outline'))
            if 'holes' in kwargs:
                for hole in kwargs['holes']:
                    shape.holes.append(hole)
        else:
            # shape is a polyline
            shape = shapes.PolyLine(kwargs.get('nodes'), kwargs.get('edges'))
        walkarea = scumm.components.Walkarea(shape=shape)
        walkarea.depth = kwargs.get('depth', None)
        walkarea.scale = kwargs.get('scale', None)
        walls = kwargs.get('walls', None)
        if walls:
            for w in walls:
                active = monkey.engine.read(w[4] if w[4:] else True)
                print ('fottimi ' + str(active))
                walkarea.add_wall([w[0], w[1]], [w[2], w[3]], active)
        e.add_component(walkarea)
        return e
    return f


def character(**kwargs):
    def f(*args):
        key = args[0]
        is_player = key == data.current_player
        desc = args[1]
        model = desc.get('model', None)
        text_color = monkey.engine.read(desc.get('text_color', [255, 255, 255, 255]))
        #text_color =
        text_offset = desc.get('text_offset', [0, 60])
        pos = monkey.engine.read(desc.get('pos'))
        tag = desc.get('tag', key)
        speed = desc.get('speed', 100)
        print (tag + " pos is " + str(pos))
        s = None
        dir = desc.get('dir', 's')
        if model:
            s = entity.Sprite(model=model, pos=pos, tag='player' if is_player else tag)
            s.add_component(compo.Collider(debug=True, flag=data.Collision.Flags.player, mask=data.Collision.Flags.other,
                                       tag=data.Collision.Tags.player, shape=shapes.Rect(width=8, height=2, offset=[-4, 0])))
            if is_player:
                s.add_component(compo.Follow())
        else:
            s = entity.Entity(pos=pos, tag='player' if is_player else tag)
        s.add_component(scumm.components.CharacterController(dir=dir, speed=speed, text_color=text_color, text_offset=text_offset))
        # if a size is provided, add a hotspot
        size = desc.get('size', None)
        if size:
            print('size is ' + str(size))
            s.add_component(compo.HotSpot(shape=shapes.Rect(width=size[0], height=size[1], offset=[-0.5*size[0], 0]),
                                          onenter=func.hover_on(key),
                                          onleave=func.hover_off(key),
                                          onclick=func.prova()))
        return s
    return f

def item2(**kwargs):
    def f(*args):
        desc = args[1]
        pos = desc.get('pos')
        size = desc.get('size')
        s = entity.Entity(pos=pos)
        s.add_component(compo.Collider(flag=vars.Collision.Flags.other, mask=vars.Collision.Flags.player,
                                       tag=vars.Collision.Tags.trap, shape=shapes.Rect(width=size[0],height=size[1]),debug=True))
        s.add_component(compo.Info(func=desc.get('func')))
        return s
    return f

def item3(**kwargs):
    def f(*args):
        desc = args[1]
        pos = desc.get('pos')
        size = desc.get('size')
        s = entity.Entity(pos=pos)
        fu = getattr(scripts.actions, desc.get('func'))
        s.add_component(compo.HotSpot(shape=shapes.Rect(width=size[0], height=size[1]), onclick=fu))
        return s
    return f

def map_hot_spot(**kwargs):
    def f(*args):
        key = args[0]
        desc = args[1]
        pos = desc.get('pos')
        size = desc.get('size')
        text = monkey.engine.read(desc.get('text'))
        s = entity.Entity(pos=pos)
        s.add_component(compo.HotSpot(shape=shapes.Rect(width=size[0], height=size[1], offset=(-size[0]*0.5, -size[1]*0.5)),
                                      onenter=func.hover_on_map_hotspot(text),
                                      onleave=func.hover_off_map_hotspot(),
                                      onclick=func.click_on_map_hotspot(key)))
        return s
    return f

def item1(**kwargs):
    def f(*args):
        key = args[0]
        desc = args[1]
        cio = desc.get('create_if_owned', False)
        if (not cio) and key in vars.inventory:
            # item is in inventory. don't create it
            return None
        pos = desc.get('pos')
        model = desc.get('model', None)
        #text = monkey.engine.read(desc.get('text'))
        s = None
        if model:
            anim = monkey.engine.read(desc.get('anim', None))
            s = entity.Sprite(model=model, pos=pos, anim= anim)
        else:
            s = entity.Entity(pos = pos)
        #s.tag = desc.get('tag', None)
        s.tag= key
        # if a size is provided, add a hotspot
        size = desc.get('size', None)
        if size:
            print('size is ' + str(size))
            s.add_component(compo.HotSpot(shape=shapes.Rect(width=size[0], height=size[1]),
                                          onenter=func.hover_on(key),
                                          onleave=func.hover_off(key),
                                          onclick=func.prova()))
        return s
    return f







def make_verb_button(verb_id: str, pos):
    verb = data.verbs[verb_id]
    e = entity.Text(font='ui', size=8, text=monkey.engine.read(verb['text']), color=data.Colors.verb_unselected, align=entity.TextAlignment.bottom_left, pos=pos)
    e.add_component(compo.HotSpot(shape=None, onenter=func.change_color(data.Colors.verb_selected), onleave=func.change_color(data.Colors.verb_unselected),
                                  onclick=func.on_verb_click(verb_id)))
    return e


class InventoryButton(entity.Text):
    def __init__(self, font: str, item_id: str, qty: int, color_inactive, color_active,
                 align: entity.TextAlignment = entity.TextAlignment.bottom_left,
                 script: callable = None, tag=None, pos=[0, 0, 0]):
        if item_id not in data.items:
            raise BaseException('Hey! unknown item: ' + item_id)
        item = data.items[item_id]
        text = ''
        if qty == 1:
            text = monkey.engine.read(item['text'])
        else:
            text = str(qty) + ' ' + monkey.engine.read(item['plural'])
        print ('init with ' + text)
        print (color_inactive)
        super().__init__(font, 8, text, color_inactive, align, tag, pos)
        self.add_component(compo.HotSpot(
            shape=None,
            onenter=func.hover_on_inventory_button(item_id),# change_color(colorActive),
            onleave=func.hover_off_inventory_button(item_id),
            onclick=func.prova()))


class DialogueButton(entity.Text):
    def __init__(self, font: str, text: str, color_inactive, color_active,
                 align: entity.TextAlignment = entity.TextAlignment.bottom_left, script: callable = None,
                 tag=None, pos=[0, 0, 0]):
        super().__init__(font,8, text, color_inactive, align, tag, pos)
        self.add_component(compo.HotSpot(
            shape=None,
            onenter=func.change_color(color_active),
            onleave=func.change_color(color_inactive),
            onclick=script))

def make_inventory_button(item):
    return InventoryButton(
        font='ui',
        item_id=item[0],
        qty=item[1],
        color_inactive=data.Colors.inv_unselected,
        color_active=data.Colors.inv_selected)

def make_dialogue_button(dialogueline):
    return DialogueButton(
        font='ui',
        text=dialogueline.get_text(),
        script=func.execute_dialogue_script(dialogueline),
        color_inactive=data.Colors.verb_unselected,
        color_active=data.Colors.verb_selected)
# def makeDialogueButton(dialogueline):
#     return se.DialogueButton(
#         font = 'ui',
#         text = dialogueline.text,
#         script = runDialogueScript(dialogueline),
#         colorInactive = scumm.Config.Colors.verb_unselected,
#         colorActive = scumm.Config.Colors.verb_selected)
# class VerbButton(entity.Text):
#     def __init__(self, font: str, verbId: str, colorInactive, colorActive, align: entity.TextAlignment = entity.TextAlignment.topleft, tag=None, pos=[0,0,0]):
#         verb = s.Config.getVerb(verbId)
#         super().__init__(font, verb.text, colorInactive, align, tag, pos)
#         self.addComponent(compo.HotSpot(
#             shape = None,
#             onenter = change_color(colorActive),
#             onleave = change_color(colorInactive),
#             onclick = verb.callback ))