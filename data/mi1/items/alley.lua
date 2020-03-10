engine.items["alley.walkarea"] = {
	type = 'walkarea',
	tag = true,
	shape = { type = "poly", outline ={0,34,120,34,120,18,190,18,190,47,304,47,304,0,18,0,18,13,0,13}},
	priority = 0,
	depth = { type="linear_y", values= {0, 1, 144, 0} },
}

engine.items["alley.exit"] = {
	type = 'object',
	pos = {0, 0, 0},
	hotspot = {
		text = strings.objects.archway,
		walk_to = mi.rooms.alley.to_village3, 
		dir = "west",
		size = {10, 144}
	},			
	actions = {
		walk = scumm.script.changeroom { room="village3", pos = mi.rooms.village3.to_alley, dir = 's'}
	}
}


