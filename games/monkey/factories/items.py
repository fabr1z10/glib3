import vars
import entity
import monkey
import components as compo
import example
import func
import entity
import scumm.components
import shapes
import scripts.actions

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
        walkarea.depth= kwargs.get('depth', None)
        walls = kwargs.get('walls', None)
        if walls:
            for w in walls:
                walkarea.add_wall([w[0], w[1]], [w[2], w[3]], True)
        e.add_component(walkarea)
        return e
    return f


def character(**kwargs):
    def f(*args):
        key = args[0]
        is_player = key == vars.current_player
        desc = args[1]
        model = desc['model']
        text_color = desc.get('text_color', [255, 255, 255, 255])
        text_offset = desc.get('text_offset', [0, 60])
        pos = desc.get('pos')
        s = entity.Sprite(model=model, pos=pos, tag='player' if is_player else key)
        dir = desc.get('dir', 's')
        s.add_component(scumm.components.CharacterController(dir=dir, speed=100, text_color=text_color, text_offset=text_offset))
        s.add_component(compo.Collider(debug=True, flag=vars.Collision.Flags.player, mask=vars.Collision.Flags.other,
                                       tag=vars.Collision.Tags.player, shape=shapes.Rect(width=8, height=2, offset=[-4, 0])))
        if is_player:
            s.add_component(compo.Follow())
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
        color_inactive=vars.Colors.inv_unselected,
        color_active=vars.Colors.inv_selected)

def make_dialogue_button(dialogueline):
    a = str(dialogueline[1]['text'])
    dialogue_id = dialogueline[0]
    set_tex = vars.dialogues[dialogue_id]['text_set']
    line = monkey.engine.read(a if a[0]=='$' else set_tex + '/' + a)
    return DialogueButton(
        font='ui',
        text=line,
        script=func.execute_dialogue_script(dialogueline),
        color_inactive=vars.Colors.verb_unselected,
        color_active=vars.Colors.verb_selected)
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