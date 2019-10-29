local str = strings.lefty
engine.items["lefty.walkarea"] = scumm.factory.walkarea {
	shape = { 
		type = "poly", 
		--holes=true, 
		--outline = {0,0,0,166,316,166,316,0}
		outline = {0,0,0,42,68,42,74,53,107,53,107,46,320,46,320,0}
	},
	priority = 0,
	depth = { type="linear_y", values= {0, 1, 144, 0} },
}
engine.items["lefty.sign.1"] = {
	pos = {166, 146, 0},
	model = "lefty.sign.1",
}
engine.items["lefty.sign.2"] = {
	pos = {277, 120, 0},
	model = "lefty.sign.2",
}
engine.items["lefty.window"] = makeItem {prio=2, outline = {132,89,265,137,265,89}, msg = str[1]}
engine.items["lefty.lefty"] = makeItem { prio=1, outline = {20,44,45,190,276,190,276,44}, msg = str[2]}
engine.items["lefty.door"] = makeItem {
	tag = "door",
	pos = {72, 54, -5},
	prio=2, 
	outline = {0,0,0,20,20,20,20,0}, 
	msg = str[4],
	model ="lefty.door",
	use = {
		{ type = scumm.action.walkto, args = {tag="player", pos = {89,50}}},
		{ type = scumm.action.turn, args = {tag="player", dir="n"}},
		{ type = action.animate, args = { tag = "door", anim="open", sync=true}},
		{ type = action.change_room, args = {room="leftyin"}}
	}
}


