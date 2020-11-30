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


class SolidFill:
    def __init__(self, r: float, g: float, b: float, a: float = 255):
        self.type = 'fill.solid'
        self.color = [r, g, b, a]

