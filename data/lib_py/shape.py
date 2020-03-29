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
        

