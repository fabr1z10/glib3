#import lib_py.room as room
from smb_py.room import PlatformerRoom
import lib_py.engine as engine
from lib_py.camera import OrthoCamera
import lib_py.entity as entity
import lib_py.shape as sh
import lib_py.components as compo
import smb_py.vars as vars
import smb_py.funcs as func
import smb_py.factories as fact
import lib_py.platformer.components as pc
from lib_py.runner import CollisionEngine, CollisionResponse, DynamicWorld, Scheduler
import example




def builder():
    r = PlatformerRoom(
        id = 'world1_1', 
        width = 256, 
        height = 256, 
        worldWidth = 224, 
        worldHeight = 16, 
        playerModel = 'mario', 
        startPos = [1, 5])
    # room.Room(id='world1_1', width=256, height=256)
    # r.keyl.addKey(key=32, func = f)
    # main = entity.Entity (tag='main')
    # main.camera = OrthoCamera(worldwidth= 224 * vars.tileSize, worldheight = 16 * vars.tileSize, 
    #     camwidth=256, camheight=256, viewport=[0, 0, 256, 256], tag='maincam')
    # r.add(main)

    # # create the collision engine (maybe to put into the ctor of the room subclass)
    # ce = CollisionEngine(80, 80)
    # ce.addResponse(vars.tags.player, vars.tags.brick_sensor, CollisionResponse(onenter=func.brickResponse))
    # ce.addResponse(vars.tags.player, vars.tags.bonus_brick_sensor, CollisionResponse(onenter=func.bonusBrickResponse))
    # ce.addResponse(vars.tags.player, vars.tags.mushroom, CollisionResponse(onenter=func.mushroomResponse))
    # ce.addResponse(vars.tags.player, vars.tags.warp, CollisionResponse(onenter = func.warpEnter, onleave= func.warpExit))


    # r.addRunner(ce)
    # r.addRunner(Scheduler())

    # dw = DynamicWorld(256, 256, 'maincam')
    # r.addRunner(dw)

    f1 = fact.makePlatform
    # add a platform
    
    a = [
        #func.makePlatform (img = 'gfx/block1.png', x=0, y=0, width=2, height=2),
        #func.makePlatform (img = 'gfx/block1.png', x=4, y=0, width=2, height=2),

        f1(img = 'gfx/block1.png', x=0, y=0, width=69, height=2),
        f1(img = 'gfx/block1.png', x=71, y=0, width=15, height=2),
        f1(img = 'gfx/block1.png', x=89, y=0, width=64, height=2),
        f1(img = 'gfx/block1.png', x=155, y=0, width=69, height=2),
        f1('gfx/block2.png', 134, 2, 4, 1),
        f1('gfx/block2.png', 135, 3, 3, 1),
        f1('gfx/block2.png', 136, 4, 2, 1),
        f1('gfx/block2.png', 137, 5, 1, 1),
        f1('gfx/block2.png', 140, 5, 1, 1),
        f1('gfx/block2.png', 140, 4, 2, 1),
        f1('gfx/block2.png', 140, 3, 3, 1),
        f1('gfx/block2.png', 140, 2, 4, 1),
        f1('gfx/block2.png', 148, 2, 5, 1),
        f1('gfx/block2.png', 149, 3, 4, 1),
        f1('gfx/block2.png', 150, 4, 3, 1),
        f1('gfx/block2.png', 151, 5, 2, 1),
        f1('gfx/block2.png', 155, 5, 1, 1),
        f1('gfx/block2.png', 155, 4, 2, 1),
        f1('gfx/block2.png', 155, 3, 3, 1),
        f1('gfx/block2.png', 155, 2, 4, 1),
        f1('gfx/block2.png', 181, 2, 9, 1),
        f1('gfx/block2.png', 182, 3, 8, 1),
        f1('gfx/block2.png', 183, 4, 7, 1),
        f1('gfx/block2.png', 184, 5, 6, 1),
        f1('gfx/block2.png', 185, 6, 5, 1),
        f1('gfx/block2.png', 186, 7, 4, 1),
        f1('gfx/block2.png', 187, 8, 3, 1),
        f1('gfx/block2.png', 188, 9, 2, 1),
        f1('gfx/block2.png', 198, 2, 1, 1),
        f1('gfx/block4.png', 0, 16, 16, 2),
        f1('gfx/brick2.png', 0, 18, 1, 11),
        f1('gfx/brick2.png', 4, 18, 7, 3),
        f1('gfx/brick2.png', 4, 28, 7, 1),
        fact.makeBrick('brick', 5, 5),
        fact.bonusBrick (model = 'bonusbrick', x= 7, y=5, callback = fact.m1),
        fact.bonusBrick (model = 'bonusbrick', x= 9, y=5, callback = fact.m2),
        fact.warpDown (x=5, y=2, width=16, height=2, callback = func.warpIn(warpTo=[2, 25], newCamBounds=[0,256,256,512])),
        fact.pipe2 (6, 2)
        #fact.tiled(x=6, y=2, z=-1, size=16, tileSheet='gfx/smb1.png', sheetSize=[16, 16], tileData=[0, 4, 1, 4, 0, 3, 1, 3], width=2, height=2)
    ]
    #{71, 0, 15, 2}, {89, 0, 64, 2}, {155, 0, 69, 2}}
    #a = entity.Entity()
    #a.addComponent (compo.Gfx(image='gfx/block1.png', repeat = [69, 2]))
    #a.addComponent (compo.Collider(flag = vars.flags.platform, mask = vars.flags.player, tag = 1, shape = sh.Rect(width=69*16, height=16*2)))

    # add player
    # mario = entity.Sprite(model = 'mario', pos = [16,5*16], tag='player')
    # mario.addComponent (compo.SmartCollider(
    #     flag = vars.flags.player,
    #     mask = vars.flags.foe | vars.flags.foe_attack,
    #     tag = vars.tags.player))
    # mario.addComponent (compo.Controller2D(
    #     maskUp = vars.flags.platform, 
    #     maskDown = vars.flags.platform | vars.flags.platform_passthrough, 
    #     maxClimbAngle = 80, 
    #     maxDescendAngle = 80))
    # mario.addComponent (compo.Dynamics2D(gravity= vars.gravity))
    # stateMachine = compo.StateMachine(initialState='walk')
    # stateMachine.states.append (pc.WalkSide(id='walk', speed=75, acceleration=0.05, jumpSpeed= vars.jump_velocity, flipHorizontal=True))
    # stateMachine.states.append (pc.Jump(id='jump', speed=75, acceleration=0.10, flipHorizontal=True, animUp='jump', animDown='jump'))

    # mario.addComponent (stateMachine)
    # mario.addComponent (compo.KeyInput())    
    # mario.addComponent (compo.Follow())

    # main.add(mario)
    for e in a:
        r.addToDynamicWorld(e)
        #dw.items.append(e)  
    return r

engine.addRoom (id = 'world1_1', f=builder)
#settings.monkey.rooms['lookout'] = builder
#settings.engine['rooms']['lookout'] = builder