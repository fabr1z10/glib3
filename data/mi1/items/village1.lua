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
	go_to = { room = 'scummbar', pos = mi.rooms.scummbar.door_out, dir = 'e' }
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
		walk = scumm.script.changeroom { room = 'lookout', pos = mi.rooms.lookout.to_village, dir='n' }
	}
}

engine.items["village1.archway"] = {
	type = 'object',
	pos = {992, 30, 0},
	hotspot = {
		text = strings.objects.archway,
		walk_to = mi.rooms.village1.to_village2,
		dir = 'e',
		size = {16, 40}
	},
	actions = {
		walk = scumm.script.changeroom { room = 'village2', pos = mi.rooms.village2.to_village1, dir='s' }
	}
}

engine.items["village1.poster"] = {
	type = 'object',	
	pos ={259, 27, 0},
	hotspot= {
		text = strings.objects.poster,
		size = {20, 23},
		walk_to = {269, 15},
		dir = 'n'	
	},
 	actions = {
 		look = { type = scumm.action.say, args = { tag="player", lines = {strings.village1[1], strings.village1[2]}}}
	}
}