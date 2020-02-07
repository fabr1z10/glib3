local items = engine.items

roomDefinition = {
	width = 320,
	height = 144,
	startTable = {
		forest_4 = { walkarea="forest5.walkarea", pos = items["forest5.4"].hotspot.walk_to, dir = "south"},
		forest_6 = { walkarea="forest5.walkarea", pos = items["forest5.6"].hotspot.walk_to, dir = "east"},
	},
	defaultroom = "forest_4",
	walkareas = { "forest5.walkarea"},
	font_size = 8,
	playerid="guybrush",
	depth = { type="linear_y", values= {0, 1, 144, 0} },
	collide = true,
}

room = scumm.factory.basic_room (roomDefinition)

room:add("main", {
	{ pos = {0, 0,-3}, components = { { type="gfx", image="forest_5.png" }}},
	scumm.factory.object { id = "forest5.4" },
	scumm.factory.object { id = "forest5.6" },
	--scumm.factory.object { id = "forest5.8" },
})


table.insert(room.initstuff, glib.curry (mi.addStorekeeper, { 
	pos = {50, 24, 0}, 
	parent="forest5.walkarea", 
	from = "forest_4",
	walkto = { items["forest5.6"].hotspot.walk_to }
}))
