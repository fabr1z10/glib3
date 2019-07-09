local roomInfo = {
	worldWidth = 224,
	worldHeight = 16,
	startPos = {2, 4},
	collisionSize = 80,
	g = -10
}

local initscripts = {}


room = {

	engines = {
		{ type = "scheduler"},
		{ 
			type = "collision", 
			size = {roomInfo.collisionSize, roomInfo.collisionSize}, 
			response = {
				{ tag = {variables.tags.player_attack, variables.tags.foe}, onenter = player_hits },
				{ tag = {variables.tags.foe_attack, variables.tags.player}, onenter = player_is_hit },
				{ tag = {variables.tags.player_attack, variables.tags.hittable_block}, onenter = mario_removeenemy }
			}
		},
		{
			type ="dynamicworld",
			width = 256, 
			height = 256,
			cam ="maincam",
			items = {
			}
		}
	},

    scene = {
		[1] = {
			tag = "main",
			camera = {
				tag = "maincam",
				type="ortho",
				size = {256, 256},
				bounds = {0, 0, roomInfo.worldWidth*16, roomInfo.worldHeight*16},
				viewport = {0, 0, 256, 256}
			},
			children = {
				{ pos = {0,256,0}, components = { { type = "text", id="TOP LEFT", font="main", size=8 }}},
				{ pos = {256,256,0}, components = {	{ type = "text", id="TOP RIGHT", font="main", size=8, align = "topright" }}},
				{ pos = {0,0,0}, components = { { type = "text", id="BOTTOM LEFT", font="main", size=8, align = "bottomleft" }}},
				{ pos = {256,0,0}, components = {	{ type = "text", id="BOTTOM RIGHT", font="main", size=8, align = "bottomright" }}},
				{ pos = {128,256,0}, components = {	{ type = "text", id="TOP", font="main", size=8, align = "top" }}},
				{ pos = {128,0,0}, components = {	{ type = "text", id="BOTTOM", font="main", size=8, align = "bottom" }}},
				{ pos = {128,128,0}, components = {	{ type = "text", id="CENTER", font="main", size=8, align = "center" }}},
			}
		},
	},
}
