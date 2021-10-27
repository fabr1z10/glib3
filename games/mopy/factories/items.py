from mopy.entity import Entity
from mopy.components import Gfx


def model3d(**kwargs):
    def f(*args):
        e = Entity(pos=(args[0], args[1], args[2]))
        renderer = Gfx(image=kwargs.get('image'))
        renderer.cls = 5
        e.add_component(renderer)
        return e
    return f

