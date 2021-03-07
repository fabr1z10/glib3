class Shape:
    def __init__(self, offset = [0, 0]):
        self.offset = offset


class Rect(Shape):
    def __init__(self, width: float, height: float, offset=[0, 0]):
        super().__init__(offset)
        self.type = 'rect'
        self.width = width
        self.height = height


class Line(Shape):
    def __init__(self, a, b, offset=[0, 0]):
        super().__init__(offset)
        self.type = 'line'
        self.A = a
        self.B = b


class Circle(Shape):
    def __init__(self, radius, offset=[0, 0]):
        super().__init__(offset)
        self.type = 'circle'
        self.radius = radius



class SolidFill:
    def __init__(self, r: float, g: float, b: float, a: float = 255):
        self.type = 'fill.solid'
        self.color = [r, g, b, a]

class ConvexPolygon(Shape):
    def __init__(self, points):
        super().__init__([0,0])
        self.type = 'convex_polygon'
        self.points = points

class Poly(Shape):
    def __init__(self, outline):
        super().__init__([0,0])
        self.type = 'poly'
        self.outline = outline
        self.holes = []
