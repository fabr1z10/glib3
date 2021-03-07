class Walkarea:
    def __init__(self, shape):
        self.type = 'scumm.components.walkarea'
        self.shape = shape

class CharacterController:
    def __init__(self, dir):
        self.type = 'scumm.components.character_controller'
        self.dir = dir
