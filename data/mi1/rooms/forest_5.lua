roomDefinition = {
	width = 320,
	height = 144,
	startTable = {
		forest_4 = { pos = items["forest5.4"].hotspot.walk_to, dir = "south"},
		forest_6 = { pos = items["forest5.6"].hotspot.walk_to, dir = "east"},
	},
	defaultroom = "forest_4",
	depth = { type="linear_y", values= {0, 1, 144, 0} },
}

room = scumm.factory.basic_room (roomDefinition)

room:add( {
	{ pos = {0, 0,-3}, components = { { type="gfx", image="gfx/forest_5.png" }}},
	--{ pos = {122, 21,1}, components = { { type="gfx", image="gfx/forest_2a.png" }}},
	scumm.factory.walkarea { shape = { 
		type = "graph", 
		vertices = { {0, 24}, {241,24}, {320, 24}, {241, 69}}, 
		edges = { {0,1}, {1,2}, {1,3} }
	}},
	scumm.factory.object { id = "forest5.4" },
	scumm.factory.object { id = "forest5.6" },


})


