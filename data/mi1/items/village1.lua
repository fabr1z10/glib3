items2["village1.cliffside"] = {
	hotspot = {
		text = strings.objects.cliffside,
		pos = {0, 0, 0},
		walk_to = {11, 70}, 
		dir = "west",
		size = {20, 144},			
	},
	actions = {
		walk = { type = action.change_room, args = {room="lookout" }}
	}
}

-- items2["village1.door"] = factory.door.create {
-- 	name = "village1.door",
-- 	pos = {699, 7, -1},
-- 	size = {30, 45},
-- 	walk_to = {715, 15},
-- 	face = "north",
-- 	door_ref = "door_village_scummbar",
-- 	model = "door_village_scummbar",
-- 	nextroom = "scummbar"
-- }

items2["village1.poster"] = {
	hotspot = {
        text = strings.objects.poster,
		pos = {259, 27, 0},
		walk_to = {269, 15},
		dir = "north",
		size = {20, 23}
	},
 	actions = {
 		look = { type = action.say, args = { actor="guybrush", lines = {strings.village1[1], strings.village1[2]}}}
 	}
}

items2["village1.archway"] = {
	hotspot = {
		text = strings.objects.archway,
		pos = {992, 30, 0},
		walk_to = {1008, 20}, 
		dir = "east",
		size = {16, 40}
	},
	actions = {
		walk = { type = action.change_room, args = {room="village2"}}
	}
}