class Walkarea:
    def __init__(self, shape):
        self.type = 'scumm.components.walkarea'
        self.shape = shape
        self.depth = None
        self.walls = []

    def add_wall(self, A, B, active):
        self.walls.append(  {'A': A, 'B': B, 'active': active})


class CharacterController:
    def __init__(self, dir, speed, text_color, text_offset, ways=4):
        self.type = 'scumm.components.character_controller'
        self.dir = dir
        self.speed = speed
        self.text_color = text_color
        self.text_offset = text_offset
        self.ways=ways
