roomDefinition = {
	width = 320,
	height = 144,
	startTable = {
		forest_15 = { pos = items["forest18.15"].hotspot.walk_to, dir = "south"},
		forest_19 = { pos = items["forest18.19"].hotspot.walk_to, dir = "west"},
	},
	defaultroom = "forest_15",
	depth = { type="linear_y", values= {0, 1, 144, 0} },
}

room = scumm.factory.basic_room (roomDefinition)

room:add( {
	{ pos = {0, 0,-3}, components = { { type="gfx", image="gfx/forest_18.png" }}},
	--{ pos = {122, 21,1}, components = { { type="gfx", image="gfx/forest_2a.png" }}},
	scumm.factory.walkarea { shape = { 
		type = "graph", 
		vertices = { {0, 35}, {135, 35}, {187, 35}, {135, 69} }, 
		edges = { {0,1}, {1,2}, {2,3} }
	}},
	scumm.factory.object { id = "forest18.15" },
	scumm.factory.object { id = "forest18.19" },
	

})



