import lib_py.entity as entity
import lib_py.components as compo

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
            onenter = change_color(colorActive), 
            onleave = change_color(colorInactive),
            onclick = set_verb(text) )) 



# class Sprite(entity.Entity):
#     def __init__(self, sprite : str, tag = None, pos = [0, 0, 0]):
#         super().__init__(tag, pos)
#         self.type = 'sprite'
#         self.model = sprite
#         #self.addComponent (compo.Gfx(image=image))