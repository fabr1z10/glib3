import lib_py.components as compo
import lib_py.script as script
#import lib_py.scumm.actions as sa 
import lib_py.scumm.functions as func
import example



class Walkarea(compo.HotSpot):
    def __init__(self, shape):
        super().__init__(shape)
        self.type = 'components.walkarea'
        self.onclick = func.walkto

class Character():
    def __init__(self, speed: float, dir: str, state: str):
        self.type = 'components.character'
        self.speed = speed
        self.dir = dir
        self.state = state

class CharacterInfo():
    def __init__(self, text_color : list, text_offset : list):
        self.type = 'components.info'
        self.text_color = text_color
        self.text_offset = text_offset