class SolidFill:
    def __init__(self, r: float, g: float, b: float, a: float = 255):
        self.type = 'fill.solid'
        self.color = [r, g, b, a]

class LinearGradient:
    def __init__(self, color0, p0, color1, p1):
        self.type = 'fill.lineargradient'
        self.color0 = color0
        self.color1 = color1
        self.p0 = p0
        self.p1 = p1


class Shape:
    def __init__(self, offset = [0, 0]):
        self.offset = offset

class Line(Shape):
    def __init__(self, A, B, offset = [0, 0]):
        super().__init__(offset)
        self.type = 'line'
        self.A = A
        self.B = B

class Rect(Shape):
    def __init__(self, width : float, height : float, offset = [0, 0]):
        super().__init__(offset)
        self.type = 'rect'
        self.width = width
        self.height = height

class Circle(Shape):
    def __init__(self, radius: float, offset = [0, 0]):
        super().__init__(offset)
        self.type = 'shape.circle'
        self.radius = radius

class Ellipse(Shape):
    def __init__(self, width : float, height : float, offset = [0, 0]):
        super().__init__(offset)
        self.type = 'shape.ellipse'
        self.width = width
        self.height = height


class Polygon(Shape):
    def __init__(self, outline : list, offset = [0, 0], holes: list = None):
        self.type='shape.poly'
        super().__init__(offset)
        self.outline = outline
        self.holes = holes

class PolygonSimple(Shape):
    def __init__(self, outline : list, offset = [0, 0], holes: list = None):
        self.type='shape.polygon'
        super().__init__(offset)
        self.outline = outline

class PolygonTri(Shape):
    def __init__(self, outline : list, offset = [0, 0]):
        self.type='shape.polygontri'
        super().__init__(offset)
        self.outline = outline


class Graph(Shape):
    def __init__(self, nodes : list, edges: list, offset = [0, 0]):
        self.type='shape.graph'
        super().__init__(offset)
        self.nodes = nodes
        self.edges = edges

class LinX:
    def __init__(self, x0 : float, z0: float, x1: float, z1: float):
        self.type = 'func.linx'
        self.values = [x0, z0, x1, z1]


class LinY:
    def __init__(self, y0 : float, z0: float, y1: float, z1: float):
        self.type = 'func.liny'
        self.values = [y0, z0, y1, z1]

class Const:
    def __init__(self, x: float):
        self.type = 'func.const'
        self.value = x

class Patch2D:
    def __init__(self):
        self.type = 'func.patch2d'
        self.rect = []

    def addFunc (self, x: float, y: float, width: float, height: float, f):
        self.rect.append({
            'pos': [x, y],
            'size': [width, height],
            'func': f
        })