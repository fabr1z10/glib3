roomDefinition = {
	width = 320,
	height = 144,
	startTable = {
		forest_6 = { pos = items["forest7.6"].hotspot.walk_to, dir = "east"},
	},
	defaultroom = "forest_6",
	depth = { type="linear_y", values= {0, 1, 144, 0} },
}

room = scumm.factory.basic_room (roomDefinition)

room:add( {
	{ pos = {0, 0,-3}, components = { { type="gfx", image="gfx/forest_7.png" }}},
	--{ pos = {122, 21,1}, components = { { type="gfx", image="gfx/forest_2a.png" }}},
	scumm.factory.walkarea { 
		shape = { 
			type = "poly", 
			outline = {0,35,86,35,236,48,320,48,320,46,236,46,184,27,168,0,123,0,86,33,0,33},
		},
		blockedlines = {
	 	    { A = {236, 0}, B = {236, 144}, active =true },
		},
	},
	scumm.factory.object { id = "forest7.6" },
	scumm.factory.object { id = "forest7.sm" },

})


