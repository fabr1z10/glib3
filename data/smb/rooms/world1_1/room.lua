local collisionSize = 80
local startPos = {32, 64}
local g = -10
local marioAcc = 0.05
local marioSpeed = 75

function mario_mushroom(e1, e2) 
	e2:parent():remove()
	mario = e1:parent()
	info = mario:getinfo()
	info.supermario = true
	mario:resetstate()
end

room = {

engines = {
	{ type = "scheduler"},
	{ 
		type = "collision", 
		size = {collisionSize, collisionSize}, 
		response = {
			{ tag = {1, 20}, onenter = basicBrickResponse },
			{ tag = {1, 21}, onenter = bonusBrickResponse },
			{ tag = {3,4}, onenter = mario_mushroom}				
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
				components = {
					{ type="luakey", keys = { { key = 299, func = restartRoom }}}
				}
		    },
			{	
				pos = {startPos[1], startPos[2], 0},
				components = {
					{ type="gfx", model="mario", anim="idle" },
					{ type="controller2d", maxclimbangle = 80, maxdescendangle = 80, horizontalrays=4, verticalrays=4 },
					{ type="dynamics2d", jumpheight = 64, timetojumpapex = 0.5 },
					{ type="collider", shape = {type="rect", width=14, height=16, offset={-8,0}}, tag = 1, flag= 1 },
					{ type="statemachine", initialstate = "idle",
						states = {
							{ id = "idle", init = { type="luaanim", func = marioinit }, behavior = { type ="idle2d", acceleration = marioAcc }},
							{ id = "walk", init = { type="anim", anim="walk", colliders = {"normal"}}, behavior = { type ="walk2d", acceleration = marioAcc, speed= marioSpeed }},
							{ id = "jump", init = { type="anim", anim="jump", colliders = {"normal"}}, behavior = { type ="jump2d", acceleration = marioAcc, speed= marioSpeed }},
						},
						keys = {
							{ current = "idle", key =  262, next="walk" },
							{ current = "idle", key =  263, next="walk" },
							{ current = "idle", key =  265, next="jump" },
						--{ current = "idle", key =  262, next="duck" },
							{ current = "walk", key =  265, next="jump" }
						}
					},
					{ type="info", supermario = false, fire = false },
					{ type="follow", cam ="maincam", relativepos={0,0,5}, up={0,1,0} }
		 		},
				-- collider boxes
				children = {
					{ 
						components = {
							{ type="collider", shape = {type="rect", width=16, height=16, offset={-8, 0}}, tag=3,flag=1 },
							{ type="gfx", shape= {type="rect", width=16, height=16, offset={-8, 0}}, color={255,0,0,255}}
						}
					}
				}
			},
			makeLine { A = {1,0}, B = {1,256} },
			makeRect { pos ={0,0,0}, width = 69, height = 2 },
			-- makeBrick { pos = {5,4}, sprite="basicbrick" },
			-- makeBrick { pos ={ 4, 5}, sprite="basicbrick"},
			makeBonusBrick { pos = {7,5}, sprite="bonusbrick", hits=1, bonusfactory = ciao }
		}
	}
},
}


-- for i = 1,10 do
--     table.insert(room.scene[1].children, { gfx = { shape = { type="line", A={collisionSize*i,0}, B={collisionSize*i, 256}}, color={255, 255, 255, 255} }})
--     table.insert(room.scene[1].children, { gfx = { shape = { type="line", A={0, collisionSize*i}, B={320, collisionSize*i}}, color={255, 255, 255, 255} }})
-- end

-- end room

function room.init()
end

function room.start()

end

function room.afterstartup() 
end



