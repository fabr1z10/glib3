local items = engine.items

roomDefinition = {
	width = 316,
	height = 166,
	startTable = {
		['007'] = { walkarea = "009.walkarea", pos = {8, 20}, dir="east"},
	},
	defaultroom = "007",
	walkareas = { "009.walkarea" },
	font_size = 8,
	playerid="graham",
	collide=true,
}

room = scumm.factory.sci_room (roomDefinition)

room:add ( "main",
	{ 
		{ pos = {0,0,-3}, components = { { type="gfx", image="009_bg_0.png" }}},   
		{ pos = {44, 35, -3+0.5}, components = { { type="gfx", image="009_bg_1.png" }}},   

		makeRoomChange { x=0, y=0, width=2, height=166, room ="007"},
		makeRoomChange { x=0, y=0, width=316, height=2, room ="002"},
		makeRoomChange { x=314, y=0, width=2, height=166, room ="010"},


		scumm.factory.item_sci {id="009.wall"},
		scumm.factory.item_sci {id="009.field"},


	}
)

-- room:add ( "007.walkarea",
-- 	{ 
-- 		scumm.factory.item_sci { id="007.tree" },
-- 	}
-- )



