engine.items["village3.walkarea"] = {
	type = 'walkarea',
	shape = { 
		type = "poly", 
	    outline = {406,49,425,49,436,63,494,63,494,42,594,42,594,71,600,71,638,23,745,23,752,17,770,17,770,10,762,10,775,0,374,0,396,22}
	},
	priority = 0,
	depth = { type="linear_y", values= {0, 1, 144, 0} },
	scale = { type="constant", value=0.3 }

}

engine.items["village3.archway"] = {
	type = 'object',
	pos = {753, 11, 0},
	hotspot = {	
		text = strings.objects.archway,
		walk_to = mi.rooms.village3.to_village2, 
		dir = "east",
		size = {23, 74}
	},	
	actions = {
		walk = scumm.script.changeroom{ room='village2', pos = mi.rooms.village2.to_village3, dir = 's'}
	}
}

engine.items["village3.alley"] = {
	type = 'object',
	pos = {581, 56, 0},
	hotspot = {		
		text = strings.objects.alley,
		walk_to = {605, 55}, 
		dir = "north",
		size = {20, 30}
	},		
	actions = {
		walk = scumm.script.changeroom{ room='alley', pos = mi.rooms.alley.to_village3, dir = 'e'}
	}
}

engine.items["village3.jail"] = {
	pos = {455, 65, 0},
	hotspot = {		
		text = strings.objects.doorway,
		walk_to = {465, 65}, 
		dir = "north",
		size = {19, 22}
	},		
	actions = {
		walk = { type = action.change_room, args = {room="jail"}}
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

engine.items['village3.door.shop'] = make_door {
	tag = 'village3.door.shop',
	model = 'village3.shop_door',
 	pos = {659, 17, -1},
 	size = {20, 32},
 	walk_to = mi.rooms.village3.to_shop,
 	dir = 'n',
	var = 'door_shop',
	go_to = { room = 'store', pos = mi.rooms.store.to_village3, dir = 'e' }
}

-- scumm.factory.door {
-- 	id = "village3.shop_door",
-- 	pos = {659, 17, -1},
-- 	size = {20, 32},
-- 	walk_to = {668, 22},
-- 	dir = "north",
-- 	model = "village3.shop_door",
-- 	variable = "door_shop",
-- 	nextroom = "store",
-- }

-- scumm.factory.door {
-- 	id = "village3.church_door",
-- 	pos = {533, 32, -1},
-- 	size = {22, 34},
-- 	walk_to = {543, 39},
-- 	dir = "north",
-- 	model = "village3.church_door",
-- 	variable = "door_church",
-- 	nextroom = "church",
-- 	open = {}
-- }

