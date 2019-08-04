local items = engine.items

roomDefinition = {
	width = 320,
	height = 144,
	startTable = {
		meleemap = { walkarea = "forest1.walkarea", pos = items["forest1.1"].hotspot.walk_to, dir = "west"},
		forest_2 = { walkarea = "forest1.walkarea", pos = items["forest1.2"].hotspot.walk_to, dir = "south"},

	},
	defaultroom = "meleemap",
	walkareas = { "forest1.walkarea"},
	font_size = 8,
	playerid="guybrush",
	--depth = { type="linear_y", values= {0, 1, 144, 0} },
}

room = scumm.factory.basic_room (roomDefinition)

room:add ( "main",
	{ 
		{ pos = {0, 0,-3}, components = { { type="gfx", image="forest_1.png" }}},
		{ pos = {102, 18,1}, components = { { type="gfx", image="forest_1a.png" }}},        
		scumm.factory.object { id = "forest1.1" },
		scumm.factory.object { id = "forest1.2" },
		scumm.factory.object { id = "forest1.2b" },	
	}
)



