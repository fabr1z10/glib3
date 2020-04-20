from lib_py.room import Room
from lib_py.entity import Entity
from lib_py.camera import OrthoCamera
from lib_py.runner import CollisionEngine, CollisionResponse, Scheduler, DynamicWorld
import smb_py.funcs as func
import smb_py.builder as build
import smb_py.vars as vars

def f():
    print('toggle pause!')
    func.upgradePlayer()

def checkWarp():
    if vars.warp_func:
        vars.warp_func()

class PlatformerRoom(Room):
    def __init__(self, id:str, width, height, worldWidth: int, worldHeight : int, playerModel: str, startPos):
        super().__init__(id, width, height)
        # adding pause button
        self.keyl.addKey(key=32, func = f)
        self.keyl.addKey(key=264, func = checkWarp)

        main = Entity (tag='main')
        main.camera = OrthoCamera(worldwidth = worldWidth * vars.tileSize, worldheight = worldHeight * vars.tileSize, 
        camwidth=width, camheight=height, viewport=[0, 0, width, height], tag='maincam')
        self.add(main)

        # create the collision engine (maybe to put into the ctor of the room subclass)
        ce = CollisionEngine(80, 80)
        ce.addResponse(vars.tags.player, vars.tags.brick_sensor, CollisionResponse(onenter=func.brickResponse))
        ce.addResponse(vars.tags.player, vars.tags.bonus_brick_sensor, CollisionResponse(onenter=func.bonusBrickResponse))
        ce.addResponse(vars.tags.player, vars.tags.mushroom, CollisionResponse(onenter=func.mushroomResponse))
        ce.addResponse(vars.tags.player, vars.tags.warp, CollisionResponse(onenter = func.warpEnter, onleave= func.warpExit))
        ce.addResponse(vars.tags.player, vars.tags.hotspot, CollisionResponse(onenter = func.hotspotEnter))
        ce.addResponse(vars.tags.player, vars.tags.coin, CollisionResponse(onenter = func.coinResponse))
        ce.addResponse(vars.tags.player, vars.tags.goomba, CollisionResponse(onenter = func.goombaResponse))
        ce.addResponse(vars.tags.player, vars.tags.koopa, CollisionResponse(onenter = func.koopaResponse))

        self.addRunner(ce)
        self.addRunner(Scheduler())

        self.dw = DynamicWorld(256, 256, 'maincam')
        self.addRunner(self.dw)

        # add player
        mario = build.makePlayer(playerModel, startPos[0], startPos[1])
        main.add(mario)

    def addToDynamicWorld(self, e):
        self.dw.items.append(e)
