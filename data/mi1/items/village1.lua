items.village1 = {}

-- the local objects
items.village1.cliffside = {
	text = strings.objects.cliffside,
	pos = {0, 0, 0},
	walk_to = {11, 70}, 
	face = "west",
	size = {20, 144},			
	actions = {
		walk = curry(change_room, "lookout")
	}
}

items.village1.door = factory.door.create {
	tag = "door",
	pos = {699, 7, -1},
	size = {30, 45},
	walk_to = {715, 15},
	face = "north",
	door_ref = "door_village_scummbar",
	model = "door_village_scummbar",
	nextroom = "scummbar"
}

items.village1.poster = {
	text = strings.objects.poster,
	pos ={259, 27, 0},
	size = {20,23},
	walk_to = {269, 15},
	face = "north",
	actions = {
		look = curry (say, {actor =items.guybrush, lines = {strings.village1[1], strings.village1[2]}})
	}
}
