engine.items["village3.walkarea"] = scumm.factory.walkarea {
	shape = { 
		type = "poly", 
	    outline = {406,49,425,49,436,63,494,63,494,42,594,42,594,71,600,71,638,23,745,23,752,17,770,17,770,10,762,10,775,0,374,0,396,22}
	},
	priority = 0,
	depth = { type="linear_y", values= {0, 1, 144, 0} },
	scale = { type="constant", value=0.3 }

}

engine.items["village3.archway"] = {
	pos = {753, 11, 0},
	hotspot = {	
		text = strings.objects.archway,
		walk_to = {762, 16}, 
		dir = "east",
		size = {23, 74}
	},	
	actions = {
		walk = { type = action.change_room, args ={room="village2"}}
	}
}

engine.items["village3.alley"] = {
	pos = {581, 56, 0},
	hotspot = {		
		text = strings.objects.alley,
		walk_to = {605, 55}, 
		dir = "north",
		size = {20, 30}
	},		
	actions = {
		walk = { type = action.change_room, args = {room="alley"}}
	}
}

engine.items["village3.shopkeeper"] = {
 	applyDepth = true,
 	model = "shop.shopkeeper",
	character = {
		state = "idle",
		dir = "west",
		speed = 50,
	},
 	text_offset = {0, 60},
    text_color = {255, 85, 255, 255},
}

scumm.factory.door {
	id = "village3.shop_door",
	pos = {659, 17, -1},
	size = {20, 32},
	walk_to = {668, 22},
	dir = "north",
	model = "village3.shop_door",
	variable = "door_shop",
	nextroom = "store",
}

scumm.factory.door {
	id = "village3.church_door",
	pos = {533, 32, -1},
	size = {22, 34},
	walk_to = {543, 39},
	dir = "north",
	model = "village3.church_door",
	variable = "door_church",
	nextroom = "church",
}

-- engine.items["fester"]= {
-- tag="fester",
-- 	text_color = {255, 85, 85, 255},
-- 	text_offset = {0, 60},
-- 	applydepth=true,
-- 	model="fester",
-- 	anim="idle_right"
-- }