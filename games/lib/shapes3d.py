import shapes


class AABB(shapes.Shape):
    def __init__(self, size, offset=(0, 0, 0)):
        super().__init__(offset)
        self.type = 'shape3d.aabb'
        self.size = size


class Prism(shapes.Shape):
    def __init__(self, shape, height, offset=(0, 0, 0)):
        super().__init__(offset)
        self.shape = shape
        self.height = height
        self.type = 'shape3d.prism'


class Plane(shapes.Shape):
    def __init__(self, n, d):
        super().__init__((0, 0, 0))
        self.type = 'shape3d.plane'
        self.n = n
        self.d = d
