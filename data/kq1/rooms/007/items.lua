engine.items["007.walkarea"] = scumm.factory.walkarea {
	shape = { 
		type = "poly", 
		holes = {},
		outline = {0,0,0,120,316,120,316,0}},
	priority = 0,
	depth = { type="linear_y", values= {0, 1, 144, 0} },
}

engine.items["007.tree"] = makeItem { 
	x = 130, y= 15,
	--x=0,y=0,
	priority=2,
	outline = {26,2,80,21,112,85,26,105,0,151,186,151,186,74,151,68,139,14,178,3},
	msg = strings.room007[1],
	gfx = "007_bg_1.png",
	hole = { 
		outline = {24,0,24,2,180,2,180,0}

	--s	outline = {50, 50, 50, 150, 250, 150, 250, 50}
	--	outline = {24,2,35,-2, 78, -2, 79, -9,93,-9, 109, -3, 182, 2, 175,6, 29, 4}
	},
	use = {
		{ type = scumm.action.walkto, args = { tag="player", pos = {206, 8}}},
		{ type = scumm.action.turn, args = {tag="player", dir="n"}},
		{ type = action.kq.showmessage, args = { msg = strings.room007[2] }},
		{ type = action.change_room, args = {room ="008"}}
	}
}