local items = engine.items

roomDefinition = {
	width = 960,
	height = 128,
	startTable = {
		start = { walkarea = "frontdoor.walkarea", pos = {950, 10}, dir="west"},
	},
	defaultroom = "start",
	walkareas = { "frontdoor.walkarea"},
	playerid="dave",
	font_size = 8,
}

room = scumm.factory.basic_room (roomDefinition)

room:add ( "main",
	{ 
		{ pos = {0, 0, -3}, components = { { type="gfx", image="frontdoor.png" }}},
		scumm.factory.object { id="frontdoor.bushes"},
		scumm.factory.object { id="frontdoor.grating"},
		scumm.factory.object { id="frontdoor.doormat"},
		scumm.factory.object { id="frontdoor.key"},


	}
)

room:add ( "frontdoor.walkarea",
	{ 
		{ pos = {815, 0, 0}, components = { { type="gfx", image="frontdoor_1.png" }}},
		{ pos = {72, 44, 0}, components = { { type="gfx", image="frontdoor_2.png" }}},


	}
)
