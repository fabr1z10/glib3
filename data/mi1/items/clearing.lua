items["clearing.path"] = {
	text = strings.objects.path,
	pos = {480, 0, 0},
	size = {16, 144},			
	walk_to = {496, 10}, 
	face = "east",
	actions = {
		walk = ms { {action.change_room, {id=1,room="meleemap"}}}
	}
}

items["clearing.tent"] = {
	text = strings.objects.circustent,
	pos = {47, 63, 0},
	size = {135, 70},
	walk_to = {160, 80}, 
	face = "north",
	actions = {
		walk = ms { {action.change_room, {id=1,room="circus"}}}
	}
}

