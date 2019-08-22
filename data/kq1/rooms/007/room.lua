local items = engine.items

roomDefinition = {
	width = 316,
	height = 166,
	startTable = {
		['006'] = { walkarea = "007.walkarea", pos = {158, 2}, dir="north"},
	},
	defaultroom = "006",
	walkareas = { "007.walkarea" },
	font_size = 8,
	playerid="graham",
}

room = scumm.factory.sci_room (roomDefinition)

room:add ( "main",
	{ 
		{ pos = {0,0,-3}, components = { { type="gfx", image="007_bg_0.png" }}},   
		makeRoomChange { x=1, y=0, width=314, height=1, room ="006"},

	}
)

room:add ( "007.walkarea",
	{ 
		scumm.factory.item_sci { id="007.tree" },
	}
)


