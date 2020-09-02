import lib_py.components as compo
import lib_py.script as script
import lib_py.scumm.functions as func
#import lib_py.scumm.actions as sa 
import example



class Walkarea(compo.HotSpot):
    def __init__(self, shape, depth = None, scale = None, blocked_lines = None):
        super().__init__(shape)
        self.type = 'components.walkarea'
        self.onclick = func.walkto
        self.depth= depth
        self.scale = scale
        self.blocked_lines = blocked_lines

class Character():
    def __init__(self, speed: float, dir: str, state: str):
        self.type = 'components.character'
        self.speed = speed
        self.dir = dir
        self.state = state

