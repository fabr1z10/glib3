local items = engine.items

roomDefinition = {
	width = 316,
	height = 166,
	startTable = {
		['003'] = { walkarea = "004.walkarea", pos = {158, 5}, dir="north"},
	},
	defaultroom = "003",
	walkareas = { "004.walkarea" },
	font_size = 8,
	playerid="graham",
}

room = scumm.factory.sci_room (roomDefinition)

room:add ( "main",
	{ 
		{ pos = {0,0,-3}, components = { { type="gfx", image="004_bg_0.png" }}},
		{ pos = {0,0,1}, components = { { type="gfx", image="004_bg_1.png" }}},
		makeRoomChange { x=93, y=0, width=132, height=1, room ="003"},
		makeRoomChange { x=0, y=0, width=1, height=78, room ="005"},
		{ pos = {128, 76, 1}, components = { { type="gfx", image="003_bg_3.png" }}},

		--makeRoomChange { x=114, y=0, width=86, height=1, room ="002"},
		--makeRoomChange { x=112, y=103, width=88, height=1, room ="004"},
		--{ pos = {128, 76, 1}, components = { { type="gfx", image="003_bg_3.png" }}},
    
	}
)
