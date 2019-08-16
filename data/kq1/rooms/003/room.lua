local items = engine.items

roomDefinition = {
	width = 316,
	height = 166,
	startTable = {
		['002'] = { walkarea = "003.walkarea", pos = {158, 5}, dir="north"},
		['004'] = { walkarea = "003.walkarea", pos = {156, 100}, dir = "south"}
	},
	defaultroom = "002",
	walkareas = { "003.walkarea" },
	font_size = 8,
	playerid="graham",
}

room = scumm.factory.sci_room (roomDefinition)

room:add ( "main",
	{ 
		{ pos = {0,0,-3}, components = { { type="gfx", image="003_bg_0.png" }}},
		makeRoomChange { x=114, y=0, width=86, height=1, room ="002"},
		makeRoomChange { x=112, y=103, width=88, height=1, room ="004"},
		{ pos = {128, 76, 1}, components = { { type="gfx", image="003_bg_3.png" }}},
    
	}
)

room:add ( "003.walkarea", { 
		{ pos = {54, 41, 0}, components = { { type="gfx", image="003_bg_2.png" }}},
		{ pos = {238, 41, 0}, components = { { type="gfx", image="003_bg_1.png" }}},
})	

-- room:add ( "001.moat", {
-- 	scumm.factory.item_sci { id="alligator_1"},
-- 	scumm.factory.item_sci { id="alligator_2"},


-- })



