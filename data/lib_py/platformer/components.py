import lib_py.components as compo

class WalkSide(compo.State):
    def __init__(self, id, speed: float, acceleration: float, jumpSpeed: float, flipHorizontal: bool):
        super().__init__(id)
        self.type = 'state.walkside'
        self.speed = speed
        self.acceleration = acceleration
        self.jumpSpeed = jumpSpeed
        self.flipH = flipHorizontal

class FoeWalk(compo.State):
    def __init__(self, id, anim: str, speed: float, acceleration: float, flipHorizontal: bool, flipWhenPlatformEnds: bool, left: int):
        super().__init__(id)
        self.type = 'state.foewalk'
        self.anim = anim
        self.speed = speed
        self.acceleration = acceleration
        self.flipH = flipHorizontal
        self.flipWhenPlatformEnds = flipWhenPlatformEnds
        self.left = left

class KoopaShell(compo.State):
    def __init__(self, id, time: float, time_walk: float):
        super().__init__(id)
        self.type = 'state.koopashell'
        self.time = time
        self.time_walk = time_walk

class FoeDead(compo.State):
    def __init__(self, id: str, anim: str, time: float):
        super().__init__(id)
        self.type = 'state.foedead'
        self.anim = anim
        self.time = time


class Jump(compo.State):
    def __init__(self, id, speed: float, acceleration: float, flipHorizontal: bool, animUp: str, animDown: str):
        super().__init__(id)
        self.type = 'state.jump'
        self.speed = speed
        self.acceleration = acceleration
        self.flipH = flipHorizontal
        self.animUp = animUp
        self.animDown = animDown
