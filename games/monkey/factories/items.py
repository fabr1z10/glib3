import vars
import entity
import monkey
import components as compo
import example
import func
import entity
import scumm.components
import shapes

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
        shape = shapes.Poly(kwargs.get('outline'))
        if 'holes' in kwargs:
            for hole in kwargs['holes']:
                shape.holes.append(hole)
        walkarea = scumm.components.Walkarea(shape=shape)
        walls = kwargs.get('walls', None)
        if walls:
            for w in walls:
                walkarea.add_wall([w[0], w[1]], [w[2], w[3]], True)
        e.add_component(walkarea)
        return e
    return f


def player(**kwargs):
    def f(*args):
        key = args[0]
        desc = args[1]
        model = desc['model']
        text_color = desc.get('text_color', [255, 255, 255, 255])
        text_offset = desc.get('text_offset', [0, 60])
        pos = desc.get('pos')
        s = entity.Sprite(model=model, pos=pos, tag='player')
        dir = desc.get('dir', 's')
        print ('direction is ' + str(dir))
        s.add_component(scumm.components.CharacterController(dir=dir, speed=20, text_color=text_color, text_offset=text_offset))
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
            s = entity.Sprite(model=model, pos=pos)
        else:
            s = entity.Entity(pos = pos)
        # if a size is provided, add a hotspot
        size = desc.get('size', None)
        if size:
            s.add_component(compo.HotSpot(shape=shapes.Rect(width=size[0], height=size[1]),
                                          onenter=func.hover_on(key),
                                          onleave=func.hover_off(key),
                                          onclick=func.prova()))
        return s
    return f







def make_verb_button(verb_id: str, pos):
    verb = vars.verbs[verb_id]
    e = entity.Text(font='ui', size=8, text=monkey.engine.read(verb['text']), color=vars.Colors.verb_unselected, align=entity.TextAlignment.bottom_left, pos=pos)
    e.add_component(compo.HotSpot(shape=None, onenter=func.change_color(vars.Colors.verb_selected), onleave=func.change_color(vars.Colors.verb_unselected),
                                  onclick=func.on_verb_click(verb_id)))
    return e


class InventoryButton(entity.Text):
    def __init__(self, font: str, item_id: str, qty: int, color_inactive, color_active,
                 align: entity.TextAlignment = entity.TextAlignment.bottom_left,
                 script: callable = None, tag=None, pos=[0, 0, 0]):
        if item_id not in vars.items:
            raise BaseException('Hey! unknown item: ' + item_id)
        item = vars.items[item_id]
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

def make_inventory_button(item):
    return InventoryButton(
        font='ui',
        item_id=item[0],
        qty=item[1],
        color_inactive=vars.Colors.inv_unselected,
        color_active=vars.Colors.inv_selected)

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