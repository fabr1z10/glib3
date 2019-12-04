-- the local objects
engine.items["swordmaster.walkarea"] = scumm.factory.walkarea {
	shape = { type = "poly", outline = {0, 22, 180, 22, 215, 16,233,29,259,35,325,73,409,74,409,47,372,21,307,17,273,31,263,32,247,28,224,12,211,6,0,6}},
	priority = 0,
	depth = { type="linear_y", values= {0, 1, 144, 0} },
	scale = { type="constant", value=0.3 }	
}

engine.items["swordmaster.sm"] = {
	pos = {385,68,0.5},
	model = "swordmaster.smtiny",
	hotspot = {
		text = strings.objects.swordmaster,
		walk_to = {375, 68}, 
		dir = "east",
		offset = {-4,0},
		size = {8, 12},			
	},
	actions = {
		--wal = { type = action.change_room, args = {room="meleemap"}}
	}
}