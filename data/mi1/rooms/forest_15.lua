roomDefinition = {
	width = 320,
	height = 144,
	startTable = {
		forest_14 = { pos = items["forest15.14"].hotspot.walk_to, dir = "south"},
		forest_18 = { pos = items["forest15.18"].hotspot.walk_to, dir = "east"},
		forest_16 = { pos = items["forest15.16"].hotspot.walk_to, dir = "west"},
	},
	defaultroom = "forest_14",
	depth = { type="linear_y", values= {0, 1, 144, 0} },
}

room = scumm.factory.basic_room (roomDefinition)

room:add( {
	{ pos = {0, 0,-3}, components = { { type="gfx", image="gfx/forest_15.png" }}},
	--{ pos = {122, 21,1}, components = { { type="gfx", image="gfx/forest_2a.png" }}},
	scumm.factory.walkarea { shape = { 
		type = "graph", 
		vertices = { {0, 35}, {153, 35}, {320, 35}, {153, 69} }, 
		edges = { {0,1}, {1,2},{1,3} }
	}},
	scumm.factory.object { id = "forest15.14" },
	scumm.factory.object { id = "forest15.16" },
	scumm.factory.object { id = "forest15.18" },

})



