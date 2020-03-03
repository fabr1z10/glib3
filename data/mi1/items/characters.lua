local text_offset = {0, 60}
local speed = 500
local normal_speed = 100

engine.items["guybrush"] = {
	type = 'char',
	model = 'guybrush',
	state = 'idle',
	speed = speed,
	text_color = {255, 255, 255, 255},
	text_offset = text_offset,
	collide = {
		size = {10, 1},
		offset = {-5, 0},
		tag = 1,
		flag = 1,
		mask = 2
	}
}

engine.items["lookout.lookout"] = {
	type = 'char',
	model ="lookout.lookout",
	tag =true,
	text_offset = {0, 60},
    text_color = {170, 170, 170, 255},
	state = 'idle',
	dir = 'west',
	speed = normal_speed,
	pos = {114, 36, 0},
	hotspot = {
		text = strings.objects.lookout,
		walk_to = {134, 36},
		size = {20, 47},
		offset = {-10,0},
		dir = "west",
	},
	actions = {
		look = { type = scumm.action.say, args = { tag="player", lines = {strings.dialogues.lookout[50]} }},
		talk = { type= scumm.action.start_dialogue, args = {dialogue = "lookout"}}
	}
}

engine.items["scummbar.cook"] = {
	type = 'char',
	tag=true,
 	model = 'cook',
 	state = 'idle',
 	speed = normal_speed,
 	text_color = mi.data.cook_text_color,
 	text_offset = {0, 60}
 }



engine.items['mancomb.guybrush'] = {
	tag = 'player',
	type = 'mockchar',
	pos = {200, 100, 0},
	text_color = {255, 255, 255, 255},
	text_offset = {0, 0}
}


engine.items['loompirate.guybrush'] = {
	tag = 'player',
	type = 'mockchar',
	pos = {20, 100, 0},
	text_color = {255, 255, 255, 255},
	text_offset = {0, 0}
}

engine.items['estevan.guybrush'] = {
	tag = 'player',
	type = 'mockchar',
	pos = {20, 100, 0},
	text_color = {255, 255, 255, 255},
	text_offset = {0, 0}
}

engine.items["scummbar.ilp1"] = {
	type = 'char',
	model = 'scummbar.ilp1', 	
	tag = true,		
	pos = {376, 11, 0.95},
	text_color = {85, 85, 255, 255},
	text_offset = {0, 60},
	state = 'idle',
	speed = 0,
	dir='e'
}

engine.items["scummbar.ilp2"] = {
	type = 'char',
	model = 'scummbar.ilp2', 	
	tag = true,		
	pos = {413, 11, 0.95},
	text_color = {255, 255, 85, 255},
	text_offset = {0, 60},
	state= 'idle',
	dir = 'east',
	speed = 0
}

engine.items["scummbar.ilp3"] = {
	type = 'char',
	model = 'scummbar.ilp3', 	
	tag = true,			
	pos = {444, 18, 0.95},
	text_color = {255, 85, 255, 255},
	text_offset = {0, 60},
	state = "idle",
	dir = "east",
	speed = 0
}