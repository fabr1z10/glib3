roomDefinition = {
	width = 320,
	height = 144,
	startTable = {
		forest_5 = { pos = items["forest8.5"].hotspot.walk_to, dir = "south"},
		forest_19 = { pos = items["forest8.19"].hotspot.walk_to, dir = "east"},
		forest_9 = { pos = items["forest8.9"].hotspot.walk_to, dir = "west"},
	},
	defaultroom = "forest_4",
	depth = { type="linear_y", values= {0, 1, 144, 0} },
}

room = scumm.factory.basic_room (roomDefinition)

room:add( {
	{ pos = {0, 0,-3}, components = { { type="gfx", image="gfx/forest_8.png" }}},
	--{ pos = {122, 21,1}, components = { { type="gfx", image="gfx/forest_2a.png" }}},
	scumm.factory.walkarea { shape = { 
		type = "graph", 
		vertices = { {0, 24}, {134,24}, {320, 24}, {134, 69}}, 
		edges = { {0,1}, {1,2}, {1,3} }
	}},
	scumm.factory.object { id = "forest8.5" },
	scumm.factory.object { id = "forest8.19" },
	scumm.factory.object { id = "forest8.9" },


})


