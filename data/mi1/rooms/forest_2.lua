roomDefinition = {
	width = 320,
	height = 144,
	startTable = {
		forest_1 = { pos = items["forest2.1"].hotspot.walk_to, dir = "west"},
		forest_3 = { pos = items["forest2.3"].hotspot.walk_to, dir = "south"},

	},
	defaultroom = "forest1",
	depth = { type="linear_y", values= {0, 1, 144, 0} },
}

room = scumm.factory.basic_room (roomDefinition)

room:add( {
	{ pos = {0, 0,-3}, components = { { type="gfx", image="gfx/forest_2.png" }}},
	{ pos = {122, 21,1}, components = { { type="gfx", image="gfx/forest_2a.png" }}},
	scumm.factory.walkarea { shape = { 
		type = "graph", 
		vertices = { {0, 35}, {257,35}, {320, 35}, {257, 69}}, 
		edges = { {0,1}, {1,2}, {1,3}}
	}},
	scumm.factory.object { id = "forest2.1" },
	scumm.factory.object { id = "forest2.3" },

})


