local items = engine.items

roomDefinition = {
	width = 320,
	height = 144,
	startTable = {
		forest_3 = { walkarea="forest4.walkarea", pos = items["forest4.3"].hotspot.walk_to, dir = "east"},
		forest_5 = { walkarea="forest4.walkarea", pos = items["forest4.5"].hotspot.walk_to, dir = "west"},
	},
	defaultroom = "forest_3",
	walkareas = { "forest4.walkarea"},
	font_size = 8,
	playerid="guybrush",
	depth = { type="linear_y", values= {0, 1, 144, 0} },
	collide = true,
}

room = scumm.factory.basic_room (roomDefinition)

room:add("main", {
	{ pos = {0, 0,-3}, components = { { type="gfx", image="forest_4.png" }}},
	scumm.factory.object { id = "forest4.3" },
	scumm.factory.object { id = "forest4.5" },
	scumm.factory.object { id = "forest.redplant" },

})


