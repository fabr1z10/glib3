import enum


class TextAlignment(enum.Enum):
    top_left = 0
    top = 1
    top_right = 2
    left = 3
    center = 4
    right = 5
    bottom_left = 6
    bottom = 7
    bottom_right = 8


class Entity:
    def __init__(self, tag: str = None, pos: tuple = (0, 0, 0)):
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
        self.flip_x = False

    def add(self, entity):
        self.children.append(entity)

    def add_component(self, comp):
        self.components.append(comp)


class Sprite(Entity):
    def __init__(self, model: str, anim: str = None, tag=None, pos: tuple = (0, 0, 0)):
        super().__init__(tag, pos)
        self.type = 'sprite'
        self.model = model
        self.anim = anim


class Skeleton(Entity):
    def __init__(self, model: str, anim: str = None, tag=None, pos: tuple = (0, 0, 0)):
        super().__init__(tag, pos)
        self.type = 'skeleton'
        self.model = model
        self.anim = anim
        self.speed_up = 1.0


class Text(Entity):
    def __init__(self, font: str, size, text: str, color, align: TextAlignment = TextAlignment.top_left, tag = None,
                 pos: tuple = (0, 0, 0)):
        super().__init__(tag, pos)
        self.type = 'text'
        self.font = font
        self.text = text
        self.size = size
        self.align = align.value
        self.color = color


class TextView(Entity):
    def __init__(self, factory: callable, size, font_size: int, lines: int, delta_x: int, tag=None,
                 pos: tuple = (0, 0, 0)):
        super().__init__(tag, pos)
        self.type = 'textview'
        self.size = size
        self.font_size = font_size
        self.lines = lines
        self.delta_x = delta_x
        self.factory = factory
