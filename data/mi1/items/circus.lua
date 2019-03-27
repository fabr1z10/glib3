items["circus.wayout"] = {
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

-- items["circus.explosion"] = {
-- 	model ="circus.explosion",
-- 	anim="default"
-- }
-- items["circus.flyingguybrush"] = {
-- 	model ="circus.flyingguy",
-- 	anim="default"
-- }

items["circus.purpleclown"] = {
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
		dir = "east"
	}
 }

items["circus.greenclown"] = {
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
		dir = "west"
	}
}