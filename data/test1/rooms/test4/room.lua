--require("rooms/001/actions")

local dt=0.1
local d = {
	depth = { 
	    { rect = {0, 316, 0, 166}, dir = "y", bounds = {1, 0} } 
	}
}

local startPositionTable = {
	['start'] = {212, 77}
}

local startPosition = startPositionTable[variables._previousroom]

room = {
engines = {
	{ type = "scheduler"},
	{ type = "collision", size = {80, 80} }
},
assets = {
	sprites.player,

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
				gfx = { model="player", anim="idle"},
				collider= {shape={type="rect", width=1, height=1}, tag=1, flag=1},
				pos = {30,30,0},
				depth = depth,
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
							anim = "punch"
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



