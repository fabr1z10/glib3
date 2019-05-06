local items = engine.items

roomDefinition = {
	width = 480,
	height = 144,
	startTable = {
		village1 = { walkarea = "village2.walkarea", pos = items["village2.archway_to_village1"].hotspot.walk_to, dir = "south"},
		village3 = { walkarea = "village2.walkarea", pos = items["village2.archway_to_village3"].hotspot.walk_to, dir = "south"},
		--voodoolady = { pos = items["village2.door_voodoolady"].walk_to, facing = "west"},
	},
	font_size = 8,
	defaultroom = "village1",
	walkareas = { "village2.walkarea"},

}

room = scumm.factory.basic_room (roomDefinition)

room:add ( "main",
	{ 
		{ pos = {0, 0,-3}, components = { { type="gfx", image="village2.png" }}},
		scumm.factory.object { id="village2.archway_to_village1" },
		scumm.factory.object { id="village2.archway_to_village3" },
		scumm.factory.object { id="village1.archway" },
		scumm.factory.object { id="village1.door" },
	}
)

room:add ( "village2.walkarea",
	{ 
	    scumm.factory.object { id="village2.citizen" },
		scumm.factory.object { id="village2.lmf1"},
		scumm.factory.object { id="village2.lmf2"},
		scumm.factory.object { id="village2.lmf3"},
		scumm.factory.object { id="village2.lmf"},
		scumm.factory.object { id="village2.rat"},

	}
)


--table.insert(room.initstuff, glib.curry (mi.addStorekeeper, { pos = {150, 35, 0}, walkto = { {150, 10}, {350, 10}, items["village2.archway_to_village1"].hotspot.walk_to }}))


-- function room.afterstartup() 
-- 	for k, v in ipairs(room.initstuff) do
-- 		v()
-- 	end
-- end

