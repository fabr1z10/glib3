from lib_py.entity import Entity, Sprite
import lib_py.components as compo
import lib_py.shape as sh
import smb_py.funcs as func
from lib_py.script import Script
import smb_py.vars as vars
import lib_py.platformer.components as pc
import lib_py.actions as act
from lib_py.camera import OrthoCamera
from lib_py.room import Room
import smb_py.tiles as tiles 
from lib_py.runner import CollisionEngine, CollisionResponse, Scheduler, DynamicWorld
import example

def m1(x: float, y: float):
    a = mushroom(x, y)
    main = example.get('main')
    id = main.add(a)
    s = Script()
    s.addAction(act.Move(id =id, speed=10, by=[0, 16]))
    s.addAction(act.SetState (id = id, state='walk'))
    example.play(s) 

def m2(x: float, y: float):
    def score():
        m3(x, y+1)
    a = spr('flyingcoin', x, y+1)
    main = example.get('main')
    id = main.add(a)
    s = Script()
    s.addAction(act.MoveAccelerated(v0 = [0, 100], a = [0, -100], yStop = (y*vars.tileSize) +16, id = id))
    s.addAction(act.RemoveEntity(id=id))
    s.addAction(act.CallFunc(f = score))
    #s.addAction(act.SetState (id = id, state='walk'))
    example.play(s) 

def m3(x: float, y: float):
    a = spr('score100', x, y)
    main = example.get('main')
    id = main.add(a)
    s = Script()
    s.addAction(act.Move(speed=100, by=[0, 64], id = id))
    s.addAction(act.RemoveEntity(id=id))
    example.play(s)


def makePlayer(model: str, x: float, y: float):
    player = Sprite(model = model, pos = [x * vars.tileSize, y*vars.tileSize], tag='player')
    player.addComponent (compo.SmartCollider(
        flag = vars.flags.player,
        mask = vars.flags.foe | vars.flags.foe_attack,
        tag = vars.tags.player))
    player.addComponent (compo.Controller2D(
        maskUp = vars.flags.platform, 
        maskDown = vars.flags.platform | vars.flags.platform_passthrough, 
        maxClimbAngle = 80, 
        maxDescendAngle = 80))
    speed = 75
    player.addComponent (compo.Dynamics2D(gravity= vars.gravity))
    stateMachine = compo.StateMachine(initialState='walk')
    stateMachine.states.append (compo.SimpleState (id='warp', anim='idle'))
    stateMachine.states.append (pc.WalkSide(id='walk', speed=200, acceleration=0.05, jumpSpeed= vars.jump_velocity, flipHorizontal=True))
    stateMachine.states.append (pc.Jump(id='jump', speed=200, acceleration=0.10, flipHorizontal=True, animUp='jump', animDown='jump'))
    stateMachine.states.append (pc.FoeWalk(id='demo', anim='walk', speed = 75, 
        acceleration=0.05, flipHorizontal=True, flipWhenPlatformEnds = False, left=1))
    player.addComponent (stateMachine)
    player.addComponent (compo.KeyInput())    
    player.addComponent (compo.Follow())
    return player

def makeGoomba(model: str, x: float, y: float):
    goomba = Sprite(model = model, pos = [x * vars.tileSize, y * vars.tileSize])
    goomba.addComponent (compo.SmartCollider(
        flag = vars.flags.foe,
        mask = vars.flags.player,
        tag = vars.tags.goomba))
    goomba.addComponent (compo.Controller2D(
        maskUp = vars.flags.platform, 
        maskDown = vars.flags.platform | vars.flags.platform_passthrough, 
        maxClimbAngle = 80, 
        maxDescendAngle = 80))
    goomba.addComponent (compo.Dynamics2D(gravity= vars.gravity))
    #{ type="garbage", target="maincam", max_dist = {256, 256}},
    stateMachine = compo.StateMachine(initialState='walk')
    stateMachine.states.append (pc.FoeWalk(id='walk', anim='walk', speed = 20, 
        acceleration=0, flipHorizontal=False, flipWhenPlatformEnds=False, left=1))
    stateMachine.states.append (pc.FoeDead(id='dead', anim='dead', time = 2))
    goomba.addComponent (stateMachine)
    return goomba

