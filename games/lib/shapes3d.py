import shapes

class AABB(shapes.Shape):
    def __init__(self, size, offset = (0, 0, 0)):
        super().__init__(offset)
        self.type = 'shape3d.aabb'
        self.size = size

