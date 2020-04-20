import smb_py.builder as b
import smb_py.tiles as tiles
import lib_py.shape as sh
import smb_py.vars as vars
import smb_py.funcs as func


def platform (img : str):
    def f(x: float, y: float, width: int, height: int):
        print ('img = ' + img)
        return b.makePlatform(img, x, y, width, height)
    return f

def brick(model: str):
    def f(x: float, y: float):
        return b.makeBrick(model, x, y)
    return f

def mushroomBrick ():
    def f(x: float, y: float):
        return b.bonusBrick (model = 'bonusbrick', x = x, y= y, callback = b.m1)
    return f

def coinBrick ():
    def f(x: float, y: float):
        return b.bonusBrick (model = 'bonusbrick', x = x, y= y, callback = b.m2)
    return f

def tileMap (template: str):
    def f(x: float, y: float, z: float = 0):
        shape = None
        tm = getattr(tiles, template)
        width = tm[0]
        height = tm[1]
        collision = tm[2]
        data = tm[3]
        if collision:
            shape = sh.Rect(width = width * vars.tileSize, height = height * vars.tileSize) 
        return b.tiled (x, y, z = z, size=vars.tileSize, tileSheet='gfx/smb1.png',
            sheetSize = [16, 16], tileData = data, width = width, height = height, 
            shape = shape) 
    return f        


def warp():
    def f(x : float, y : float, warpTo, newCamBounds):
        return b.warp(x, y, warpTo, newCamBounds)
    return f

def hotspot():
    def f(x : float, y : float, warpTo, newCamBounds):
        return b.hotspot(x, y, warpTo, newCamBounds)
    return f
    #     fact.hotspot (x=13, y=18, width=16, height=2, callback = func.warpUp(warpTo=[164, 0],
    #         newCamBounds=[0, 224*vars.tileSize, 0, 16*vars.tileSize])),

def spawn(factory: callable):
    def f(x : float, y : float, *args):
        print (args)
        f = globals()[factory]()
        return b.makeSpawn(x, y, f, *args)
    return f


def coin():
    def f(x: float, y: float):
        return b.coin(x, y)
    return f

def goomba():
    def f(x: float, y: float):
        return b.makeGoomba('goomba', x, y)
    return f

def koopa():
    def f(x: float, y: float):
        return b.makeKoopa('koopa', x, y)
    return f



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



