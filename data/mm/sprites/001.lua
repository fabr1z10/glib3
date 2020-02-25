local dt = 0.1
local sheet = "sprites.png"
local layer_dz = 0.001

local simple_sprite = function(frame)
	return {
    	sheet = sheet,
    	type = "sprite",
    	ppu=1,
		animations = {
			{ name = "default", frames = { { duration = dt, quads = {{ id = frame }}}}},
		}
	}

end

local s = {
	arrow_up = {x=300, y=0, width = 12, height=20 },
	arrow_down = {x = 300, y=0, width=12, height=20 },
	dave_head_s = {x = 2, y = 1, width = 22, height = 29, anchor = {11, 0}},
	dave_head_n = {x = 2, y = 32, width = 22, height = 24, anchor = {11, 0}},
	dave_head_e = {x = 2, y = 57, width = 23, height = 28, anchor = {7, 1}},
	dave_idle_n = {x=113, y=3, width=20, height=50, anchor={10,0}},
	dave_idle_s = {x=112, y=55, width=20, height=49, anchor={10,0}},
	dave_idle_e = {x=123, y=106, width=14, height=48, anchor={10,0}},
	dave_walk_n_1 = {x=28, y=1, width=18, height=52, anchor = {9,0}},
	dave_walk_n_2 = {x=49, y=3, width=20, height=50, anchor = {10,0}},
	dave_walk_n_3 = {x=71, y=1, width=18, height=52, anchor = {9,0}},
	dave_walk_n_4 = {x=91, y=3, width=20, height=50, anchor = {10,0}},
	dave_walk_s_1 = {x=29, y=55, width=18, height=49, anchor = {9,0}},
	dave_walk_s_2 = {x=49, y=57, width=20, height=47, anchor = {10,0}},
	dave_walk_s_3 = {x=70, y=55, width=18, height=49, anchor = {9,0}},
	dave_walk_s_4 = {x=90, y=57, width=20, height=47, anchor = {10,0}},
	dave_walk_e_1 = {x=29, y=107, width=21, height=47, anchor = {13, 0}},
	dave_walk_e_2 = {x=52, y=106, width=22, height=48, anchor = {12, 0}},	
	dave_walk_e_3 = {x=76, y=107, width=19, height=49, anchor = {7, 0}},
	dave_walk_e_4 = {x=97, y=105, width=23, height=49, anchor = {11, 0}},
	bushes = {x=1, y=476, width=53, height=18 },
	grating = {x=1, y=495, width = 50, height=16 },
	mat_closed = {x=53, y=505, width=88, height=6 },
	mat_open = {x=53, y=496, width=70, height=7 },
	frontdoor_key = {x=126, y=498, width = 11, height=4 },
	frontdoor_open = {x=1, y=397, width=40, height=78},
	frontdoor_close = {x=42, y=397, width=40, height=78},
	--frontdoor_open_in = {x=1, y=397, width=40, height=78},
	frontdoor_open_in = {x=28, y=284, width=25, height=112},
	frontdoor_close_in = {x=1, y=284, width=25, height=112},
	entr_cellar_door_open = {x = 97, y=307, width=42, height=89},
	entr_cellar_door_closed = {x = 54, y=307, width=42, height=89},

	flag_down = {x=56,y=476,width=13,height=6, anchor = {5,4}},
	flag_up = {x=56,y=483,width=8,height=12},
	gf_clock_1 = {x=83, y=426, width=16, height=49},
	gf_clock_2 = {x=100, y=426, width=16, height=49},

}

scumm.utils.mm2 ('arrow_up', sheet, { 'unselected', 'selected' }, { {s.arrow_up}, {s.arrow_up} })
scumm.utils.mm2 ('arrow_down', sheet, { 'unselected', 'selected' }, { {s.arrow_down}, {s.arrow_down} })


