items.village3 = {}

items["village3.archway"] = {
	text = strings.objects.archway,
	pos = {753, 11, 0},
	walk_to = {762, 16}, 
	face = "east",
	size = {23, 74},			
	actions = {
		walk = ms { {action.change_room, {id=1,room="village2"}}}
	}
}

items["village3.alley"] = {
	text = strings.objects.alley,
	pos = {581, 56, 0},
	walk_to = {605, 55}, 
	face = "north",
	size = {20, 30},			
	actions = {
		walk = ms { {action.change_room, {id=1,room="alley"}}}
	}
}

items["village3.shop_door"] = factory.door.create {
	name = "village3.shop_door",
	pos = {659, 17, -1},
	size = {20, 32},
	walk_to = {668, 22},
	face = "north",
	door_ref = "door_shop",
	model = "village3.shop_door",
	nextroom = "shop"
}

items["fester"]= {
tag="fester",
	text_color = {255, 85, 85, 255},
	text_offset = {0, 60},
	applydepth=true,
	model="fester",
	anim="idle_right"
}