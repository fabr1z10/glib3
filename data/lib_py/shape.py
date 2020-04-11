class Shape:
    def __init__(self, offset = [0, 0]):
        self.offset = offset

class Rect(Shape):
    def __init__(self, width : float, height : float, offset = [0, 0]):
        super().__init__(offset)
        self.type = 'rect'
        self.width = width
        self.height = height

class Polygon(Shape):
    def __init__(self, outline : list, offset = [0, 0]):
        self.type='shape.poly'
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