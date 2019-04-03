items["village3.archway"] = {
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

items["village3.alley"] = {
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

items["village3.shopkeeper"] = {
 	pos = {669, 15, 0},
 	applydepth = true,
 	model = "shop.shopkeeper",
	character = {
		state = "idle",
		dir = "east"
	},
 }

scumm.factory.door {
	id = "village3.shop_door",
	pos = {659, 17, -1},
	size = {20, 32},
	walk_to = {668, 22},
	dir = "north",
	model = "village3.shop_door",
	variable = "door_shop",
	nextroom = "shop",
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

-- items["fester"]= {
-- tag="fester",
-- 	text_color = {255, 85, 85, 255},
-- 	text_offset = {0, 60},
-- 	applydepth=true,
-- 	model="fester",
-- 	anim="idle_right"
-- }