import lib.states


class KeyMove(lib.states.State):
    def __init__(self, uid, speed: float, rotation_speed: float,  keys=None):
        super().__init__(uid, keys)
        self.type = 'state.keymove'
        self.speed = speed
        self.rotation_speed = rotation_speed

class KeyMoveF(lib.states.State):
    def __init__(self, uid, speed: float,  keys=None):
        super().__init__(uid, keys)
        self.type = 'state.keymovef'
        self.speed = speed


class WalkSide(lib.states.State):
    def __init__(self, uid, speed: float, acceleration: float, jump_speed: float, flip_horizontal: bool, keys=None):
        super().__init__(uid, keys)
        self.type = 'state.walkside'
        self.speed = speed
        self.acceleration = acceleration
        self.jumpSpeed = jump_speed
        self.flipH = flip_horizontal

class WalkSide3D(lib.states.State):
    def __init__(self, uid, speed: float, acceleration: float, jump_speed: float, flip_horizontal: bool, keys=None):
        super().__init__(uid, keys)
        self.type = 'state.walkside3d'
        self.speed = speed
        self.acceleration = acceleration
        self.jumpSpeed = jump_speed
        self.flipH = flip_horizontal

class Jump(lib.states.State):
    def __init__(self, uid, speed: float, acceleration: float, flip_horizontal: bool, anim_up: str = None, anim_down: str = None, keys=None):
        super().__init__(uid, keys)
        self.type = 'state.jump'
        self.speed = speed
        self.acceleration = acceleration
        self.flipH = flip_horizontal
        self.animUp = anim_up
        self.animDown = anim_down

class Jump3D(lib.states.State):
    def __init__(self, uid, speed: float, acceleration: float, flip_horizontal: bool, anim_up: str = None, anim_down: str = None, keys=None):
        super().__init__(uid, keys)
        self.type = 'state.jump'
        self.speed = speed
        self.acceleration = acceleration
        self.flipH = flip_horizontal
        self.animUp = anim_up
        self.animDown = anim_down

class Bounce(lib.states.State):
    def __init__(self, uid: str, speed: float, a: float, b: float):
        super().__init__(uid)
        self.type = 'state.bounce'
        self.speed = speed
        self.a = a
        self.b = b


class FoeWalk(lib.states.State):
    def __init__(self, uid, anim: str, speed: float, acceleration: float, flip_horizontal: bool, flip_when_platform_ends: bool, left: int):
        super().__init__(uid)
        self.type = 'state.foewalk'
        self.anim = anim
        self.speed = speed
        self.acceleration = acceleration
        self.flipH = flip_horizontal
        self.flipWhenPlatformEnds = flip_when_platform_ends
        self.left = left


class FoeChase(lib.states.State):
    def __init__(self, uid, walk_anim: str, idle_anim: str, speed: float, acceleration: float, attacks, prob_attack: float = 0):
        super().__init__(uid)
        self.type = 'state.foechase'
        self.walkanim = walk_anim
        self.idleanim = idle_anim
        self.speed = speed
        self.acceleration = acceleration
        self.attacks = attacks
        self.probattack = prob_attack


class IsHit (lib.states.State):
    def __init__(self, uid,anim: str, acceleration: float, dist):
        super().__init__(uid)
        self.type = 'state.hit'
        self.anim = anim
        self.acceleration = acceleration
        self.dist = dist


class JAttack (lib.states.State):
    def __init__(self, uid: str, animup: str, animdown: str, animland: str, height: float, hit_mask: int, timeDown = 1, callback = None):
        super().__init__(uid)
        self.type = 'state.jattack'
        self.anim_up = animup
        self.anim_down = animdown
        self.anim_land = animland
        self.jump_height = height
        self.time_down = timeDown
        self.hit_mask = hit_mask
        self.callback = callback