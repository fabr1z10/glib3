local dt = 0.1
local sheet = "sprites/sprites.png"

spritesheets["sprites"] = {
	cursor_hand = {x=1,y=1,width=15,height=15, anchor = {7,7} },
	cursor_talk = {x=17,y=1, width=16, height=16, anchor = {8,8}},
	cursor_walk = {x=34,y=1,width=11,height=16, anchor = {5, 8}},
	cursor_look = {x=46,y=1,width=12,height=9, anchor = {6,4}},
	graham_idle_body_front = {x=1, y=18, width=16, height=38, anchor = {9, 0}},
	graham_idle_head_front_1 = {x=19, y=29, width=8, height=9, anchor = {6, 0}},
	graham_idle_head_front_2 = {x=19, y=18, width=8, height=10, anchor = {5, 0}},
	graham_idle_head_front_3 = {x=19, y=39, width=10, height=10, anchor = {6, 0}},
	graham_walk_body_front_1 = {x=30, y=19, width=16, height=37, anchor = {9, 0}},
	graham_walk_body_front_2 = {x=47, y=18, width=16, height=38, anchor = {9, 0}},
	graham_walk_body_front_3 = {x=64, y=20, width=16, height=36, anchor = {9, 0}},
	graham_walk_body_front_4 = {x=82, y=19, width=16, height=37, anchor = {9, 0}},
	graham_walk_body_front_5 = {x=99, y=18, width=16, height=38, anchor = {9, 0}},
	graham_walk_body_front_6 = {x=116, y=20, width=16, height=36, anchor = {9, 0}},

	graham_idle_body_side = {x=129, y=58, width=9, height=37, anchor={4, 0}},
	graham_idle_head_side_1 = {x=60, y=2, width=9, height=10, anchor ={5, 0}},
	graham_idle_head_side_2 = {x=73, y=1, width=10, height=11, anchor ={6, 0}},
	graham_idle_head_side_3 = {x=84, y=1, width=8, height=11, anchor ={4, 0}},
	graham_walk_body_side_1 = {x=3, y=58, width=10, height=37, anchor = {4,0}},
	graham_walk_body_side_2 = {x=16, y=58, width=13, height=37, anchor = {6,0}},
	graham_walk_body_side_3 = {x=31, y=59, width=17, height=36, anchor = {8,0}},
	graham_walk_body_side_4 = {x=49, y=59, width=16, height=36, anchor = {10,0}},
	graham_walk_body_side_5 = {x=68, y=58, width=10, height=37, anchor = {4,0}},
	graham_walk_body_side_6 = {x=79, y=58, width=13, height=37, anchor = {6,0}},
	graham_walk_body_side_7 = {x=93, y=59, width=17, height=36, anchor = {8,0}},
	graham_walk_body_side_8 = {x=111, y=59, width=16, height=36, anchor = {10,0}},

	graham_idle_body_back = {x=134, y=18, width=16, height=38, anchor = {9, 0}},
	graham_idle_head_back_1 = {x=94, y=3, width=8, height=9, anchor= {4,0}},
	graham_idle_head_back_2 = {x=103, y=3, width=8, height=9, anchor= {4,0}},
	graham_idle_head_back_3 = {x=112, y=3, width=8, height=9, anchor= {5,0}},
	graham_walk_body_back_1 = {x=152, y=20, width=16, height=36, anchor = {9,0}},
	graham_walk_body_back_2 = {x=169, y=18, width=16, height=38, anchor = {9,0}},
	graham_walk_body_back_3 = {x=186, y=19, width=16, height=37, anchor = {9,0}},
	graham_walk_body_back_4 = {x=203, y=20, width=16, height=36, anchor = {9,0}},
	graham_walk_body_back_5 = {x=220, y=18, width=16, height=38, anchor = {9,0}},
	graham_walk_body_back_6 = {x=237, y=19, width=16, height=37, anchor = {9,0}},



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

local idle_e_offset = {0, 37}
local idle_n_offset = {0, 38}
local idle_s_offset = {0, 37}

models["graham"] = {
	sheet = sheet, 
	type = "sprite", 
	ppu=1, animations = {
		{ name = "idle_s", frames = { 
			{ duration = 10*dt, quads = {{ id = s.graham_idle_body_front }, {id = s.graham_idle_head_front_1, pos = idle_s_offset }}},
			{ duration = 10*dt, quads = {{ id = s.graham_idle_body_front }, {id = s.graham_idle_head_front_2, pos = idle_s_offset }}},
			{ duration = 10*dt, quads = {{ id = s.graham_idle_body_front }, {id = s.graham_idle_head_front_1, pos = idle_s_offset }}},
			{ duration = 10*dt, quads = {{ id = s.graham_idle_body_front }, {id = s.graham_idle_head_front_3, pos = idle_s_offset }}}
		}},
		{ name = "walk_s", frames = { 
			{ duration = dt, quads = {{ id = s.graham_walk_body_front_1 }, {id = s.graham_idle_head_front_1, pos=idle_s_offset }}},
			{ duration = dt, quads = {{ id = s.graham_walk_body_front_2 }, {id = s.graham_idle_head_front_1, pos=idle_s_offset }}},
			{ duration = dt, quads = {{ id = s.graham_walk_body_front_3 }, {id = s.graham_idle_head_front_1, pos=idle_s_offset }}},
			{ duration = dt, quads = {{ id = s.graham_walk_body_front_4 }, {id = s.graham_idle_head_front_1, pos=idle_s_offset }}},
			{ duration = dt, quads = {{ id = s.graham_walk_body_front_5 }, {id = s.graham_idle_head_front_1, pos=idle_s_offset }}},
			{ duration = dt, quads = {{ id = s.graham_walk_body_front_6 }, {id = s.graham_idle_head_front_1, pos=idle_s_offset }}}
		}},
		{ name = "idle_e", frames = { 
			{ duration = 10*dt, quads = {{ id = s.graham_idle_body_side }, {id = s.graham_idle_head_side_1, pos = idle_e_offset }}},
			{ duration = 10*dt, quads = {{ id = s.graham_idle_body_side }, {id = s.graham_idle_head_side_2, pos = idle_e_offset }}},
			{ duration = 10*dt, quads = {{ id = s.graham_idle_body_side }, {id = s.graham_idle_head_side_1, pos = idle_e_offset }}},
			{ duration = 10*dt, quads = {{ id = s.graham_idle_body_side }, {id = s.graham_idle_head_side_3, pos = idle_e_offset }}}
		}},
		{ name = "walk_e", frames = { 
			{ duration = dt, quads = {{ id = s.graham_walk_body_side_1 }, {id = s.graham_idle_head_side_1, pos = idle_e_offset }}},
			{ duration = dt, quads = {{ id = s.graham_walk_body_side_2 }, {id = s.graham_idle_head_side_1, pos = idle_e_offset }}},
			{ duration = dt, quads = {{ id = s.graham_walk_body_side_3 }, {id = s.graham_idle_head_side_1, pos = idle_e_offset }}},
			{ duration = dt, quads = {{ id = s.graham_walk_body_side_4 }, {id = s.graham_idle_head_side_1, pos = idle_e_offset }}},
			{ duration = dt, quads = {{ id = s.graham_walk_body_side_5 }, {id = s.graham_idle_head_side_1, pos = idle_e_offset }}},
			{ duration = dt, quads = {{ id = s.graham_walk_body_side_6 }, {id = s.graham_idle_head_side_1, pos = idle_e_offset }}},
			{ duration = dt, quads = {{ id = s.graham_walk_body_side_7 }, {id = s.graham_idle_head_side_1, pos = idle_e_offset }}},
			{ duration = dt, quads = {{ id = s.graham_walk_body_side_8 }, {id = s.graham_idle_head_side_1, pos = idle_e_offset }}}
		}},
		{ name = "idle_n", frames = { 
			{ duration = 10*dt, quads = {{ id = s.graham_idle_body_back }, {id = s.graham_idle_head_back_1, pos = idle_n_offset }}},
			{ duration = 10*dt, quads = {{ id = s.graham_idle_body_back }, {id = s.graham_idle_head_back_2, pos = idle_n_offset }}},
			{ duration = 10*dt, quads = {{ id = s.graham_idle_body_back }, {id = s.graham_idle_head_back_1, pos = idle_n_offset }}},
			{ duration = 10*dt, quads = {{ id = s.graham_idle_body_back }, {id = s.graham_idle_head_back_3, pos = idle_n_offset }}}
		}},
		{ name = "walk_n", frames = { 
			{ duration = dt, quads = {{ id = s.graham_walk_body_back_1 }, {id = s.graham_idle_head_back_1, pos = idle_n_offset }}},
			{ duration = dt, quads = {{ id = s.graham_walk_body_back_2 }, {id = s.graham_idle_head_back_1, pos = idle_n_offset }}},
			{ duration = dt, quads = {{ id = s.graham_walk_body_back_3 }, {id = s.graham_idle_head_back_1, pos = idle_n_offset }}},
			{ duration = dt, quads = {{ id = s.graham_walk_body_back_4 }, {id = s.graham_idle_head_back_1, pos = idle_n_offset }}},
			{ duration = dt, quads = {{ id = s.graham_walk_body_back_5 }, {id = s.graham_idle_head_back_1, pos = idle_n_offset }}},
			{ duration = dt, quads = {{ id = s.graham_walk_body_back_6 }, {id = s.graham_idle_head_back_1, pos = idle_n_offset }}}
		}}
	}


}


