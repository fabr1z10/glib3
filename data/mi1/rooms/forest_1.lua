roomDefinition = {
	width = 320,
	height = 144,
	startTable = {
		meleemap = { pos = items["forest1.1"].hotspot.walk_to, dir = "west"},
		forest_2 = { pos = items["forest1.2"].hotspot.walk_to, dir = "south"},

	},
	defaultroom = "meleemap",
	depth = { type="linear_y", values= {0, 1, 144, 0} },
}

room = scumm.factory.basic_room (roomDefinition)

room:add( {
	{ pos = {0, 0,-3}, components = { { type="gfx", image="gfx/forest_1.png" }}},
	{ pos = {102, 18,1}, components = { { type="gfx", image="gfx/forest_1a.png" }}},
	scumm.factory.walkarea { shape = { 
		type = "graph", 
		vertices = { {103, 35}, {154,35}, {238, 35}, {320, 35}, {154, 69}, {238, 69}}, 
		edges = { {0,1}, {1,2}, {2,3}, {1, 4}, {2, 5}}
	}},
	scumm.factory.object { id = "forest1.1" },
	scumm.factory.object { id = "forest1.2" },

})


