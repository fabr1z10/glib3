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