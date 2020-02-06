engine.items["circus.walkarea"] = scumm.factory.walkarea {
	shape = { type = "poly", outline = {0,34,368,34,368,0,0,0}},
	depth = { type="linear_y", values= {0, 1, 144, 0} },
	scale = { type="patchwise", rects = {
    	{ pos = {0, 0}, size={368, 20}, type="constant", value = 1},
    	{ pos = {0, 20}, size={368, 14}, type="linear_y", values={20,1,34,0.57}}
		
	}},
	priority = 0
}


engine.items["circus.wayout"] = {
	pos = {280, 32, 0},
	hotspot = {
		text = strings.objects.outside,
		size = {16, 144},			
		walk_to = {280, 32}, 
		dir = "east",
	},
	actions = {
		walk = { { type = action.change_room, args = {room="clearing"}}}
	}
}

engine.items["circus.explosion"] = { model ="circus.explosion" }
engine.items["circus.flyingguybrush"] = { model ="circus.flyingguy" }

engine.items["circus.purpleclown"] = {
 	pos = {37,34,0},
 	hotspot = {
 		text = strings.objects.fettuccini,
 		size = {18,30},
 		offset = {-9,0},
 		walk_to = {178, 9} ,
	 	dir = "south",
 	},    
    text_color = {255, 85, 255, 255},
 	text_offset = {0,60},
 	applydepth = true,
 	model = "fettuccini.purple",
	character = {
		state = "idle",
		dir = "east",
		speed=500
	},
	actions = {}
}

engine.items["circus.greenclown"] = {
	pos = {51,34,0},
	hotspot = {
		text = strings.objects.fettuccini,
	 	size= {18,30},
	 	offset ={-9,0},
	 	walk_to = {178, 9},
	 	dir = "south",
	},
 	text_color = {85, 255, 85, 255},
 	text_offset={0,60},
 	applydepth = true,
 	model = "fettuccini.green",
	character = {
		state = "idle",
		dir = "west",
		speed =500
	},
	actions = {}

}

engine.items["circus.fire"] = {
 	pos = {14, 70, -1},
	model = "circus.fire",
}
