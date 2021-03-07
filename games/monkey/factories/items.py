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
        e.add_component(scumm.components.Walkarea(shape=shape))
        return e
    return f


def player(**kwargs):
    def f(*args):
        key = args[0]
        desc = args[1]
        model = desc['model']
        pos = desc.get('pos')
        s = entity.Sprite(model=model, pos=pos, tag='player')
        dir = desc.get('dir', 's')
        print ('direction is ' + str(dir))
        s.add_component(scumm.components.CharacterController(dir = dir))
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
        text = monkey.engine.read(desc.get('text'))
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
                                          onclick=func.prova))
        return s
    return f







def make_verb_button(verb_id: str, pos):
    verb = vars.verbs[verb_id]
    e = entity.Text(font='ui', size=8, text=monkey.engine.read(verb['text']), color=vars.Colors.verb_unselected, align=entity.TextAlignment.bottom_left, pos=pos)
    e.add_component(compo.HotSpot(shape=None, onenter=func.change_color(vars.Colors.verb_selected), onleave=func.change_color(vars.Colors.verb_unselected),
                                  onclick=func.on_verb_click(verb_id)))
    return e


# class VerbButton(entity.Text):
#     def __init__(self, font: str, verbId: str, colorInactive, colorActive, align: entity.TextAlignment = entity.TextAlignment.topleft, tag=None, pos=[0,0,0]):
#         verb = s.Config.getVerb(verbId)
#         super().__init__(font, verb.text, colorInactive, align, tag, pos)
#         self.addComponent(compo.HotSpot(
#             shape = None,
#             onenter = change_color(colorActive),
#             onleave = change_color(colorInactive),
#             onclick = verb.callback ))