roomDefinition = {
	width = 320,
	height = 144,
	startTable = {
		forest_10 = { pos = items["forest9.10"].hotspot.walk_to, dir = "south"},
		forest_2 = { pos = items["forest9.2"].hotspot.walk_to, dir = "east"},
		forest_8 = { pos = items["forest9.8"].hotspot.walk_to, dir = "west"},
	},
	defaultroom = "forest_8",
	depth = { type="linear_y", values= {0, 1, 144, 0} },
}

room = scumm.factory.basic_room (roomDefinition)

room:add( {
	{ pos = {0, 0,-3}, components = { { type="gfx", image="gfx/forest_9.png" }}},
	--{ pos = {122, 21,1}, components = { { type="gfx", image="gfx/forest_2a.png" }}},
	scumm.factory.walkarea { shape = { 
		type = "graph", 
		vertices = { {0, 24}, {80,24}, {125, 35}, {154, 35}, {320, 35}, {154,69}}, 
		edges = { {0,1}, {1,2}, {2,3},{3,4},{3,5} }
	}},
	scumm.factory.object { id = "forest9.10" },
	scumm.factory.object { id = "forest9.2" },
	scumm.factory.object { id = "forest9.8" },


})


