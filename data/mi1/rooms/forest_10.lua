roomDefinition = {
	width = 320,
	height = 144,
	startTable = {
		forest_9 = { pos = items["forest10.9"].hotspot.walk_to, dir = "west"},
		forest_11 = { pos = items["forest10.11"].hotspot.walk_to, dir = "east"},

	},
	defaultroom = "forest_9",
	depth = { type="linear_y", values= {0, 1, 144, 0} },
}

room = scumm.factory.basic_room (roomDefinition)

room:add( {
	{ pos = {0, 0,-3}, components = { { type="gfx", image="gfx/forest_10.png" }}},
	--{ pos = {122, 21,1}, components = { { type="gfx", image="gfx/forest_2a.png" }}},
	scumm.factory.walkarea { shape = { 
		type = "graph", 
		vertices = { {0, 24}, {320,24} }, 
		edges = { {0,1} }
	}},
	scumm.factory.object { id = "forest10.9" },
	scumm.factory.object { id = "forest10.11" },

})


