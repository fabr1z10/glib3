roomDefinition = {
	width = 496,
	height = 144,
	startTable = {
		meleemap = { pos = items["clearing.path"].hotspot.walk_to, dir = "west"},
		circus = { pos = items["clearing.tent"].hotspot.walk_to, dir = "south"}
	},
	defaultroom = "meleemap",
	depth = { type="linear_y", values= {0, 1, 144, 0} },
	scale = { type="patchwise", rects = {
   		{ pos = {0, 0}, size={229, 144}, type="constant", value = 0.2},
   		{ pos = {229,31}, size={85, 144}, type="constant", type="linear_x", values={229,0.2,314,1.0}},
 		{ pos = {314,0}, size={200, 144}, type="constant", type="constant", value=1.0},
		{ pos = {283,0}, size={100, 32}, type="constant", type="constant", value=1.0},
	}}	
}

room = scumm.factory.basic_room(roomDefinition)

room:add( {
	{ pos = {0, 0, -3}, components = { { type="gfx", image="gfx/clearing1.png" }}},
	{ pos = {441, 0, 2}, components = { { type="gfx", image="gfx/clearing2.png" }}},
	scumm.factory.walkarea { shape = { type = "poly", outline = 
		{496,38,496,0, 283, 0, 283, 20, 315, 28,315, 44, 229, 31, 92, 31, 41, 64,54, 75, 80, 64, 115, 58, 119, 48,
		165, 53, 180,64, 214, 64, 229, 33, 315, 46, 400,38}},
	},
	scumm.factory.object { id="clearing.path"},
	scumm.factory.object { id="clearing.tent"},
})

