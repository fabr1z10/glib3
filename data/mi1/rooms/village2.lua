require("template/room1")

local roomInfo = {
	width = 480,
	height = 144,
	startTable = {
		village1 = { pos = items2["village2.archway1"].hotspot.walk_to, facing = "south"},
		--village3 = { pos = items["village2.archway2"].walk_to, facing = "south"},
		--voodoolady = { pos = items["village2.door_voodoolady"].walk_to, facing = "west"},
	},
	defaultroom = "village1",
	depth = { type="linear_y", values= {0, 1, 144, 0} },
	scale = { type="patchwise", rects = {
    		{ pos = {0, 0}, size={480, 40}, type="constant", value = 1},
    		{ pos = {0, 40}, size={480, 104}, type="constant", value = 0.8},    		
    	}
	}
	
}

room = generateBasicRoom (roomInfo)

-- room:add_asset(sprites.citizen)
-- room:add_asset(sprites.lmf1)
-- room:add_asset(sprites.lmf2)
-- room:add_asset(sprites.lmf3)
-- room:add_asset(sprites.rat)
-- room:add_asset(sprites["village2.door_voodoo"])

room:add( {
	{ pos = {0, 0,-3}, components = { { type="gfx", image="gfx/village2.png" }}},
-- 	{
-- 		pos = {0,0,0},
-- 		components = {
--       		{ 
-- 				type ="walkarea",
-- 				priority = 0,
--        			target = "player",
-- 				shape = { 
-- 	                type = "poly", 
-- 	                outline = {0,24, 123,63,199,63,299,30,377,30,385,35,454,35,470,0,0}
-- 	            }
-- 			}
--       	}
-- 	},
--  	factory.object.create { object = "village2.archway1" },
-- 	factory.object.create { object = "village2.archway2" },
-- 	factory.object.create { object = "village2.citizen" },
-- 	factory.object.create { object = "village2.lmf1" },
-- 	factory.object.create { object = "village2.lmf2" },
-- 	factory.object.create { object = "village2.lmf3" },
-- 	factory.object.create { object = "village2.lmf" },
-- 	factory.object.create { object = "village2.rat" },
-- 	factory.object.create { object = "village2.door_voodoolady" },


})


function room.afterstartup() 
	for k, v in ipairs(room.initstuff) do
		v()
	end
end


