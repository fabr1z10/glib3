-- the local objects
engine.items["frontdoor.walkarea"] = scumm.factory.walkarea {
	shape = { type = "poly", outline = {0,2,0,16,283,16, 283,4, 305,4, 338, 44.1, 123, 44.1, 123, 44.2, 657, 44.2, 657, 44.1, 420, 44.1,  456, 4, 479,4,479,16, 960,16,960,2}},
	priority = 0,
	depth = { type="linear_y", values= {0, 1, 128, 0} },

}

engine.items["frontdoor.bushes"] = { 
	pos = {256, 16, -0.99},
	model = "bushes",
	hotspot = {
		text = strings.objects.bushes,
		size = {52, 18},
		walk_to = {275, 12},
		dir = "north",
		priority=2
	},
 	actions = {
 		look = { type = action.say, args = {actor="dave", lines = {"prova"}}},
 		pick = { type = action.remove_object, args = { tag ="frontdoor.bushes"} }
 	}	
}

engine.items["frontdoor.grating"] = { 
	pos = {257, 16, -1},
	model = "grating",
	hotspot = {
		text = strings.objects.grating,
		size = {50, 16},
		walk_to = {275, 12},
		dir = "north",
		priority =1
	},
 	actions = {
 		look = { type = action.say, args = {actor="dave", lines = {"prova"}}}
 	}	
}