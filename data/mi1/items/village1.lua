engine.items['village1.walkarea'] = {
	type = 'walkarea',
	shape = { type = "graph", 
		vertices = { {8, 71}, {23, 63}, {49, 49}, {40, 37}, {56, 24}, {84, 13}, {770, 13}, {780,34}, {1000,34} }, 
		edges = { {0,1}, {1,2}, {2,3},{3,4}, {4,5},{5,6},{6,7},{7,8} }},
	scale = { type="linear_y", values= {0, 0.8, 144, 0.1}},
}


engine.items['village1.door'] = make_door {
	tag = 'village1.door',
	model = 'door_village_scummbar',
 	pos = {699, 7, -1},
 	size = {30, 45},
 	walk_to = {715, 13},
 	dir = 'n',
	var = 'door_village_scummbar',
	room = 'scummbar'
}

engine.items["village1.cliffside"] = {
	type = 'object',
	pos = {0, 0, 0},
	hotspot = {
		text = strings.objects.cliffside,
		walk_to = {11, 70}, 
		dir = 'w',
		size = {20, 144},			
	},
	actions = {
		walk = { type = action.change_room, args = {room='lookout'}}
	}
}
