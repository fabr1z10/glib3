local items = engine.items


roomDefinition = {
	width = 320,
	height = 200,
	startTable = {
		['leftyin'] = { walkarea = "lefty.walkarea", pos = {89, 50}, dir="south"},
--		meleemap = { walkarea = "lookout.walkarea", pos = items["lookout.path"].hotspot.walk_to, dir = "east"},
	},
	defaultroom = "leftyin",
	walkareas = { "lefty.walkarea" },
	font_size = 8,
	playerid="larry",
	
}

room = scumm.factory.sci_room (roomDefinition)

room:add ( "main",
	{ 
		{ pos = {0,0,-3}, components = { { type="gfx", image="lefty.png" }}},
		scumm.factory.item_sci { id="lefty.sign.1" },
		scumm.factory.item_sci { id="lefty.sign.2" },
		scumm.factory.item_sci { id="lefty.window"},
		scumm.factory.item_sci { id="lefty.lefty"},
		scumm.factory.item_sci { id="lefty.door"},

	}
)

room:add ("lefty.walkarea",{
		{ pos = {13, 37,-3}, components = { { type="gfx", image="pole.png" }}},


})