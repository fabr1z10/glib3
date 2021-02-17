import vars
import entity
import monkey
import components as compo
import example
import func
import entity


def bg(**kwargs):
    def f(*args):
        e = entity.Entity(pos=(args[0], args[1], args[2]))
        e.add_component(compo.Gfx(image = kwargs['image']))
        return e
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