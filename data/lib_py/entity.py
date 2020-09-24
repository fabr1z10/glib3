# importing enum for enumerations 
import lib_py.camera as cam

import enum

# creating enumerations using class 
class TextAlignment(enum.Enum): 
    topleft = 0
    top = 1
    topright = 2
    left = 3
    center = 4
    right = 5
    bottomleft = 6
    bottom = 7
    bottomright = 8



class Entity:
    def __init__(self, tag : str = None, pos: tuple = (0,0,0)):
        """
        Parameters
        ----------
        tag : str, optional
            A string that uniquely identifier the entity
        
        pos : list, optional
            The position in the world where the entity is located
        """

        self.type = 'entity'
        if len(pos) == 2:
            self.pos = (pos[0], pos[1], 0)
        else:
            self.pos = pos
        
        self.tag = tag
        self.camera = None
        self.components = []
        self.children = []
        self.scale = None

    def add(self, entity):
        """A simple function that says hello... Richie style"""
        self.children.append(entity)

    def addComponent(self, comp):
        self.components.append(comp)

class Sprite(Entity):
    def __init__(self, model: str, anim: str = None, tag = None, pos = [0,0,0]):
        super().__init__(tag, pos)
        self.type = 'sprite'
        self.model = model
        self.anim = anim
        
class Skeleton(Entity):
    def __init__(self, model: str, anim: str = None, tag = None, pos = [0,0,0]):
        super().__init__(tag, pos)
        self.type = 'skeleton'
        self.model = model
        self.anim = anim


class Text(Entity):
    def __init__(self, font: str, size, text: str, color, align: TextAlignment = TextAlignment.topleft, tag=None, pos=[0,0,0]):
        super().__init__(tag, pos)
        self.type = 'text'
        self.font = font
        self.text = text
        self.size = size
        #print ('cazz0 ' + str(align.value))
        self.align = align.value
        self.color = color
        
class TextView(Entity):
    def __init__(self, factory: callable,size, fontSize: int, lines: int, deltax: int, tag = None, pos = [0,0,0]):
        super().__init__(tag, pos)
        self.type = 'textview'
        self.size = size
        self.fontSize = fontSize
        self.lines = lines
        self.deltax = deltax
        self.factory = factory
