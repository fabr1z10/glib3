from lib_py.room import Room
from lib_py.entity import Entity, Text, TextAlignment, Sprite
from lib_py.camera import OrthoCamera
from lib_py.runner import CollisionEngine, CollisionResponse, Scheduler, DynamicWorld, KeyListener
from lib_py.components import FPSCounter
import smb_py.funcs as func
import smb_py.factories.items.items1 as build
import smb_py.vars as vars
import lib_py.engine as engine

def f():
    print('toggle pause!')
    func.upgradePlayer()



def checkWarp():
    print ('qui')
    if vars.warp_func:
        vars.warp_func()

#def restart():
##    print ('ciao')
#    example.restart()    


class PlatformerRoom(Room):
    def __init__(self, id:str, width, height, worldWidth: int, worldHeight : int, startPos):
        super().__init__(id, width, height)
        # adding pause button
        self.keyl.addKey(key=32, func = func.togglePause)
        #self.keyl.addKey(key=264, func = checkWarp)
        # restart on F10
        self.keyl.addKey(key=299, func = func.restart)

        main = Entity (tag='main')
        main.camera = OrthoCamera(worldwidth = worldWidth * vars.tileSize, worldheight = worldHeight * vars.tileSize, 
        camwidth=width, camheight=height, viewport=[0, 0, width, height], tag='maincam')
        self.main = main
        self.add(main)

        # create the collision engine (maybe to put into the ctor of the room subclass)
        ce = CollisionEngine(80, 80)
        ce.addResponse(vars.tags.player, vars.tags.brick_sensor, CollisionResponse(onenter=func.brickResponse))
        ce.addResponse(vars.tags.player, vars.tags.bonus_brick_sensor, CollisionResponse(onenter=func.bonusBrickResponse))
        ce.addResponse(vars.tags.player, vars.tags.mushroom, CollisionResponse(onenter=func.mushroomResponse))
        ce.addResponse(vars.tags.player, vars.tags.warp, CollisionResponse(onenter = func.onWarpEnter, onleave= func.onWarpExit))
        ce.addResponse(vars.tags.player, vars.tags.hotspot, CollisionResponse(onenter = func.hotspotEnter))
        ce.addResponse(vars.tags.player, vars.tags.coin, CollisionResponse(onenter = func.coinResponse))
        ce.addResponse(vars.tags.player, vars.tags.goomba, CollisionResponse(onenter = func.goombaResponse))
        ce.addResponse(vars.tags.player, vars.tags.koopa, CollisionResponse(onenter = func.koopaResponse))		
        ce.addResponse (vars.tags.player, vars.tags.spawn, CollisionResponse (onenter = func.onSpawn))
        ce.addResponse (vars.tags.player, vars.tags.key, CollisionResponse (onenter = func.onCollectItem))
        ce.addResponse(vars.tags.goomba, vars.tags.player_fire, CollisionResponse (onenter = func.fireHitsFoe))
        self.addRunner(ce)
        self.addRunner(Scheduler())


        self.dw = DynamicWorld(256, 256, 'maincam')
        self.addRunner(self.dw)

        diag = Entity (tag = 'diag')
        diag.camera = OrthoCamera(worldwidth = width, worldheight = height, 
            camwidth=width, camheight=height, viewport=[0, 0, width, height], tag='diagcam')
        diag.add(Text ('main', 8, engine.getString('mario'), [255, 255, 255, 255], TextAlignment.topleft, pos=[24, 248, 2]))
        diag.add(Text ('main', 8, '{:06d}'.format(vars.score), [255, 255, 255, 255], TextAlignment.topleft, tag='score_label', pos=[24, 240, 2]))
        diag.add(Text ('main', 8, engine.getString('world'), [255, 255, 255, 255], TextAlignment.topleft, pos=[144, 248, 2]))
        diag.add(Text ('main', 8, id, [255, 255, 255, 255], TextAlignment.top, pos=[164, 240, 2]))
        diag.add(Text ('main', 8, engine.getString('time'), [255, 255, 255, 255], TextAlignment.topright, pos=[232, 248, 2]))
        diag.add(Text ('main', 8, str(vars.time), [255, 255, 255, 255], TextAlignment.topright, tag='score_label', pos=[232, 240, 2]))
        diag.add(Sprite (model = 'coin_counter', pos=[96, 232, 2]))
        diag.add(Text ('main', 8, 'x', [255,255,255,255], pos=[108,240,2]))
        diag.add(Text ('main', 8, '{:02d}'.format(vars.coins), [255, 255, 255, 255], TextAlignment.topleft, tag='coin_label', pos=[116, 240, 2]))

        fpsCount = Text ('main', 8, '0', [255,255,255,255], align = TextAlignment.topleft, tag='fps', pos = [0, 256, 2])
        fpsCount.addComponent (FPSCounter())
        diag.add (fpsCount)

        self.add(diag)

	    # scene = {

		# 	[2] = {
		# 		tag = "diag",
		# 		camera = {
		# 			tag = "diagcam",
		# 			type ="ortho",
		# 			pos = {0,0,5},
		# 			size = {args.screen_size[1]*16, args.screen_size[2]*16},
		# 			bounds = {0,0,args.screen_size[1]*16, args.screen_size[2]*16},
		# 			viewport = {0, 0, args.screen_size[1]*16, args.screen_size[2]*16}
		# 		},
		# 		children = {
		# 	 		{
		# 				pos = {24,248,0},
		# 				components = {
		# 					{ type = "text", id="MARIO", font="main", size=8, }
		# 				}
		# 			},
		# 			{
		# 				tag = "score_label",
		# 				pos = {24, 240, 0},
		# 				components = {
		# 					{ type = "text", id=string.format("%06d", variables.score), font="main", size=8, }	
		# 				}
		# 			},
		# 	 		{
		# 				pos = {144,248,0},
		# 				components = {
		# 					{ type = "text", id="WORLD", font="main", size=8, }
		# 				}
		# 			},	
		# 	 		{
		# 				pos = {164,236,0},
		# 				components = {
		# 					{ type = "text", id=variables.world_name, font="main", size=8, align="center" }
		# 				}
		# 			},						
		# 			{
		# 				pos = {232,248,0},
		# 				components = {
		# 					{ type = "text", id="TIME", font="main", size=8, align="topright" }
		# 				}
		# 			},	
		# 			{
		# 				tag = "time_label",
		# 				pos = {232,240,0},
		# 				components = {
		# 					{ type = "text", id=tostring(variables.time), font="main", size=8, align="topright" }
		# 				}
		# 			},				
		# 			{
		# 				pos = {96, 232, 0},
		# 				type="sprite",
		# 				model="coin_counter"
		# 			},
		# 			{
		# 				pos = {108,240,0},
		# 				components = {
		# 					{ type = "text", id="x", font="main", size=8 }
		# 				}
		# 			},	
		# 			{
		# 				tag = "coin_label",
		# 				pos = {116, 240, 0},
		# 				components = {
		# 					{ type = "text", id=string.format("%02d", variables.coins), font="main", size=8, }	
		# 				}
		# 			},
		# 		}
		# 	}
		# },

        # add player
        mario = build.makePlayer(vars.stateInfo[vars.state], startPos[0], startPos[1])
        main.add(mario)

    def addToDynamicWorld(self, e):
        self.dw.items.append(e)