engine.assets.models["dave"] = {
    sheet = sheet,
    type = "sprite.model",
    ppu=1,
	animations = {
		{ name = "idle_s", frames = { { duration = dt, quads = {{ id = s.dave_idle_s}, { id=s.dave_head_s, pos = {0, 45} }}}}},
		{ name = "idle_n", frames = { { duration = dt, quads = {{ id = s.dave_idle_n}, { id=s.dave_head_n, pos = {0, 50} }}}}},
		{ name = "idle_e", frames = { { duration = dt, quads = {{ id = s.dave_idle_e}, { id=s.dave_head_e, pos = {-8, 46} }}}}},
		{ name = "walk_s", frames = { 
			{ duration = dt, quads = {{ id = s.dave_walk_s_1}, { id=s.dave_head_s, pos = {0, 45} }}},
			{ duration = dt, quads = {{ id = s.dave_walk_s_2}, { id=s.dave_head_s, pos = {0, 45} }}},
			{ duration = dt, quads = {{ id = s.dave_walk_s_3}, { id=s.dave_head_s, pos = {0, 45} }}},
			{ duration = dt, quads = {{ id = s.dave_walk_s_4}, { id=s.dave_head_s, pos = {0, 45} }}}
		}},
		{ name = "walk_n", frames = { 
			{ duration = dt, quads = {{ id = s.dave_walk_n_1}, { id=s.dave_head_n, pos = {0,52} }}},
			{ duration = dt, quads = {{ id = s.dave_walk_n_2}, { id=s.dave_head_n, pos = {0,50} }}},
			{ duration = dt, quads = {{ id = s.dave_walk_n_3}, { id=s.dave_head_n, pos = {0,52} }}},
			{ duration = dt, quads = {{ id = s.dave_walk_n_4}, { id=s.dave_head_n, pos = {0,50} }}}
		}},
		{ name = "walk_e", frames = { 
			{ duration = dt, quads = {{ id = s.dave_walk_e_1}, { id=s.dave_head_e, pos ={-5,45} }}},
			{ duration = dt, quads = {{ id = s.dave_walk_e_2}, { id=s.dave_head_e, pos ={-5,46} }}},
			{ duration = dt, quads = {{ id = s.dave_walk_e_3}, { id=s.dave_head_e, pos ={-5,45} }}},
			{ duration = dt, quads = {{ id = s.dave_walk_e_4}, { id=s.dave_head_e, pos ={-4,46} }}}
		}},
		{ name = "talk_s", frames = { { duration = dt, quads = {{ id = s.dave_idle_s}, { id=s.dave_head_s, pos = {0, 45} }}}}},
		{ name = "talk_n", frames = { { duration = dt, quads = {{ id = s.dave_idle_n}, { id=s.dave_head_n, pos = {0, 50} }}}}},
		{ name = "talk_e", frames = { { duration = dt, quads = {{ id = s.dave_idle_e}, { id=s.dave_head_e, pos = {-8, 46} }}}}},
			
	}
}

scumm.utils.mm2 ('front.door', sheet, { 'open', 'closed' }, { {s.frontdoor_open}, {s.frontdoor_close} })
scumm.utils.mm2 ('entrance.door.out', sheet, { 'open', 'closed' }, { {s.frontdoor_open_in}, {s.frontdoor_close_in} })
scumm.utils.mm2 ('entrance.cellar.door', sheet, { 'open', 'closed' }, { {s.entr_cellar_door_open}, {s.entr_cellar_door_closed} })
scumm.utils.mm2 ('door.mat', sheet, { 'open', 'closed' }, { {s.mat_open}, {s.mat_closed} })
scumm.utils.mm2 ('front.door.key', sheet, { 'default' }, { {s.frontdoor_key} })
scumm.utils.mm2 ('front.door.grating', sheet, { 'default' }, { {s.grating} })
scumm.utils.mm2 ('front.door.bush', sheet, { 'default' }, { {s.bushes} })
scumm.utils.mm2 ('front.door.flag', sheet, { 'up', 'down' }, { {s.flag_up}, {s.flag_down} })
scumm.utils.mm2 ('grandfather.clock', sheet, { 'default' }, { {s.gf_clock_1, s.gf_clock_2} }, 1)
