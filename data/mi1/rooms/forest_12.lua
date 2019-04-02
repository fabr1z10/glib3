roomDefinition = {
	width = 320,
	height = 144,
	startTable = {
		forest_11 = { pos = items["forest12.11"].hotspot.walk_to, dir = "west"},
		forest_13 = { pos = items["forest12.13"].hotspot.walk_to, dir = "east"},

	},
	defaultroom = "forest_9",
	depth = { type="linear_y", values= {0, 1, 144, 0} },
}

room = scumm.factory.basic_room (roomDefinition)

room:add( {
	{ pos = {0, 0,-3}, components = { { type="gfx", image="gfx/forest_12.png" }}},
	--{ pos = {122, 21,1}, components = { { type="gfx", image="gfx/forest_2a.png" }}},
	scumm.factory.walkarea { shape = { 
		type = "graph", 
		vertices = { {0, 46}, {103, 46}, {170, 35}, {320, 35} }, 
		edges = { {0,1}, {1,2}, {2,3} }
	}},
	scumm.factory.object { id = "forest12.11" },
	scumm.factory.object { id = "forest12.13" },

})


