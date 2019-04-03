roomDefinition = {
	width = 320,
	height = 144,
	startTable = {
		forest_13 = { pos = items["forest14.13"].hotspot.walk_to, dir = "east"},
		forest_15 = { pos = items["forest14.15"].hotspot.walk_to, dir = "south"},

	},
	defaultroom = "forest_13",
	depth = { type="linear_y", values= {0, 1, 144, 0} },
}

room = scumm.factory.basic_room (roomDefinition)

room:add( {
	{ pos = {0, 0,-3}, components = { { type="gfx", image="gfx/forest_14.png" }}},
	--{ pos = {122, 21,1}, components = { { type="gfx", image="gfx/forest_2a.png" }}},
	scumm.factory.walkarea { shape = { 
		type = "graph", 
		vertices = { {0, 35}, {48, 35}, {106, 35}, {48, 69} }, 
		edges = { {0,1}, {1,2},{1,3} }
	}},
	scumm.factory.object { id = "forest14.13" },
	scumm.factory.object { id = "forest14.15" },

})


