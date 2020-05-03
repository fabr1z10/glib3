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

class Graph(Shape):
    def __init__(self, nodes : list, edges: list, offset = [0, 0]):
        self.type='shape.graph'
        super().__init__(offset)
        self.nodes = nodes
        self.edges = edges


class LinY:
    def __init__(self, y0 : float, z0: float, y1: float, z1: float):
        self.type = 'func.liny'
        self.values = [y0, z0, y1, z1]
