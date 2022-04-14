import enum
import mopy.monkey as monkey
from mopy.util import tiles_to_world



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

        self.model = None
        self.tag = tag
        self.camera = None
        self.components = []
        self.children = []
        self.scale = None
        self.flip_x = False
        self.layer = 0
        self.transform = None
        self.depth = 0x0201             # GL_LESS is the default
        self.on_create = None
        self.auto_pos = False

    def add(self, entity):
        self.children.append(entity)

    def add_component(self, comp):
        self.components.append(comp)

    def read_children(self, ciao):
        children = ciao.get('children')
        if children:
            tile_size = getattr(monkey.engine.data.globals, 'tile_size',
                                [1, 1])  # monkey.engine.room_vars.get('tile_size', [1, 1])
            for c in children:
                entity_desc = c
                positions = c.get('pos', [0, 0, 0])
                if 'ref' in c:
                    entity_desc = monkey.engine.get_asset(entity_desc, c['ref'])
                factory = monkey.engine.get_item_factory(entity_desc['type'])
                if not factory:
                    print('Don''t have factory for item: ' + entity_desc['type'])
                    exit(1)
                for ip in range(0, len(positions), 3):
                    pos = positions[ip:ip + 3]
                    child = factory(entity_desc)
                    child.pos = tiles_to_world(pos, tile_size)
                    self.children.append(child)


class Sprite(Entity):
    def __init__(self, model: str, anim: str = None, tag=None, pos: tuple = (0, 0, 0), blend: int = 0):
        super().__init__(tag, pos)
        self.type = 'sprite'
        self.model = model
        self.anim = anim
        self.blend = blend


class Skeleton(Entity):
    def __init__(self, model: str, anim: str = None, tag=None, pos: tuple = (0, 0, 0)):
        super().__init__(tag, pos)
        self.type = 'skeleton'
        self.model = model
        self.anim = anim
        self.speed_up = 1.0
        self.depth = 0x0201
        self.model_args = None


class Text(Entity):
    def __init__(self, font: str, size, text: str, color, align: TextAlignment = TextAlignment.top_left, tag = None,
                 pos: tuple = (0, 0, 0), maxwidth=None):
        super().__init__(tag, pos)
        self.type = 'text'
        self.font = font
        self.text = text
        self.size = size
        self.align = align.value
        self.color = color
        self.maxwidth = maxwidth


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
