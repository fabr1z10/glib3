local items = engine.items

roomDefinition = {
	width = 496,
	height = 144,
	startTable = {
		village2 = { walkarea="voodoolady.walkarea", pos = items["voodoolady.door"].hotspot.walk_to, dir = "east"},
	},
	font_size = 8,
	playerid="guybrush",
	defaultroom = "village2",
	walkareas = { "voodoolady.walkarea"},
	enableScroll = false,
	collide = true,
}

room = scumm.factory.basic_room (roomDefinition)

room:add ( "main",
	{ 
		{ pos = {0, 0,-3}, components = { { type="gfx", image="voodoolady1.png" }}},
		scumm.factory.object { id="voodoolady.door"},
		scumm.factory.object { id="rubber.chicken"}
	}
)

room:add ("voodoolady.walkarea",	
	{
		scumm.factory.object {id = "voodoolady.trunk"},
		scumm.factory.object {id = "voodoolady.baskets"},
		scumm.factory.object {id = "voodoolady.basket"}
	}
)
