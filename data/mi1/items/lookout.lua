-- the local objects
items["lookout.stairs"] = {
	pos = {230, 0, 0},
	hotspot = {
		text = strings.objects.stairs,
		walk_to = {250, 0}, 
		dir = "south",
		size = {30, 10}
	},
	actions = {
		walk = { type = action.change_room, args = {id=1}}
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
		walk_to = {134, 36},
		size = {20, 47},
		offset = {-10,0},
		dir = "west",
	},
	
	text_offset = {0, 60},
    text_color = {170, 170, 170, 255},
	text = strings.objects.lookout,
	applyDepth = true,
	character = {
		state = "idle",
		dir = "west"
	},
	model ="lookout",
	anim ="idle_right",	
	actions = {
		talk = { type= scumm.start_dialogue, args = {dialogue = "lookout"}}
	}
}

items["lookout.fire"] = {
	pos = {126, 52, -1},
	model = "fire",
    --anim = "default"
}