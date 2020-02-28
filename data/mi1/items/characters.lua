local text_offset = {0, 60}
local speed = 500

engine.items["guybrush"] = {
	type = 'char',
	model = 'guybrush',
	state = 'idle',
	speed = speed,
	text_color = {255, 255, 255, 255},
	text_offset = text_offset,
}

engine.items['mancomb.guybrush'] = {
	tag = 'player',
	type = 'mockchar',
	pos = {150, 100, 0},
	text_color = {255, 255, 255, 255},
	text_offset = {0, 0}
}


