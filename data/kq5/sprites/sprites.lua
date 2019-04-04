local dt = 0.1
local sheet = "sprites/sprites.png"

spritesheets["sprites"] = {
	cursor_hand = {x=1,y=1,width=15,height=15 },
	cursor_talk = {x=17,y=1, width=16, height=16},
	cursor_walk = {x=34,y=1,width=11,height=16},
	cursor_look = {x=46,y=1,width=12,height=9}
}

local s = spritesheets["sprites"]

models["cursor"] = { 
	sheet = sheet, 
	type = "sprite", 
	ppu=1, animations = {
		{ name = "hand", frames = { { duration = dt, quads = {{ id = s.cursor_hand }}}}},
		{ name = "talk", frames = { { duration = dt, quads = {{ id = s.cursor_talk }}}}},
		{ name = "walk", frames = { { duration = dt, quads = {{ id = s.cursor_walk }}}}},
		{ name = "look", frames = { { duration = dt, quads = {{ id = s.cursor_look }}}}}
	}
}


