# importing enum for enumerations 
import lib_py.camera as cam

import enum

# creating enumerations using class 
class TextAlignment(enum.Enum): 
    topleft = 0,
    top = 1,
    topright = 2,
    left = 3,
    center = 4,
    right = 5,
    bottomleft = 6,
    bottom = 7,
    bottomright = 8

class Entity:
    def __init__(self, tag = None, pos = [0, 0, 0]):
        self.type = 'entity'
        self.pos = pos
        self.tag = tag
        self.camera = None
        self.components = []
        self.children = []

    def add(self, entity):
        self.children.append(entity)

    def addComponent(self, comp):
        self.components.append(comp)


class Text(Entity):
    def __init__(self, font: str, text: str, color, align: TextAlignment = TextAlignment.topleft, tag=None, pos=[0,0,0]):
        super().__init__(tag, pos)
        self.type = 'text'
        self.font = font
        self.text = text
        self.align = align
        self.color = color
        