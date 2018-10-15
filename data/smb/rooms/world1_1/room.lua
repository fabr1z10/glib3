local collisionSize = 80
local startPos = {32, 64}
local g = -10
local marioAcc = 0.05
local marioSpeed = 75



room = {

engines = {
	{ type = "scheduler"},
	{ 
		type = "collision", 
		size = {collisionSize, collisionSize}, 
		response = {
			{ tag = {1, 20}, onenter = basicBrickResponse },
			{ tag = {1, 21}, onenter = bonusBrickResponse },
			{ tag = {1, mushroomTag}, onenter = mario_mushroom},
			{ tag = {1, goombaTag}, onenter = mario_goomba},
			{ tag = {1, koopaTag}, onenter = mario_koopa},
				
		}
	}
},
assets = {
	sprites.mario,
	sprites.basicbrick,
	sprites.bonusbrick,
	sprites.mushroom,
	sprites.goomba,
	sprites.koopa
},
scene = {
	{
		tag = "main",
		camera = {
			tag = "maincam",
			type="ortho",
			size = {256, 256},
			bounds = {0, 0, 512, 256},
			viewport = {0, 0, 256, 256}
		},
		children = {
			{
				components = {
					{ type="luakey", keys = { { key = 299, func = restartRoom }}}
				}
		    },
			-- player
			{	
				tag="player",
				pos = {startPos[1], startPos[2], 0},
				components = {
					{ type="gfx", model="mario", anim="idle" },
					{ type="controller2d", maxclimbangle = 80, maxdescendangle = 80, horizontalrays=4, verticalrays=4 },
					{ type="dynamics2d", jumpheight = 64, timetojumpapex = 0.5 },
					{ type="multicollider", tag=1, flag=1, initialshape="small", shapes = {
						{ name ="small", type="rect", width=14, height=16, offset={-8,0}},
						{ name ="big", type="rect", width=14, height=32, offset={-8,0}},
						{ name ="duck", type="rect", width=14, height=24, offset={-8,0}}
					}},
					{ type="statemachine", initialstate = "idle",
						states = {
						 	{ id = "idle", init = { type="luaanim", func = curry21(marioinit, "idle") }, behavior = { type ="idle2d", acceleration = marioAcc }},
							{ id = "walk", init = { type="luaanim", func = curry21(marioinit, "walk") }, behavior = { type ="walk2d", acceleration = marioAcc, speed= marioSpeed }},
							{ id = "jump", init = { type="luaanim", func = curry21(marioinit, "jump") }, behavior = { type ="jump2d", acceleration = marioAcc, speed= marioSpeed }},
							{ id = "duck", init = { type="animcollider", anim= "duck", collider="duck" }, behavior = { type ="idle2d", acceleration = marioAcc, speed= marioSpeed }},
						},
						keys = {
						 	{ current = "idle", key =  262, next="walk" },
						 	{ current = "idle", key =  263, next="walk" },
						 	{ current = "idle", key =  265, next="jump" },
						 	{ current = "idle", key =  264, func=mario_duck},
						-- --{ current = "idle", key =  262, next="duck" },
						 	{ current = "walk", key =  265, next="jump" },
						 	{ current = "walk", key = 264, func=mario_duck},
						 	{ current = "duck", key = 264, press=false, next="idle" }
							-- event key release when duck returning to idle

						}
					},
					{ type="info", supermario = false, fire = false, invincible = true },
					{ type="follow", cam ="maincam", relativepos={0,0,5}, up={0,1,0} }
		 		},
				-- collider boxes
				-- children = {
				-- 	{ 
				-- 		name="small",
				-- 		components = {
				-- 			{ type="collider", shape = {type="rect", width=16, height=16, offset={-8, 0}}, tag=3,flag=1 },
				-- 			{ type="gfx", shape= {type="rect", width=16, height=16, offset={-8, 0}}, color={255,0,0,255}}
				-- 		}
				-- 	},
				-- 	{ 
				-- 		name="big",
				-- 		components = {
				-- 			{ type="collider", shape = {type="rect", width=16, height=32, offset={-8, 0}}, tag=3,flag=1 },
				-- 			{ type="gfx", shape= {type="rect", width=16, height=32, offset={-8, 0}}, color={255,0,0,255}}
				-- 		}
				-- 	},
				-- }
			},
			{
				tag = "restofscene",
				children = {
					makeLine { A = {1,0}, B = {1,256} },
					makeRect { pos ={0,0,0}, width = 69, height = 2, gfx="block1" },
					makeRect { pos ={8,2,0}, width = 1, height = 1, gfx="block2" },
					makeRect { pos ={12,2,0}, width = 1, height = 1, gfx="block2" },
					makeRect { pos ={16,2,0}, width = 1, height = 1, gfx="block2" },
					items.brick.create { pos = {6,5}, sprite="basicbrick" },
					-- -- makeBrick { pos ={ 4, 5}, sprite="basicbrick"},
					items.bonusbrick.create { pos = {7,5}, sprite="bonusbrick", hits=1, item = "mushroom" },					
					items.goomba.create { x = 16*10, y = 16*3, z = 0, dir = -1},
					items.koopa.create { x = 16*14, y = 16*3, z = 0, dir = -1}
				}		
			}
		}
	}
},
}


for i = 1,10 do
	print ("pollo")
     table.insert(room.scene[1].children, { components = 
     	{
     		{ type="gfx", shape = { type="line", A={collisionSize*i,0}, B={collisionSize*i, 256}}, color={255, 255, 255, 255}}
     	}})
     table.insert(room.scene[1].children, { components =
     	{
     		{ type="gfx", shape = { type="line", A={0, collisionSize*i}, B={320, collisionSize*i}}, color={255, 255, 255, 255}}
     	}})
end

-- end room

function room.init()
end

function room.start()

end

function room.afterstartup() 
end



