roomDefinition = {
	width = 320,
	height = 144,
	startTable = {
		forest_5 = { pos = items["forest6.5"].hotspot.walk_to, dir = "east"},
		forest_7 = { pos = items["forest6.7"].hotspot.walk_to, dir = "south"},
	},
	defaultroom = "forest_5",
	depth = { type="linear_y", values= {0, 1, 144, 0} },
}

room = scumm.factory.basic_room (roomDefinition)

room:add( {
	{ pos = {0, 0,-3}, components = { { type="gfx", image="gfx/forest_6.png" }}},
	--{ pos = {122, 21,1}, components = { { type="gfx", image="gfx/forest_2a.png" }}},
	scumm.factory.walkarea { shape = { 
		type = "graph", 
		vertices = { {0, 35}, {241,35}, {320, 35}, {241, 69}}, 
		edges = { {0,1}, {1,2}, {1,3} }
	}},
	scumm.factory.object { id = "forest6.5" },
	scumm.factory.object { id = "forest6.7" },
})


