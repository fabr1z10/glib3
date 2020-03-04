-- the local objects
engine.items["meleemap.walkarea"] = {
	type = 'walkarea',
	shape = { 
		type = "graph", 
		vertices = { {76, 80}, {78, 81}, {71,90}, {64, 96}, {48,99}, {49, 114}, {73, 113}, {88, 114},{118,114}, {135,113}, {83,109},
			{101, 107}, {112, 97}, {157, 78}, {172, 64}, {196, 54}, {217,54}, {232,49}, {245,48}, {254,50}, {275, 95}, {54,131},{57,140}, {60,151},
		 	{67,161}, {82, 174}, {113, 177}, {146, 168}, {169,168}, {180, 174}, {196,174}, {227,180} }, 
		edges = { {0,1}, {1,2}, {2,3},{3,4}, {4,5}, {5,6}, {6,7}, {7,8}, {8,9}, {6,10}, {10,11}, {11,12}, {12,13}, {13,14}, {14,15}, {15,16},{16,17},{17,18},
			{18,19}, {19,20}, {5,21}, {21,22}, {22,23}, {23,24}, {24,25}, {25,26}, {26,27}, {27, 28}, {28,29}, {29,30}, {30,31}}
	},
	priority = 0,
	scale = { type="constant", value = 0.2},
}

engine.items['meleemap.lookout'] = {
	type = 'mapitem',
	pos = {75, 79, 0},
	name = strings.objects.lookout,
	go_to = {
		room = 'lookout',
		pos = mi.rooms.lookout.to_map,
		dir = 'w'
	}
}	

engine.items['meleemap.village'] = {
	type = 'mapitem',
	pos = {68, 73, 0},
	name = strings.objects.village,
	go_to = {
		room = 'village1',
		pos = mi.rooms.village1.to_lookout,
		dir = 'e'
	}
}	

engine.items['meleemap.clearing'] = {
	type = 'mapitem',
	pos = {136, 113, 0},
	name = strings.objects.clearing,
	go_to = {
		room = 'clearing',
		pos = mi.rooms.clearing.to_map,
		dir = 'w'
	}
}	
engine.items['meleemap.fork'] = {
	type = 'mapitem',
	pos = {74, 112, 0},
	name = strings.objects.fork,
	go_to = {
		room = 'forest_1',
		pos = mi.rooms.forest1.to_map,
		dir = 'w'
	}
}
		
