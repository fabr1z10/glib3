local roomInfo = {
	worldWidth = 224,
	worldHeight = 16,
	startPos = {2, 4},
	collisionSize = 80,
	g = -10
}

local initscripts = {}


room =  {

		engines = {
			{ type = "scheduler"},
			{ 
				type = "collision", 
				size = {roomInfo.collisionSize, roomInfo.collisionSize}, 
				response = {}
			}
			-- 		{ tag = {1, 20}, onenter = basicBrickResponse },
			-- 		{ tag = {1, 21}, onenter = bonusBrickResponse },
			-- 		{ tag = {1, mushroomTag}, onenter = mario_mushroom},
			-- 		{ tag = {1, mushroom1upTag}, onenter = mario_mushroom1up},
			-- 		{ tag = {1, goombaTag}, onenter = mario_goomba},
			-- 		{ tag = {1, koopaTag}, onenter = mario_koopa},
			-- 		{ tag = {1, flowerTag}, onenter = mario_flower},
			-- 		{ tag = {1, starTag}, onenter = mario_star},
			-- 		{ tag = {1, invisibleBrickTag}, onenter = mario_invisiblebrick},
			-- 		{ tag = {1, movingPlatformTag}, onenter = character_movingplatform},
			-- 		{ tag = {1, spawnTag}, onenter = mario_spawn},
			-- 		{ tag = {1, warpTag}, onenter = mario_warp_in, onleave = mario_warp_out },
			-- 		{ tag = {1, warpTouch}, onenter = mario_warptouch},
			-- 		{ tag = {1, plantTag}, onenter = mario_plant},
			-- 		{ tag = {1, coinTag}, onenter = mario_coin },
		
						
			-- 	}
			-- }
		},

    	scene = {
			[1] = {
				tag = "main",
				camera = {
					tag = "maincam",
					type="ortho",
					size = {256, 256},
					bounds = {0, 0, roomInfo.worldWidth*16, roomInfo.worldHeight*16},
					viewport = {0, 0, 256, 256}
				},
				children = {
					-- [1] = {
					-- 	components = {
					-- 		{ type="luakey", keys = { 
					-- 			{ key = 299, func = restartRoom }}
					-- 		},
							
					-- 	}
				 --    },
					-- player
					--items.mario.create { pos = Pos{roomInfo.startPos[1], roomInfo.startPos[2]} },
					{	
						tag="player",
						type="sprite",
						model="mario",
						anim="idle",
						pos = {32, 32, 0},
						components = {
							--{ type="gfx", model="mario", anim="idle" },
							{ type="controller2d", maxclimbangle = 80, maxdescendangle = 80, horizontalrays=4, verticalrays=4 },
							-- { type="dynamics2d", jumpheight = 80, timetojumpapex = 0.5 },

							{ type="multicollider", tag=1, flag=1, mask =2, initialshape="small", shapes = {
							 	{ name ="small", type="rect", width=14, height=16, offset={-8,0}},
							 	{ name ="big", type="rect", width=14, height=32, offset={-8,0}},
							 	{ name ="duck", type="rect", width=14, height=24, offset={-8,0}}
							}},
							-- { type="statemachine", initialstate = "idle",
							-- 	states = {
							-- 	 	{ id = "idle", init = { type="luaanim", func = curry21(marioinit, "idle") }, behavior = { type ="idle2d", acceleration = marioAcc }},
							-- 		{ id = "walk", init = { type="luaanim", func = curry21(marioinit, "walk") }, behavior = { type ="walk2d", acceleration = marioAcc, speed= marioSpeed }},
							-- 		{ id = "jump", init = { type="luaanim", func = curry21(marioinit, "jump") }, behavior = { type ="jump2d", acceleration = marioAcc, speed= marioSpeed }},
							-- 		{ id = "duck", init = { type="animcollider", anim= "duck", collider="duck" }, behavior = { type ="idle2d", acceleration = marioAcc, speed= marioSpeed }},
							-- 		{ id = "nophys", init = { type="luaanim", func = curry21(marioinit2, "idle") } }
							-- 	},
							-- 	keys = {
							-- 	 	{ current = "idle", key =  262, next="walk" },
							-- 	 	{ current = "idle", key =  263, next="walk" },
							-- 	 	{ current = "idle", key =  265, next="jump" },
							-- 	 	{ current = "idle", key =  264, func=mario_duck},
							-- 		-- --{ current = "idle", key =  262, next="duck" },
							-- 		{ current = "walk", key =  265, next="jump" },
							-- 		{ current = "walk", key = 264, func=mario_duck},
							-- 		{ current = "duck", key = 264, press=false, next="idle" }
							-- 		-- event key release when duck returning to idle
							-- 	}
							-- },
							-- { type="info", supermario = false, fire = false, invincible = false },
							{ type="follow", cam ="maincam", relativepos={0,0,5}, up={0,1,0} }
						 },
					}					
					-- [3] = {
					-- 	tag = "restofscene",
					-- 	children = {
					-- 		makeLine { A = {1,0}, B = {1, roomInfo.worldHeight} },
					-- 	}		
					-- }
				}
			},
			-- [2] = {
			-- 	tag = "diag",
			-- 	camera = {
			-- 		tag = "diagcam",
			-- 		type ="ortho",
			-- 		size = {256, 256},
			-- 		bounds = {0,0,256, 256},
			-- 		viewport = {0,0,256,256}
			-- 	},
			-- 	children = {
			-- 		{
			-- 			tag = "_fps",
			-- 			pos = {0, 256, 0},
			-- 			components = {
			-- 				{ 
			-- 					type = "text", id = "Ciao", font ="diag"
			-- 				},
			-- 				{
			-- 					type="fps"
			-- 				}
			-- 			}
			-- 		}
			-- 	}
			-- }
		},
	}
