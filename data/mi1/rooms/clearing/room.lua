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

