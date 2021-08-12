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

class BasicAnimator:
    def __init__(self, idle, walk):
        self.type = 'walkanim.basic'
        self.idle = idle
        self.walk = walk


class YAnimator:
    def __init__(self, idle_up, walk_up, idle_down, walk_down):
        self.type = 'walkanim.y'
        self.idle_up = idle_up
        self.walk_up = walk_up
        self.idle_down = idle_down
        self.walk_down = walk_down


class WalkSide3D(lib.states.State):
    def __init__(self, uid, speed: float, acceleration: float, jump_speed: float, flip_horizontal: bool, animator, keys=None):
        super().__init__(uid, keys)
        self.type = 'state.walkside3d'
        self.speed = speed
        self.acceleration = acceleration
        self.jumpSpeed = jump_speed
        self.flipH = flip_horizontal
        self.animator = animator

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
        self.type = 'state.jump3D'
        self.speed = speed
        self.acceleration = acceleration
        self.flipH = flip_horizontal
        self.animUp = anim_up
        self.animDown = anim_down


class Climb(lib.states.State):
    def __init__(self, uid, speed, idle_anim, climb_anim, keys=None):
        super().__init__(uid, keys)
        self.type ='state.climb'
        self.speed = speed
        self.idle_anim = idle_anim
        self.climb_anim = climb_anim

class Bounce(lib.states.State):
    def __init__(self, uid: str, speed: float, a: float, b: float):
        super().__init__(uid)
        self.type = 'state.bounce'
        self.speed = speed
        self.a = a
        self.b = b


class FoeWalk(lib.states.State):
    def __init__(self, uid, anim: str, speed: float, acceleration: float, flip_horizontal: bool,
                 flip_when_platform_ends: bool, left: int, flip_on_wall: bool = True):
        super().__init__(uid)
        self.type = 'state.foewalk'
        self.anim = anim
        self.speed = speed
        self.acceleration = acceleration
        self.flipH = flip_horizontal
        self.flipWhenPlatformEnds = flip_when_platform_ends
        self.flip_on_wall = flip_on_wall
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

class FoeChase3D(lib.states.State):
    def __init__(self, uid, walk_anim: str, idle_anim: str, speed: float, acceleration: float, attacks, prob_attack: float = 0):
        super().__init__(uid)
        self.type = 'state.foechase3d'
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


class Fly(lib.states.State):
    def __init__(self, uid, anim_up: str, anim_down: str, anim_lie: str, v0):
        super().__init__(uid)
        self.type = 'state.fly'
        self.anim_up = anim_up
        self.anim_down = anim_down
        self.anim_lie = anim_lie
        self.v0 = v0


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