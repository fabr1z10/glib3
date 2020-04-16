import lib_py.components as compo

class WalkSide(compo.State):
    def __init__(self, id, speed: float, acceleration: float, jumpSpeed: float, flipHorizontal: bool):
        super().__init__(id)
        self.type = 'state.walkside'
        self.speed = speed
        self.acceleration = acceleration
        self.jumpSpeed = jumpSpeed
        self.flipH = flipHorizontal


class Jump(compo.State):
    def __init__(self, id, speed: float, acceleration: float, flipHorizontal: bool, animUp: str, animDown: str):
        super().__init__(id)
        self.type = 'state.jump'
        self.speed = speed
        self.acceleration = acceleration
        self.flipH = flipHorizontal
        self.animUp = animUp
        self.animDown = animDown
