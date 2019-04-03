roomDefinition = {
	width = 320,
	height = 144,
	startTable = {
		forest_17 = { pos = items["forest21.17"].hotspot.walk_to, dir = "west"},
	},
	defaultroom = "forest_17",
	depth = { type="linear_y", values= {0, 1, 144, 0} },
}

room = scumm.factory.basic_room (roomDefinition)

room:add( {
	{ pos = {0, 0,-3}, components = { { type="gfx", image="gfx/forest_21.png" }}},
	--{ pos = {122, 21,1}, components = { { type="gfx", image="gfx/forest_2a.png" }}},
	scumm.factory.walkarea { shape = { 
		type = "graph", 
		vertices = { {135, 35}, {320, 35} }, 
		edges = { {0,1}  }
	}},
	scumm.factory.object { id = "forest21.17" },
	

})



