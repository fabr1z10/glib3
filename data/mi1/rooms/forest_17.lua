roomDefinition = {
	width = 320,
	height = 144,
	startTable = {
		forest_16 = { pos = items["forest17.16"].hotspot.walk_to, dir = "west"},
		forest_21 = { pos = items["forest17.21"].hotspot.walk_to, dir = "east"},
		treasure = { pos = items["forest17.treasure"].hotspot.walk_to, dir ="south"}
	},
	defaultroom = "forest_16",
	depth = { type="linear_y", values= {0, 1, 144, 0} },
}

room = scumm.factory.basic_room (roomDefinition)

room:add( {
	{ pos = {0, 0,-3}, components = { { type="gfx", image="gfx/forest_17.png" }}},
	--{ pos = {122, 21,1}, components = { { type="gfx", image="gfx/forest_2a.png" }}},
	scumm.factory.walkarea { shape = { 
		type = "graph", 
		vertices = { {0, 48}, {155, 48}, {215, 35}, {320, 35}, {155,69} }, 
		edges = { {0,1}, {1,2}, {2,3}, {1,4} }
	}},
	scumm.factory.object { id = "forest17.16" },
	scumm.factory.object { id = "forest17.21" },
	scumm.factory.object { id = "forest17.treasure" },
	

})



