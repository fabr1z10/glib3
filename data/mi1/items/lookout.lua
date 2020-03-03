-- the local objects
engine.items['lookout.walkarea'] = { 
	type = 'walkarea',
	shape = { 
		type = 'poly', 
		outline = {203,51,315,62,315,40,293,40,260,10,260,0,260,-20,234,-20,234,0,234,10,221,26,152,33,152,51}
	},
	depth = { type = 'linear_y', values= {0, 1, 144, 0} },	
	priority = 0
}

engine.items["lookout.stairs"] = {
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

engine.items["lookout.path"] = {
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


engine.items["lookout.lookout"] = {
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
		look = { type = scumm.action.say, args = { actor="guybrush", lines = {strings.dialogues.lookout[50]} }},
		talk = { type= scumm.action.start_dialogue, args = {dialogue = "lookout"}}
	}
}

engine.items["lookout.fire"] = {
	type ='object',
	pos = {126, 52, 0},
	model = "lookout.fire",
}