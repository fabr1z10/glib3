from lib_py.room import Room
from lib_py.entity import Entity
from lib_py.camera import OrthoCamera
from lib_py.runner import CollisionEngine, CollisionResponse, Scheduler, DynamicWorld
import physics.vars as var
import example

def f (player : example.Wrap1, item : example.Wrap1, x, y):
    item.setColor ([0, 0, 0, 0], [255, 0, 0, 255])
    print ('ciao')

def g (player : example.Wrap1, item : example.Wrap1, x, y):
    item.setColor ([255, 255, 255, 255], [0, 0, 0, 0])
    print ('ciao')

class Phy2DRoom(Room):
    def __init__(self, id:str, width, height, worldWidth: int, worldHeight : int):
        super().__init__(id, width, height)
        # adding pause button
        #self.keyl.addKey(key=32, func = f)
        #self.keyl.addKey(key=264, func = checkWarp)

        main = Entity (tag='main')
        main.camera = OrthoCamera(
            worldwidth = worldWidth, 
            worldheight = worldHeight, 
            camwidth = width, 
            camheight = height, 
            viewport = [0, 0, width, height], 
            tag='maincam')
        self.add(main)

        # create the collision engine (maybe to put into the ctor of the room subclass)
        ce = CollisionEngine(80, 80)
        ce.addResponse (var.Tags.player, var.Tags.wall, CollisionResponse(onenter=f, onleave=g))
        self.addRunner(ce)
        self.addRunner(Scheduler())
