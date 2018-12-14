require("template/room1")

local roomInfo = {
	width = 480,
	height = 144,
	startTable = {
		village1 = { pos = items["village2.archway1"].walk_to, facing = "south"},
	},
	defaultroom = "village1",
	depth = { type="linear_y", values= {0, 1, 144, 0} },
	scale = { type="linear_y", values= {0, 0.8, 144, 0.2}}
}

room = generateBasicRoom (roomInfo)

room:add_asset(sprites.citizen)

room:add( {
	{ pos = {0, 0,-3}, components = { { type="gfx", image="gfx/village2.png" }}},
	{
		pos = {0,0,0},
		components = {
      		{ 
				type ="walkarea",
				priority = 0,
       			target = "player",
				shape = { 
	                type = "poly", 
	                outline = {0,24, 123,63,199,63,299,30,377,30,385,35,454,35,470,0,0}
	            }
			}
      	}
	},
 	factory.object.create { object = "village2.archway1" },
	factory.object.create { object = "village2.citizen" },
-- 	factory.object.create { object = "village1.poster" },
-- 	factory.object.create { object = "village1.archway" },
})


function room.afterstartup() 
	for k, v in ipairs(room.initstuff) do
		v()
	end
end


