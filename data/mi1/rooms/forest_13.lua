roomDefinition = {
	width = 320,
	height = 144,
	startTable = {
		forest_12 = { pos = items["forest13.12"].hotspot.walk_to, dir = "west"},
		forest_14 = { pos = items["forest13.14"].hotspot.walk_to, dir = "south"},

	},
	defaultroom = "forest_10",
	depth = { type="linear_y", values= {0, 1, 144, 0} },
}

room = scumm.factory.basic_room (roomDefinition)

room:add( {
	{ pos = {0, 0,-3}, components = { { type="gfx", image="gfx/forest_13.png" }}},
	--{ pos = {122, 21,1}, components = { { type="gfx", image="gfx/forest_2a.png" }}},
	scumm.factory.walkarea { shape = { 
		type = "graph", 
		vertices = { {159, 35}, {256, 35}, {320, 35}, {256, 69} }, 
		edges = { {0,1}, {1,2},{1,3} }
	}},
	scumm.factory.object { id = "forest13.12" },
	scumm.factory.object { id = "forest13.14" },

})


