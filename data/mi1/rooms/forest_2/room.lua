local items = engine.items

roomDefinition = {
	width = 320,
	height = 144,
	startTable = {
		forest_1 = { walkarea="forest2.walkarea", pos = items["forest2.1"].hotspot.walk_to, dir = "west"},
		forest_3 = { walkarea="forest2.walkarea", pos = items["forest2.3"].hotspot.walk_to, dir = "south"},
		forest_9 = { walkarea="forest2.walkarea", pos = items["forest2.9"].hotspot.walk_to, dir = "east"},

	},
	defaultroom = "forest_1",
	walkareas = { "forest2.walkarea"},
	font_size = 8,
	playerid="guybrush",
	collide=true
}

room = scumm.factory.basic_room (roomDefinition)

room:add ( "main",
	{ 
		{ pos = {0, 0,-3}, components = { { type="gfx", image="forest_2.png" }}},
		{ pos = {122, 21, 1}, components = { { type="gfx", image="forest_2a.png" }}},        
		{ pos = {247, 0, 1}, components = { { type="gfx", image="forestyp.png" }}},        
		scumm.factory.object { id = "forest2.1" },
		scumm.factory.object { id = "forest2.3" },
		--scumm.factory.object { id = "forest2.9" },
		scumm.factory.object { id = "forest.yellowplant" },

	}
)

table.insert(room.initstuff, glib.curry (mi.addStorekeeper, { 
	pos = {240, 35, 0}, 
	parent="forest2.walkarea", 
	from = "forest_1",
	walkto = { items["forest2.3"].hotspot.walk_to }
}))
