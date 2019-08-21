local items = engine.items

roomDefinition = {
	width = 316,
	height = 166,
	startTable = {
		['002'] = { walkarea = "006.walkarea", pos = {306, 50}, dir="west"},
		['007'] = { walkarea = "006.walkarea", pos = {216, 123}, dir="south"},
	},
	defaultroom = "002",
	walkareas = { "006.walkarea" },
	font_size = 8,
	playerid="graham",
}

room = scumm.factory.sci_room (roomDefinition)

room:add ( "main",
	{ 
		{ pos = {0,0,-3}, components = { { type="gfx", image="006_bg_0.png" }}}, 
		makeRoomChange { x=1, y=124, width=314, height=1, room ="007"},
 
	}
)

room:add ( "006.walkarea",
	{ 
		scumm.factory.item_sci { id="006.rock" },
		scumm.factory.item_sci { id="006.hole" },
	}
)



