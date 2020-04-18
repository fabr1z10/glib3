from lib_py.entity import Entity, Sprite
import lib_py.components as compo
import lib_py.shape as sh
import smb_py.funcs as func
from lib_py.script import Script
import smb_py.vars as vars
import lib_py.platformer.components as pc
import lib_py.actions as act
import example

def makePlatform(img : str, x:float, y:float, width : int, height: int):
    a = Entity()
    a.addComponent (compo.Gfx(image = img, repeat = [width, height]))
    a.addComponent (compo.Collider(flag = vars.flags.platform, mask = vars.flags.player, tag = 1, 
        shape = sh.Rect(width = width * vars.tileSize, height = height * vars.tileSize)))
    a.pos = [x * vars.tileSize, y * vars.tileSize]
    return a

def makeBrick(model: str, x: float, y: float):
    a = Sprite(model = model)
    a.addComponent (compo.Collider (flag = vars.flags.platform, mask = 0, tag = 0, 
        shape = sh.Rect(width=vars.tileSize, height=vars.tileSize)))
    a.pos = [x * vars.tileSize, y * vars.tileSize]
    
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

def spr(model: str, x: float, y: float):
    a = Sprite(model= model, pos = [x*vars.tileSize, y*vars.tileSize])
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
	# local s = { type = "rect", width = engine.tilesize, height = engine.tilesize }
	# local s1 = { type = "rect", width = engine.tilesize-4, height = 1.0}
	# --local b = nextTag()
	# local y = arg.pos[2]*engine.tilesize
	# return {
	# 	--tag = b,
	# 	type = "sprite",
	# 	model = arg.sprite,
	# 	pos = {arg.pos[1]*engine.tilesize, y, 0},
	# 	components = {			
	# 		--{ type="gfx", model=arg.sprite, anim="idle", width = engine.tilesize, height = engine.tilesize},	
	# 		{ type="collider", shape=s, tag=10, flag = variables.collision.flags.platform, mask = 0},
	# 		{ type="info", y = y, hitsleft = hitsleft, factory = arg.factory, args = arg.args },
	# 	},
	# 	children = {
	# 		{
	# 			pos = { 2, -0.5, 0},
	# 			components = {
	# 				{ 
	# 					-- sensor for head-butt
	# 					type="collider", 
	# 					shape = s1, 
	# 					tag = variables.collision.tags.bonus_brick_sensor, 
	# 					flag = variables.collision.flags.foe, 
	# 					mask = variables.collision.flags.player 
	# 				},
	# 				{ type="gfx", shape = s1, color = {255,0,0,255}}
	# 			}
	# 		}
	# 	}
	# }
