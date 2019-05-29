local dt = 0.1
local sheet = "sprites.png"
local layer_dz = 0.001

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
	grating = {x=1, y=495, width = 50, height=16 }
}

engine.assets.models["arrow_up"] = {
    sheet = sheet,
    type = "sprite",
    ppu=1,
	animations = {
		{ name = "unselected", frames = { { duration = dt, quads = {{ id = s.arrow_up }}}}},
		{ name = "selected", frames = { { duration = dt, quads = {{ id = s.arrow_up }}}}}
	}
}

engine.assets.models["arrow_down"] = {
    sheet = sheet,
    type = "sprite",
    ppu=1,
	animations = {
		{ name = "unselected", frames = { { duration = dt, quads = {{ id = s.arrow_down }}}}},
		{ name = "selected", frames = { { duration = dt, quads = {{ id = s.arrow_down }}}}}
	}
}


engine.assets.models["dave"] = {
    sheet = sheet,
    type = "sprite",
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
		}}
			
	}
}

engine.assets.models["grating"] = {
    sheet = sheet,
    type = "sprite",
    ppu=1,
	animations = {
		{ name = "default", frames = { { duration = dt, quads = {{ id = s.grating }}}}},
	}
}

engine.assets.models["bushes"] = {
    sheet = sheet,
    type = "sprite",
    ppu=1,
	animations = {
		{ name = "default", frames = { { duration = dt, quads = {{ id = s.bushes }}}}},
	}
}