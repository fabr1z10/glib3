items["village1.cliffside"] = {
	pos = {0, 0, 0},
	hotspot = {
		text = strings.objects.cliffside,
		walk_to = {11, 70}, 
		dir = "west",
		size = {20, 144},			
	},
	actions = {
		walk = { type=action.change_room, args={room="lookout"}}
	}
}

scumm.factory.door {
	id = "village1.door",
-- 	name = "village1.door",
 	pos = {699, 7, -1},
 	size = {30, 45},
 	walk_to = {715, 15},
 	dir = "north",
	model = "door_village_scummbar",
	nextroom="scummbar",
	variable = "door_village_scummbar"
-- 	door_ref = "door_village_scummbar",
-- 	model = "door_village_scummbar",
-- 	nextroom = "scummbar"
}

items["village1.poster"] = {
	pos ={259, 27, 0},
	hotspot= {
		text = strings.objects.poster,
		size = {20,23},
		walk_to = {269, 15},
		dir = "north"	
	},
 	actions = {
 		look = { type = scumm.action.say, args = {actor="guybrush", lines = {strings.village1[1], strings.village1[2]}}}
	}
}

items["village1.archway"] = {
	pos = {992, 30, 0},
	hotspot = {
		text = strings.objects.archway,
		walk_to = {1008, 34}, 
		dir = "east",
		size = {16, 40}
	},
	actions = {
		walk = { type = action.change_room, args = {room="village2"}}
	}
}