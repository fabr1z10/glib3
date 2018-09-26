--require("rooms/001/actions")

local dt=0.1
local d = {
	depth = { 
	    type = "linear_y", values = {0, 1, 400, 0}
	}
}

local startPositionTable = {
	['start'] = {212, 77}
}
local function ciao(x)
	print("pollo")
	x:setcolor(255,0,0,255)
	pp =  x:parent()
 	info = x:getinfo()
 	print ("pos = (" .. tostring(pp.x) .. ", " .. tostring(pp.y) .. ")")
 	print ("hitting = " .. info.pos)
 -- 	local s = script:new("_cook")
	-- s.actions = {
	-- 	[1] = { type = "callfunc", func = curry (createObject, { 
	-- 		pos = {100, 100, 0},
	-- 		gfx = { model = "piece1", anim = "default" },
	-- 		depth = d,
	-- 		tag="p1"
	-- 	})},
	-- 	[2] = {
	-- 		type="movegravity",
	-- 		actor="p1",
	-- 		velocity={50,20},
	-- 		g =20,
	-- 		ystop = x.y,
	-- 		after={1}
	-- 	}
	-- }
	-- monkey.play(s)
end

local startPosition = startPositionTable[variables._previousroom]

room = {
engines = {
	{ type = "scheduler"},
	{ type = "collision", size = {80, 80} }
},
assets = {
	sprites.player,
	sprites.character_1,
	sprites.piece1

},
scene = {
	{
		tag = "main",
		camera = {
			tag = "maincam",
			type="ortho",
			size = {640, 400},
			bounds = {0, 0, 1280, 400},
			viewport = {0, 0, 640, 400}
		},
		children = {
			{
				gfx = { model="character_1", anim="idle"},	
				pos = {60, 30, 0},
				depth = d,
				children = {
					{
						pos={0,50,1},
				 		gfx = {
				 			shape= {type="rect", width=10, height=10},
				 			color={255,255,255,255}
				 		},
					collider = {
						shape= {type="rect", width=10, height=10}, 
						tag=1, 
						flag=2
					},
					info = {
						pos = "head"
					}
				}
					
				}
				-- children = {
				-- 	-- head collider
				-- 	{
				-- 		pos = {0, 50, 0},
				-- 		collider = {
				-- 			shape= {type="rect", width=10, height=10}, 
				-- 			tag=1, 
				-- 			flag=2
				-- 		},

				-- 	}					
				-- }
			},
			{		
				pos={0,50,1},
				gfx = {
					shape= {type="rect", width=10, height=10},
					color={255,255,255,255}
				}
			},
			{
				gfx = { model="player", anim="idle"},
				collider= {shape={type="rect", width=1, height=1}, tag=1, flag=1},
				pos = {30,30,0},
				depth = d,
				statemachine = {
					initialstate = "walk",
					states = {
						{ 
							id = "walk", 
							type="walkcollision", 
							speed = 1, width=5, height=1, 
							horizontal_rays=1, vertical_rays=2,
							anims = {
								{ id = "walk_right", anim = "walk" },
								{ id = "walk_front", anim = "walk" },
								{ id = "walk_back", anim = "walk" },
								{ id = "idle_right", anim = "idle" },
								{ id = "idle_front", anim = "idle"},
								{ id = "idle_back", anim = "idle"}
							}
						},
						{	
							id = "punch",
							type ="hit",
							anim = "punch",
							frame = 2,
							mask = 2,
							shape = { type = "rect", width = 10, height = 10 },
							offset = {32, 52},
							func = ciao
						},
						{	
							id = "kick",
							type ="hit",
							anim = "kick"
						},
					},
					keys = {
						{ key = 65, current = "walk", next= "punch"},
						{ key = 83, current = "walk", next= "kick"}

					}
				
				}
			},
			{
				pos = {50, 50, 0},
				gfx = { image="gfx/tree1.png" },
				depth = d,
			},
			{
				-- a collider object
				pos = {100,50,0},
				depth =d,
				collider = {
					shape= {type="rect", width=10, height=51}, 
					tag=1, 
					flag=2
				},
				gfx = {
					shape= {type="rect", width=10, height=51},
					color={255,255,255,255}
				}
			}
		}
	}
}
}

for i = 1,10 do
    table.insert(room.scene[1].children, { gfx = { shape = { type="line", A={40*i,0}, B={40*i, 200}}, color={255, 255, 255, 255} }})
    table.insert(room.scene[1].children, { gfx = { shape = { type="line", A={0, 40*i}, B={320, 40*i}}, color={255, 255, 255, 255} }})
end

-- end room

function room.init()
end

function room.start()

end



function room.afterstartup() 

end