def makeKoopa (model: str, x: float, y: float):
    koopa = Sprite(model = model, pos = [x * vars.tileSize, y * vars.tileSize])
    koopa.addComponent (compo.SmartCollider(
        flag = vars.flags.foe,
        mask = vars.flags.player,
        tag = vars.tags.koopa))
    koopa.addComponent (compo.Controller2D(
        maskUp = vars.flags.platform, 
        maskDown = vars.flags.platform | vars.flags.platform_passthrough, 
        maxClimbAngle = 80, 
        maxDescendAngle = 80))
    koopa.addComponent (compo.Dynamics2D(gravity= vars.gravity))
    stateMachine = compo.StateMachine(initialState='walk')
    stateMachine.states.append (pc.FoeWalk(id='walk', anim='walk', speed = 20, 
        acceleration=0, flipHorizontal=True, flipWhenPlatformEnds=False, left=1))
    stateMachine.states.append (pc.FoeWalk(id='walk2', anim='hide', speed = 100, 
        acceleration=0, flipHorizontal=False, flipWhenPlatformEnds=False, left=1))    
    stateMachine.states.append (pc.KoopaShell(id='hide', time = 2, time_walk = 4))
    koopa.addComponent (stateMachine)
    return koopa




def makePlatform(img : str, x:float, y:float, width : int, height: int):
    a = Entity()
    a.addComponent (compo.Gfx(image = img, repeat = [width, height]))
    a.addComponent (compo.Collider(flag = vars.flags.platform, mask = vars.flags.player, tag = 1, 
        shape = sh.Rect(width = width * vars.tileSize, height = height * vars.tileSize)))
    print ('position ' + str(x*vars.tileSize))
    a.pos = (x * vars.tileSize, y * vars.tileSize, 0)
    return a

def makeBrick(model: str, x: float, y: float):
    a = Sprite(model = model)
    a.addComponent (compo.Collider (flag = vars.flags.platform, mask = 0, tag = 0, 
        shape = sh.Rect(width=vars.tileSize, height=vars.tileSize)))
    a.pos = [x * vars.tileSize, y * vars.tileSize, 0]
    
    b = Entity()
    b.pos = [2, -0.5, 0]
    b.addComponent (compo.Collider (
        flag=vars.flags.foe,
        mask=vars.flags.player,
        tag = vars.tags.brick_sensor,
        shape = sh.Rect(width = vars.tileSize-4, height = 1.0)
    ))
    a.add(b)
    return a

def bonusBrick(model: str, x: float, y: float, callback: callable, hits: int = 1):
    a = Sprite(model = model, pos= [x * vars.tileSize, y * vars.tileSize, 0])
    a.addComponent (compo.Collider (flag = vars.flags.platform, mask = 0, tag = 0, 
        shape = sh.Rect(width=vars.tileSize, height=vars.tileSize)))
    a.addComponent (compo.Info ( 
        hitsLeft = hits,
        callback = callback ))
    b = Entity()
    b.pos = [2, -0.5, 0]
    b.addComponent (compo.Collider (
        flag = vars.flags.foe,
        mask = vars.flags.player,
        tag = vars.tags.bonus_brick_sensor,
        shape = sh.Rect(width = vars.tileSize - 4, height = 1.0)
    ))
    a.add(b)
    return a


def mushroom(x: float, y: float):
    a = Sprite(model='mushroom', pos = [x*vars.tileSize, y*vars.tileSize, 1])
    a.addComponent (compo.SmartCollider(
        flag = vars.flags.foe,
        mask = vars.flags.player,
        tag = vars.tags.mushroom))
    a.addComponent (compo.Controller2D(
        maskUp = vars.flags.platform, 
        maskDown = vars.flags.platform | vars.flags.platform_passthrough, 
        maxClimbAngle = 80, 
        maxDescendAngle = 80))
    a.addComponent (compo.Dynamics2D(gravity= vars.gravity))
    stateMachine = compo.StateMachine (initialState='idle')
    stateMachine.states.append (compo.SimpleState (id='idle', anim = 'walk'))
    stateMachine.states.append (pc.FoeWalk(id='walk', anim='walk', speed=30, acceleration=0, flipHorizontal=False, flipWhenPlatformEnds=False, left=1))
    a.addComponent (stateMachine)
    return a

