import lib_py.components as compo
import lib_py.script as script
import lib_py.scumm.actions as sa 
import example

def walkto(x, y, obj):
    ds = example.getDeviceSize()
    print('device size is ' + str(ds))
    s = script.Script()
    s.addAction( sa.Walk(pos = [x, y], tag = 'player'))
    example.play(s)    
    print ('clicked on ' + str(x) + ', ' + str(y))

class Walkarea(compo.HotSpot):
    def __init__(self, shape):
        super().__init__(shape)
        self.type = 'components.walkarea'
        self.onclick = walkto

class Character():
    def __init__(self, speed: float, dir: str, state: str):
        self.type = 'components.character'
        self.speed = speed
        self.dir = dir
        self.state = state