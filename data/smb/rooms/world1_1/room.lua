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
			{ tag = {1, 21}, onenter = bonusBrickResponse }				
		}
	}
},
assets = {
	sprites.mario,
	sprites.basicbrick,
	sprites.bonusbrick,
	sprites.mushroom
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
				luakey = {
					keys = {
						{ key = 299, func = restartRoom }
					}
				}
		    },
			{	
				pos = {startPos[1], startPos[2], 0},
				gfx = { model="mario", anim="idle" },
				controller2d = { maxclimbangle = 80, maxdescendangle = 80, horizontalrays=4, verticalrays=4 },
				dynamics2d = { jumpheight = 64, timetojumpapex = 0.5 },
				collider = { shape = {type="rect", width=14, height=16, offset={-8,0}}, tag = 1, flag= 1},
				statemachine = {
					initialstate = "idle",
					states = {
						{ id = "idle", type ="idle2d", anim="idle", acceleration = marioAcc },
						{ id = "walk", type ="walk2d", anim="walk", acceleration = marioAcc, speed = marioSpeed},
						{ id = "jump", type ="jump2d", anim="jump", acceleration = marioAcc, speed = marioSpeed}
					},

					keys = {
						{ current = "idle", key =  262, next="walk" },
						{ current = "idle", key =  263, next="walk" },
						{ current = "idle", key =  265, next="jump" },
						--{ current = "idle", key =  262, next="duck" },
						{ current = "walk", key =  265, next="jump" }
					},

				},
				follow = { cam ="maincam", relativepos={0,0,5}, up={0,1,0}},
				--				follow = follow,
				--info = args.template.info,
				-- children = {
				-- 	{
				-- 		name ="colliders",
				-- 		children = colliders
				-- 	},
		 	-- 		{
				-- 		name ="shadow",
		 	-- 			gfx = { shape={type="ellipse", semiaxes=args.template.shadowsize }, draw="solid", color={0,0,0,128} },
		 	-- 			shadow = {}
		 	-- 		},

				-- }
			},
			makeLine { A = {0,0}, B = {0,256} },
			makeRect { pos ={0,0,0}, width = 69, height = 2 },
			makeBrick { pos = {5,4}, sprite="basicbrick" },
			makeBrick { pos ={ 4, 5}, sprite="basicbrick"},
			makeBonusBrick { pos = {7,5}, sprite="bonusbrick", hits=1, bonusfactory = ciao }
			-- {
			-- 	pos = {0,0,0},
			-- 	gfx = {shape={type="rect", width = 64, height=32}, color={255,255,255,255} },
			-- 	collider= {shape={type="rect", width = 64, height=32}, tag=10, flag = 2},
			-- }
		--collider= { shape = {type="rect", width=1, height=1}, tag=1, flag=1},
		}
	}
},
}


for i = 1,10 do
    table.insert(room.scene[1].children, { gfx = { shape = { type="line", A={collisionSize*i,0}, B={collisionSize*i, 256}}, color={255, 255, 255, 255} }})
    table.insert(room.scene[1].children, { gfx = { shape = { type="line", A={0, collisionSize*i}, B={320, collisionSize*i}}, color={255, 255, 255, 255} }})
end

-- end room

function room.init()
end

function room.start()

end

function room.afterstartup() 
end