def coin(x: float, y: float):
    a = Sprite(model = 'pickupcoin', pos = [x*vars.tileSize, y*vars.tileSize, 1])
    a.addComponent(compo.SmartCollider(
        flag = vars.flags.foe,
        mask = vars.flags.player,
        tag = vars.tags.coin))
    return a

#     fact.warp (x=5, y=2, width=16, height=2, callback = func.warpIn(warpTo=[2, 25], newCamBounds=[0,256,256,512])),

def warp(x : float, y : float, warpTo, newCamBounds):
    e = Entity(pos = [x * vars.tileSize, y * vars.tileSize])
    e.addComponent (compo.Collider (flag = vars.flags.foe, mask = vars.flags.player, tag = vars.tags.warp, 
        shape = sh.Rect (16, 2)))
    e.addComponent (compo.Info (func = func.warpIn(warpTo, newCamBounds)))
    return e
    #     fact.hotspot (x=13, y=18, width=16, height=2, callback = func.warpUp(warpTo=[164, 0],
    #         newCamBounds=[0, 224*vars.tileSize, 0, 16*vars.tileSize])),

def hotspot(x : float, y : float, warpTo, newCamBounds):
    e = Entity(pos = [x * vars.tileSize, y * vars.tileSize])
    e.addComponent (compo.Collider (flag = vars.flags.foe, mask = vars.flags.player, tag = vars.tags.hotspot, 
        shape = sh.Rect (16, 2)))
    e.addComponent (compo.Info (func = func.warpUp(warpTo, newCamBounds)))
    return e

def hotspot2(x : float, y : float, width: float, height: float, f: callable):
    e = Entity(pos = [x * vars.tileSize, y * vars.tileSize])
    e.addComponent (compo.Collider (flag = vars.flags.foe, mask = vars.flags.player, tag = vars.tags.hotspot, 
        shape = sh.Rect (width*vars.tileSize, height*vars.tileSize)))
    e.addComponent (compo.Info (func = f))
    return e


def makeSpawn(x: float, y: float, f: callable, *args):
    print (args)
    e = Entity(pos = [x * vars.tileSize, y * vars.tileSize])
    e.addComponent (compo.Collider (flag = vars.flags.foe, mask = vars.flags.player, tag = vars.tags.hotspot, 
        shape = sh.Rect (1, 100)))
    e.addComponent (compo.Info (func = func.createItem(f, *args)))
    return e




def tiled(x: float, y: float, tileSheet : str, sheetSize, tileData: list, 
    width: int, height:int, size: float, z: float = 0, shape: sh.Shape = None):
    e = Entity(pos = [x*vars.tileSize, y*vars.tileSize, z])
    e.addComponent (compo.TiledGfx(
        tilesheet = tileSheet, 
        sheetSize = sheetSize, 
        tileData = tileData, 
        width = width, 
        height = height,
        size = size))
    if shape:
        e.addComponent (compo.Collider (
            flag=vars.flags.platform,
            mask = 1,
            tag = 1,
            shape = shape
        ))
	#if (args.collide) then
	#	table.insert(components, { type = "collider", flag = variables.collision.flags.platform, mask = 1, tag=1, shape = { type="rect", width = args.width*engine.tilesize, height = 
    #		args.height*engine.tilesize }})
	#end
    return e

def line(x: float, y: float, A, B):
    e = Entity(pos = [x*vars.tileSize, y*vars.tileSize])
    e.addComponent (compo.Collider(flag = vars.flags.platform, mask=1, tag=1, 
        shape= sh.Line(A, B)))
    return e

def spr(model: str, x: float, y: float, z: float = 0.0, tag: str = None):
    a = Sprite(model= model, pos = [x*vars.tileSize, y*vars.tileSize, z], tag = tag)
    return a

