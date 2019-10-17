engine.items["voodoolady.walkarea"] = scumm.factory.walkarea {
   	shape = { 
		type = "poly", 
		outline = {78,37,124,47,146,42,320,42,320,40,320,0,156,0,145,22},
        holes = {
 	       {164,11,194,11,194,7,164,7}
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

engine.items["voodoolady.baskets"] = {
	pos = {87, 0, 1},
	hotspot = {
		text = strings.objects.baskets,
		size = {80, 35},
		walk_to = {112, 5},
		priority=1,
		dir = "south"
	},
	model = "voodoolady.baskets",
	actions = {
		look = { type= scumm.action.say, args = {actor="guybrush", lines = {strings.voodoolady[4]}}},
	}
}


engine.items["voodoolady.basket"] = {
	pos = {168, 10, 1},
	hotspot = {
		text = strings.objects.basket,
		size = {23, 20},
		walk_to = {178, 12},
		priority=1,
		dir = "south"
	},
	model = "voodoolady.basket",
	actions = {
		look = { type= scumm.action.say, args = {actor="guybrush", lines = {strings.voodoolady[5]}}},
	}
}


engine.items["rubber.chicken"] = { 
	pos = {238, 16, 2},
	hotspot = {
		text = strings.objects.chicken,
		size = {24, 20},
		walk_to = {260, 10},
		priority=2,
		dir = "south"
	},
 	model = "rubber.chicken",
 	actions = {
 		look = {
 			{ type= scumm.action.say, args = {actor="guybrush", lines = {strings.voodoolady[19], strings.voodoolady[20], strings.voodoolady[21]}}},
 			{ type= scumm.action.change_text_item, args = {id="rubber.chicken", text = strings.objects.rubberchicken }},
 		},
 		pick = {
 			glib.curry(scumm.action.pickup2, {id="rubber.chicken", anim1="operate_s", anim2="idle_s"})(),
 			{ type= scumm.action.say, args = {actor="guybrush", lines = {strings.voodoolady[22]}}}
 		}

 	}	
}