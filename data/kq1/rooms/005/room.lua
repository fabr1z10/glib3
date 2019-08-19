local items = engine.items

roomDefinition = {
	width = 316,
	height = 166,
	startTable = {
		['004'] = { walkarea = "005.walkarea", pos = {310, 53}, dir="west"},
	},
	defaultroom = "004",
	walkareas = { "005.walkarea" },
	font_size = 8,
	playerid="graham",
}

room = scumm.factory.sci_room (roomDefinition)

room:add ( "main",
	{ 
		{ pos = {0,0,-3}, components = { { type="gfx", image="005_bg_0.png" }}},   
		{ pos = {204, 0, 1}, components = { { type="gfx", image="005_bg_2.png" }}},   
    	scumm.factory.item_sci { id="005.king"},
		makeRoomChange { x=315, y=32, width=1, height=35, room ="004"},

	}
)
room:add ( "005.walkarea",
	{ 
		{ pos = {46, 64, 0}, components = { { type="gfx", image="005_bg_1.png" }}},
	}
)



