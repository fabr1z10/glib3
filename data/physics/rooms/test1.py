import example
import yaml
from physics.room import Phy2DRoom
import lib_py.engine as engine

from lib_py.entity import Entity
from lib_py.components import ShapeGfxOutline, StateMachine, Walk3D, KeyInput, Collider
from lib_py.shape import Rect, Line, PolygonSimple, Circle

import physics.vars as var

def s(x: float, y: float, shape):
    o1 = Entity (pos = [x, y])
    o1.addComponent (ShapeGfxOutline(shape, color=[255,255,255,255]))
    o1.addComponent (Collider(flag=var.Flags.wall, mask = var.Flags.player, tag= var.Tags.wall, shape=shape))
    return o1


def builder():
    r = Phy2DRoom(id='test1', width=256, height=256,worldWidth= 256,worldHeight= 256)
    
    # add player
    p = Entity( pos = [160, 100])
    shape_player = Rect (10, 20, offset=[-5,-10])
    p.addComponent (ShapeGfxOutline(shape_player, color=[255, 255, 255, 255]))
    p.addComponent (Collider(flag=var.Flags.player, mask = var.Flags.wall, tag = var.Tags.player, shape = shape_player))
    sm = StateMachine('walk')
    sm.states.append(Walk3D('walk', 5))
    p.addComponent(sm)
    p.addComponent(KeyInput())
    r.add (p, 'main')

    # add object
    o1 = Entity (pos= [200,170])
    o_shape = Rect(20,10)
    o1.addComponent (ShapeGfxOutline(o_shape, color=[255,255,255,255]))
    o1.addComponent (Collider(flag=var.Flags.wall, mask = var.Flags.player, tag= var.Tags.wall, shape=o_shape))
    r.add(o1, 'main')

    r.add (s(10,80,Line(A=[0,0],B=[50,25])), 'main')
    r.add (s(30,130,PolygonSimple(outline=[0, 0, 10, 0, 5, 20])), 'main')
    r.add (s(150,30,Circle(20)), 'main')
    #r.add (s(-150,80,Line(A=[0,0],B=[50,25])), 'main')
    return r

engine.addRoom (id = 'test1', f=builder)