--room = getBaseRoom(roomInfo)
-- local mainScene = room.scene[1].children[3].children

-- local coinBricks = { {16, 5}, {23, 5}, {22, 9}, {94,9}, {106,5}, {109,5}, {112,5}, {129,9}, {130,9}, {170,5} }
-- local basicBricks = { {20, 5}, {22, 5}, {24, 5}, {77, 5}, {79,5}, {80,9}, {81,9},{82,9},{83,9},{84,9},{85,9},{86,9},{87,9}, {91,9},{92,9},{93,9}, {100,5}, {118,5}, {121,9}, {122,9}, {123,9},
-- 	{128, 9}, {129, 5}, {130,5}, {131, 9}, {168, 5}, {169, 5}, {171,5} }
-- local mushroomBricks = {{21,5}, {78,5}, {109,9}}
-- local pipe2 = { {28,2}, {163, 2}, {179, 2} }
-- local pipe3 = { {38,2} }
-- local pipe4 = { {46,2}, {57, 2} }
-- local coins = { {4, 25}, {5,25}, {6,25}, {7,25}, {8,25}, {9,25}, {10,25}, {4, 27}, {5,27}, {6,27}, {7,27}, {8,27}, {9,27}, {10,27}, {5,29},
-- {6,29}, {7,29}, {8,29}, {9,29}}

