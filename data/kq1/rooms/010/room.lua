local items = engine.items

roomDefinition = {
	width = 316,
	height = 166,
	startTable = {
		['011'] = { walkarea = "010.walkarea", pos = {308, 20}, dir="west"},
		['009'] = { walkarea = "010.walkarea", pos = {10, 20}, dir="east"},
	},
	defaultroom = "010",
	walkareas = { "010.walkarea" },
	font_size = 8,
	playerid="graham",
	collide=true,
}

room = scumm.factory.sci_room (roomDefinition)

room:add ( "main",
	{ 
		{ pos = {0,0,-3}, components = { { type="gfx", image="010_bg_0.png" }}},   
		{ pos = {160, 35, -3+0.5}, components = { { type="gfx", image="010_bg_1.png" }}},   
		scumm.factory.item_sci {id="010.garden"},
		scumm.factory.item_sci {id="010.wall"},

	}
)


