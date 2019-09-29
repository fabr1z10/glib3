local items = engine.items

roomDefinition = {
	width = 496,
	height = 144,
	startTable = {
		meleemap = { walkarea="clearing.walkarea", pos = items["clearing.path"].hotspot.walk_to, dir = "west"},
		circus = { walkarea="clearing.walkarea", pos = items["clearing.tent"].hotspot.walk_to, dir = "south"}
	},
	font_size=8,
	playerid="guybrush",
	walkareas = { "clearing.walkarea"},
	collide=true,
	defaultroom = "meleemap",
	depth = { type="linear_y", values= {0, 1, 144, 0} },
	scale = { type="patchwise", rects = {
   		{ pos = {0, 0}, size={229, 144}, type="constant", value = 0.2},
   		{ pos = {229,31}, size={85, 144}, type="constant", type="linear_x", values={229,0.2,314,1.0}},
 		{ pos = {314,0}, size={200, 144}, type="constant", type="constant", value=1.0},
		{ pos = {283,0}, size={100, 32}, type="constant", type="constant", value=1.0},
	}}	
}

room = scumm.factory.basic_room  (roomDefinition)

room:add("main", {
	{ pos = {0, 0, -3}, components = { { type="gfx", image="clearing1.png" }}},
	{ pos = {441, 0, 2}, components = { { type="gfx", image="clearing2.png" }}},
	-- scumm.factory.walkarea { shape = ,
	-- },
	scumm.factory.object { id="clearing.path"},
	scumm.factory.object { id="clearing.tent"},
})

