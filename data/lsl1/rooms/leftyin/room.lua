local items = engine.items


roomDefinition = {
	width = 320,
	height = 200,
	startTable = {
		['lefty'] = { walkarea = "leftyin.walkarea", pos = {10, 15}, dir="north"},
--		meleemap = { walkarea = "lookout.walkarea", pos = items["lookout.path"].hotspot.walk_to, dir = "east"},
	},
	defaultroom = "lefty",
	walkareas = { "leftyin.walkarea" },
	font_size = 8,
	playerid="larry",
	
}

room = scumm.factory.sci_room (roomDefinition)

room:add ( "main",
	{ 
		{ pos = {0,0,-3}, components = { { type="gfx", image="leftyin.png" }}},

	}
)