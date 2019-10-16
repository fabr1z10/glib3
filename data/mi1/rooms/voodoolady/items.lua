engine.items["voodoolady.walkarea"] = scumm.factory.walkarea {
   	shape = { 
		type = "poly", 
		outline = {78,37,124,47,146,42,320,42,320,40,320,0,156,0,145,22},
        holes = {
 	       {164,21,164,7,194,7,194,21}
        }
	},
	depth = { type="linear_y", values= {0, 1, 144, 0} },
	priority = 0,
}

scumm.factory.door {
	id = "voodoolady.door",
	pos = {87, 42, -1},
	size = {33, 58},
	walk_to = {108, 38},
	dir = "west",
	model = "door_voodoolady",
	nextroom="village2",
	variable = "door_voodoolady"
}

engine.items["voodoolady.trunk"] = { 
	pos = {230, 0, 1},
	hotspot = {
		text = strings.objects.trunk,	
		size = {81, 24},
		walk_to = {265, 10},
		dir = "south"
	},
 	model = "voodoolady.trunk",
 	actions = {
 	}	
}

