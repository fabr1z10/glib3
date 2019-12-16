local items = engine.items

roomDefinition = {
	width = 316,
	height = 166,
	startTable = {
		['006'] = { walkarea = "007.walkarea", pos = {158, 4}, dir="north"},
		['008'] = { walkarea = "007.walkarea", pos = {190, 10}, dir="south"},
		['009'] = { walkarea = "007.walkarea", pos = {300, 10}, dir="west"},
	},
	defaultroom = "006",
	walkareas = { "007.walkarea" },
	font_size = 8,
	playerid="graham",
	collide = true
}

room = scumm.factory.sci_room (roomDefinition)

room:add ( "main",
	{ 
		{ pos = {0,0,-3}, components = { { type="gfx", image="007_bg_0.png" }}},   
		makeRoomChange { x=1, y=0, width=314, height=2, room ="006"},
		makeRoomChange { x=314, y=0, width=2, height=166, room ="009"},

	}
)

room:add ( "007.walkarea",
	{ 
		scumm.factory.item_sci { id="007.tree" },
	}
)



