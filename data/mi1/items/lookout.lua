-- the local objects
items["lookout.walkarea"] = {
	walkarea = {
		shape = { type = "poly", outline = {203,51,315,62,315,40,293,40,260,10,260,0,260,-20,234,-20,234,0,234,10,221,26,152,33,152,51}},
	},
	actions = {
		walk = function(x,y) return scumm.ui.walk {pos={x,y}} end
	}
}

items["lookout.stairs"] = {
	pos = {230, 0, 0},
	hotspot = {
		text = strings.objects.stairs,
		walk_to = {250, 0}, 
		dir = "south",
		size = {30, 10}
	},
	actions = {
		walk = { type = action.change_room, args = {room="village1"}}
	}
}

items["lookout.path"] = {
	pos = {294, 0, 0},
	hotspot = {
		text = strings.objects.path,
		walk_to = {320, 50}, 
		dir = "west",
		size = {26, 144},			
	},
	actions = {
		walk = { type = action.change_room, args = {room="meleemap"}}
	}
}


items["lookout.lookout"] = {
	pos = {114, 36, 0},
	hotspot = {
		text = strings.objects.lookout,
		walk_to = {134, 36},
		size = {20, 47},
		offset = {-10,0},
		dir = "west",
	},
	
	text_offset = {0, 60},
    text_color = {170, 170, 170, 255},
	applyDepth = true,
	character = {
		state = "idle",
		dir = "west",
		speed = 20
	},
	model ="lookout.lookout",
	actions = {
		talk = { type= scumm.action.start_dialogue, args = {dialogue = "lookout"}}
	}
}

items["lookout.fire"] = {
	pos = {126, 52, 0},
	model = "lookout.fire",
}