local items = engine.items

roomDefinition = {
	width = 316,
	height = 166,
	startTable = {
		['007'] = { walkarea = "008.walkarea", pos = {84, 2}, dir="north"},
	},
	defaultroom = "007",
	walkareas = { "008.walkarea" },
	font_size = 8,
	playerid="graham",
}

room = scumm.factory.sci_room (roomDefinition)

room:add ( "main",
	{ 
		{ pos = {0,0,-3}, components = { { type="gfx", image="008_bg_0.png" }}},   
		scumm.factory.item_sci { id="008.egg" },

	}
)

-- room:add ( "007.walkarea",
-- 	{ 
-- 		scumm.factory.item_sci { id="007.tree" },
-- 	}
-- )



