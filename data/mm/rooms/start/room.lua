local items = engine.items

roomDefinition = {
	width = 320,
	height = 128,
	startTable = {
		entrance = { walkarea = "start.walkarea", pos = {10,10}, dir="south"},
	},
	defaultroom = "entrance",
	walkareas = { "start.walkarea"},
	playerid="dave",
	font_size = 8,

	--depth = { type="linear_y", values= {0, 1, 144, 0} },
}

room = scumm.factory.basic_room (roomDefinition)

room:add ( "main",
	{ 
		{ pos = {0, 0, -3}, components = { { type="gfx", image="start.png" }}},
		{ pos = {0, 0, 3}, components = { { type="gfx", image="start1.png" }}},
		
	}
)

