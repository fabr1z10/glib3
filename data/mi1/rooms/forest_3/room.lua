local items = engine.items

roomDefinition = {
	width = 320,
	height = 144,
	startTable = {
		forest_2 = { walkarea="forest3.walkarea", pos = items["forest3.2"].hotspot.walk_to, dir = "south"},
		forest_4 = { walkarea="forest3.walkarea", pos = items["forest3.4"].hotspot.walk_to, dir = "west"},
	},
	defaultroom = "forest2",
	walkareas = { "forest3.walkarea"},
	font_size = 8,
	playerid="guybrush",
	depth = { type="linear_y", values= {0, 1, 144, 0} },
	collide = true,

}

room = scumm.factory.basic_room (roomDefinition)

room:add("main", {
	{ pos = {0, 0,-3}, components = { { type="gfx", image="forest_3.png" }}},
	scumm.factory.object { id = "forest3.2" },
	scumm.factory.object { id = "forest3.4" },
})


table.insert(room.initstuff, glib.curry (mi.addStorekeeper, { 
	pos = {200, 35, 0}, 
	parent="forest3.walkarea", 
	from = "forest_2",
	walkto = { items["forest3.4"].hotspot.walk_to }
}))