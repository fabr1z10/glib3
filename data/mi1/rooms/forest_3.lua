roomDefinition = {
	width = 320,
	height = 144,
	startTable = {
		forest_2 = { pos = items["forest3.2"].hotspot.walk_to, dir = "south"},
		forest_4 = { pos = items["forest3.4"].hotspot.walk_to, dir = "west"},

	},
	defaultroom = "forest2",
	depth = { type="linear_y", values= {0, 1, 144, 0} },
}

room = scumm.factory.basic_room (roomDefinition)

room:add( {
	{ pos = {0, 0,-3}, components = { { type="gfx", image="gfx/forest_3.png" }}},
	--{ pos = {122, 21,1}, components = { { type="gfx", image="gfx/forest_2a.png" }}},
	scumm.factory.walkarea { shape = { 
		type = "graph", 
		vertices = { {135, 69}, {135,35}, {320, 35}}, 
		edges = { {0,1}, {1,2} }
	}},
	scumm.factory.object { id = "forest3.2" },
	scumm.factory.object { id = "forest3.4" },

})


