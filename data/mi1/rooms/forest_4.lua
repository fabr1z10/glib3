roomDefinition = {
	width = 320,
	height = 144,
	startTable = {
		forest_3 = { pos = items["forest4.3"].hotspot.walk_to, dir = "east"},
		forest_5 = { pos = items["forest4.5"].hotspot.walk_to, dir = "west"},

	},
	defaultroom = "forest_3",
	depth = { type="linear_y", values= {0, 1, 144, 0} },
}

room = scumm.factory.basic_room (roomDefinition)

room:add( {
	{ pos = {0, 0,-3}, components = { { type="gfx", image="gfx/forest_4.png" }}},
	--{ pos = {122, 21,1}, components = { { type="gfx", image="gfx/forest_2a.png" }}},
	scumm.factory.walkarea { shape = { 
		type = "graph", 
		vertices = { {0, 35}, {266,35}, {320, 35}, {266, 20}}, 
		edges = { {0,1}, {1,2}, {1,3} }
	}},
	scumm.factory.object { id = "forest4.3" },
	scumm.factory.object { id = "forest4.5" },

})


