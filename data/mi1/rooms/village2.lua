roomDefinition = {
	width = 480,
	height = 144,
	startTable = {
		village1 = { pos = items["village2.archway_to_village1"].hotspot.walk_to, dir = "south"},
		village3 = { pos = items["village2.archway_to_village3"].hotspot.walk_to, dir = "south"},
		--voodoolady = { pos = items["village2.door_voodoolady"].walk_to, facing = "west"},
	},
	defaultroom = "village1",
	depth = { type="linear_y", values= {0, 1, 144, 0} },
	scale = { type="patchwise", rects = {
    		{ pos = {0, 0}, size={480, 30}, type="constant", value = 1},
    		{ pos = {0, 30}, size={480, 104}, type="linear_y", values = {30, 1, 59, 0.35}},    		
    	}
	}	
}

room = scumm.factory.basic_room (roomDefinition)

room:add( {
	{ pos = {0, 0,-3}, components = { { type="gfx", image="gfx/village2.png" }}},
	scumm.factory.walkarea { shape = { type = "poly", outline = {0, 24, 123, 63, 199, 63, 299, 30, 377, 30, 385, 35, 454, 35, 470, 0, 0}}},
	scumm.factory.object { id="village2.archway_to_village1" },
	scumm.factory.object { id="village2.archway_to_village3" },

    scumm.factory.object { id="village2.citizen" },
	scumm.factory.object { id="village2.lmf1"},
	scumm.factory.object { id="village2.lmf2"},
	scumm.factory.object { id="village2.lmf3"},
	scumm.factory.object { id="village2.lmf"},
	scumm.factory.object { id="village2.rat"},
	-- factory.objc { id="village2.voodoolady_door"},
	-- factory.objc { id="village2.fakedoor1"},
	-- factory.objc { id="village2.fakedoor2"},

-- 	factory.object.create { object = "village2.archway1" },
-- 	factory.object.create { object = "village2.archway2" },
-- 	factory.object.create { object = "village2.lmf1" },
-- 	factory.object.create { object = "village2.lmf2" },
-- 	factory.object.create { object = "village2.lmf3" },
-- 	factory.object.create { object = "village2.lmf" },
-- 	factory.object.create { object = "village2.rat" },
-- 	factory.object.create { object = "village2.door_voodoolady" },


})

table.insert(room.initstuff, glib.curry (mi.addStorekeeper, { pos = {150, 35, 0}, walkto = { {150, 10}, {350, 10}, items["village2.archway_to_village1"].hotspot.walk_to }}))


-- function room.afterstartup() 
-- 	for k, v in ipairs(room.initstuff) do
-- 		v()
-- 	end
-- end


