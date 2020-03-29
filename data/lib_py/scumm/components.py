import lib_py.components as compo

class Walkarea(compo.HotSpot):
    def __init__(self, shape):
        super().__init__(shape)
        self.type = 'components.walkarea'
