local items = engine.items

roomDefinition = {
	width = 320,
	height = 144,
	startTable = {
		forest_5 = { walkarea="forest6.walkarea", pos = items["forest6.5"].hotspot.walk_to, dir = "east"},
		forest_7 = { walkarea="forest6.walkarea", pos = items["forest6.7"].hotspot.walk_to, dir = "south"},
	},
	defaultroom = "forest_5",
	walkareas = { "forest6.walkarea"},
	font_size = 8,
	playerid="guybrush",
	depth = { type="linear_y", values= {0, 1, 144, 0} },
	collide = true,
}

room = scumm.factory.basic_room (roomDefinition)

room:add("main", {
	{ pos = {0, 0,-3}, components = { { type="gfx", image="forest_6.png" }}},
	scumm.factory.object { id = "forest6.5" },
	scumm.factory.object { id = "forest6.7" },
})

table.insert(room.initstuff, glib.curry (mi.addStorekeeper, { 
	pos = {120, 35, 0}, 
	parent="forest6.walkarea", 
	from = "forest_5",
	walkto = { items["forest6.7"].hotspot.walk_to }
}))

