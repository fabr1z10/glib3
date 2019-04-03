roomDefinition = {
	width = 320,
	height = 144,
	startTable = {
		forest_15 = { pos = items["forest16.15"].hotspot.walk_to, dir = "south"},
		forest_17 = { pos = items["forest16.17"].hotspot.walk_to, dir = "east"},

	},
	defaultroom = "forest_14",
	depth = { type="linear_y", values= {0, 1, 144, 0} },
}

room = scumm.factory.basic_room (roomDefinition)

room:add( {
	{ pos = {0, 0,-3}, components = { { type="gfx", image="gfx/forest_16.png" }}},
	--{ pos = {122, 21,1}, components = { { type="gfx", image="gfx/forest_2a.png" }}},
	scumm.factory.walkarea { shape = { 
		type = "graph", 
		vertices = { {0, 48}, {155, 48}, {215, 35}, {320, 35}, {155,69} }, 
		edges = { {0,1}, {1,2}, {2,3}, {1,4} }
	}},
	scumm.factory.object { id = "forest16.15" },
	scumm.factory.object { id = "forest16.17" },
	

})



