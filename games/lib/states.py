class State:
    def __init__(self, uid: str, keys=None):
        self.id = uid
        self.keys = [] if keys is None else keys


class NullState(State):
    def __init__(self, uid: str):
        super().__init__(uid)
        self.type = 'state.null'


class SimpleState (State):
    def __init__(self, uid: str, anim: str):
        super().__init__(uid)
        self.type = 'state.simple'
        self.anim = anim


class Attack(State):
    def __init__(self, uid: str, anim: str):
        super().__init__(uid)
        self.type = 'state.attack'
        self.anim = anim


class JumpAttack(State):
    def __init__(self, uid: str, anim: str, speed: float, acceleration: float, flip_horizontal: bool):
        super().__init__(uid)
        self.type = 'state.jumpattack'
        self.speed = speed
        self.acceleration = acceleration
        self.flipH = flip_horizontal
        self.anim = anim


class StateCallback:
    def __init__(self, f: callable):
        self.type = 'stateaction.callback'
        self.f = f


class StateTransition:
    def __init__(self, state : str):
        self.type = 'stateaction.statetransition'
        self.state = state