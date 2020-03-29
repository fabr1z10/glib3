import lib_py.entity as entity
import lib_py.components as compo
import lib_py.scumm.components as sc
import lib_py.shape as sh

import example

def change_color(color):
    def f(e : example.Wrap1):
        e.setColor(color)
    return f    

def set_verb(verb):
    def f(e : example.Wrap1):
        a : example.Wrap1 = example.what.get('current_verb')
        a.setText (verb)
    return f

class BackgroundItem(entity.Entity):
    def __init__(self, image = None, tag = None, pos = [0, 0, 0]):
        super().__init__(tag, pos)
        self.addComponent (compo.Gfx(image=image))

class VerbButton(entity.Text):
    def __init__(self, font: str, text: str, colorInactive, colorActive, align: entity.TextAlignment = entity.TextAlignment.topleft, tag=None, pos=[0,0,0]):
        super().__init__(font, text, colorInactive, align, tag, pos)          
        self.addComponent(compo.HotSpot(
            shape = None,
            onenter = change_color(colorActive), 
            onleave = change_color(colorInactive),
            onclick = set_verb(text) )) 

class WalkArea(entity.Entity):
    def __init__(self, shape, depth = None, priority : int = 0, tag = None, pos = [0,0,0]):
        super().__init__(tag, pos)
        self.addComponent(sc.Walkarea(shape = shape))
        #self.shape = shape
        #self.depth = depth
        #self.priority = priority

class Sprite(entity.Entity):
    def __init__(self, model: str, tag = None, pos = [0,0,0]):
        super().__init__(tag, pos)
        self.type = 'sprite'
        self.model = model


# class Sprite(entity.Entity):
#     def __init__(self, sprite : str, tag = None, pos = [0, 0, 0]):
#         super().__init__(tag, pos)
#         self.type = 'sprite'
#         self.model = sprite
#         #self.addComponent (compo.Gfx(image=image))