-- local sceneItems = {
-- 	makeRect { pos = Pos{0,0}, width = 69, height = 2, gfx="block1" },
-- 	makeRect { pos = Pos{71,0}, width = 15, height = 2, gfx="block1" },
-- 	makeRect { pos = Pos{89,0}, width = 64, height = 2, gfx="block1" },
-- 	makeRect { pos = Pos{155,0}, width = 69, height = 2, gfx="block1" },
-- 	makeRect { pos = Pos{134, 2}, width = 4, height = 1, gfx="block2" },
-- 	makeRect { pos = Pos{135, 3}, width = 3, height = 1, gfx="block2" },
-- 	makeRect { pos = Pos{136, 4}, width = 2, height = 1, gfx="block2" },
-- 	makeRect { pos = Pos{137, 5}, width = 1, height = 1, gfx="block2" },
-- 	makeRect { pos = Pos{140, 2}, width = 4, height = 1, gfx="block2" },
-- 	makeRect { pos = Pos{140, 3}, width = 3, height = 1, gfx="block2" },
-- 	makeRect { pos = Pos{140, 4}, width = 2, height = 1, gfx="block2" },
-- 	makeRect { pos = Pos{140, 5}, width = 1, height = 1, gfx="block2" },
-- 	makeRect { pos = Pos{148, 2}, width = 5, height = 1, gfx="block2" },
-- 	makeRect { pos = Pos{149, 3}, width = 4, height = 1, gfx="block2" },
-- 	makeRect { pos = Pos{150, 4}, width = 3, height = 1, gfx="block2" },
-- 	makeRect { pos = Pos{151, 5}, width = 2, height = 1, gfx="block2" },
-- 	makeRect { pos = Pos{155, 2}, width = 4, height = 1, gfx="block2" },
-- 	makeRect { pos = Pos{155, 3}, width = 3, height = 1, gfx="block2" },
-- 	makeRect { pos = Pos{155, 4}, width = 2, height = 1, gfx="block2" },
-- 	makeRect { pos = Pos{155, 5}, width = 1, height = 1, gfx="block2" },
-- 	makeRect { pos = Pos{181, 2}, width = 9, height = 1, gfx="block2" },
-- 	makeRect { pos = Pos{182, 3}, width = 8, height = 1, gfx="block2" },
-- 	makeRect { pos = Pos{183, 4}, width = 7, height = 1, gfx="block2" },
-- 	makeRect { pos = Pos{184, 5}, width = 6, height = 1, gfx="block2" },
-- 	makeRect { pos = Pos{185, 6}, width = 5, height = 1, gfx="block2" },
-- 	makeRect { pos = Pos{186, 7}, width = 4, height = 1, gfx="block2" },
-- 	makeRect { pos = Pos{187, 8}, width = 3, height = 1, gfx="block2" },
-- 	makeRect { pos = Pos{188, 9}, width = 2, height = 1, gfx="block2" },
-- 	makeRect { pos = Pos{198, 2}, width = 1, height = 1, gfx="block2" },

-- 	makeRect { pos = Pos{0, 20}, width = 16, height = 2, gfx="block4"},
-- 	makeRect { pos = Pos{0, 22}, width = 1, height = 11, gfx="brick2"},
-- 	makeRect { pos = Pos{4, 22}, width = 7, height = 3, gfx="brick2"},
-- 	makeRect { pos = Pos{4, 32}, width = 7, height = 1, gfx="brick2"},
-- 	makeRect { pos = Pos{13, 22}, z=0.5, width = 3, height = 2, tiledata = {2,5,3,5,4,5,2,4,3,4,4,4}},
-- 	makeRect { pos = Pos{15, 24}, width = 1, height = 9, gfx="block3"},
-- 	items.spawn.create { pos = Pos{5,0}, func = items.goomba.create, args = { pos =Pos{10,4}, dir = -1} },		
-- 	items.warp.create { pos = Pos{58, 6}, width = 8, height = 2, ctag =warpTag, func = curry(pipeDown, 
-- 		{x = 2, y = 36, xmin=0, xmax=256, ymin=20*16, ymax= 20*16+256}) },							
-- 	items.warp.create { pos = Pos{12.5, 22}, width = 8, height = 1, ctag = warpTouch, func = curry(pipeRight, 
-- 		{x = 164, y = 2, xmin=0, xmax=roomInfo.worldWidth*16, ymin=0, ymax= roomInfo.worldHeight*16}) },
-- 	items.invisiblebrick.create { pos = Pos{64, 6}, sprite="invbrick", hits=1, item="mushroom1up" },
-- 	items.bonusbrick.create { pos = Pos{94,5}, sprite="basicbrick", hits=5, item = "brickcoin" },
-- 	items.bonusbrick.create { pos = Pos{101, 5}, sprite="bonusbrick", hits=1, item = "star" },			
-- 	items.backgroundelement.create { pos = Pos{198,3}, z=-1, width=1, height=9, tiledata ={3,2,3,2,3,2,3,2,3,2,3,2,3,2,3,2,3,2}},
-- 	items.backgroundelement.create { pos = Pos{198,12}, z=-1, width=1, height=1, tiledata ={4,2}},
-- 	items.backgroundelement.create { pos = Pos{197.5,11}, tag="flag", z=-0.5, width=1, height=1, tiledata ={14,4}},		
-- 	items.warp.create { pos = Pos{198.5, 2}, tag="goal", width = 1, height = 15*16, ctag = warpTouch, func = curry(mario_end_level, {x=198, y = 48, deltayflag = -8*16, goal="goal"}) },
-- 	items.warp.create { pos = Pos{205, 2}, width = 1, height = 15*16, ctag = warpTouch, func = mario_complete },
-- }

-- for k, v in ipairs(sceneItems) do
-- 	table.insert(mainScene, v)
-- end
-- for k, v in ipairs(basicBricks) do
-- 	table.insert(mainScene, items.brick.create{ pos=Pos(v), sprite="basicbrick" })
-- end
-- for k, v in ipairs(coinBricks) do
-- 	table.insert(mainScene, items.bonusbrick.create { pos = Pos(v), sprite="bonusbrick", hits=1, item = "brickcoin" })
-- end
-- for k, v in ipairs(mushroomBricks) do
-- 	table.insert(mainScene, items.bonusbrick.create { pos = Pos(v), sprite="bonusbrick", hits=1, item = "flower" })
-- end
-- -- pipes
-- for k, v in ipairs(pipe2) do table.insert(mainScene, makeRect { pos = Pos(v), z = 0.5, width = 2, height = 2, tiledata = {0,4,1,4,0,3,1,3}}) end	
-- for k, v in ipairs(pipe3) do table.insert(mainScene, makeRect { pos = Pos(v), z = 0.5, width = 2, height = 3, tiledata = {0,4,1,4,0,4,1,4,0,3,1,3}}) end	
-- for k, v in ipairs(pipe4) do table.insert(mainScene, makeRect { pos = Pos(v), z = 0.5, width = 2, height = 4, tiledata = {0,4,1,4,0,4,1,4,0,4,1,4,0,3,1,3}}) end	
-- for k, v in ipairs(coins) do
-- 	table.insert(mainScene, items.coin.create { pos = Pos(v) })
-- end

-- function room.init()
-- end

-- function room.start()

-- end

-- function room.afterstartup() 
-- 	for k, v in pairs(initscripts) do
-- 		monkey.play(v)
-- 	end		
-- end



