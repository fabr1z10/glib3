local models = engine.assets.models

local s = {
	ryu_idle_1 = {x=3, y=2, width=57, height=103, anchor = {25, 4}},
	ryu_idle_2 = {x=64, y=5, width=57, height=101, anchor = {25, 4}},
	ryu_idle_3 = {x=125, y=4, width=57, height=103, anchor = {25, 4}},
	ryu_idle_4 = {x=189, y=2, width=57, height=106, anchor = {25, 4}},
	ryu_idle_5 = {x=252, y=3, width=57, height=106, anchor = {25, 4}},
	ryu_idle_6 = {x=313, y=6, width=57, height=104, anchor = {25, 4}},
	ryu_walk_1 = {x=372, y=3, width=50, height=107, anchor = {20, 4}},
	ryu_walk_2 = {x=425, y=2, width=50, height=108, anchor = {18, 5}},
	ryu_walk_3 = {x=2,y=109,width=50,height=108, anchor={18, 5}},
	ryu_walk_4 = {x=57, y=115, width=56, height=102, anchor={20, 5} },
	ryu_walk_5 = {x=116, y=114, width=56, height=103, anchor = {26, 5}},
	ryu_walk_6 = {x=175, y=112, width=65, height=105, anchor = {35, 5}},
	ryu_walk_7 = {x=243,y=111,width=59,height=108, anchor={30, 5}},
	ryu_walk_8 = {x=307, y=114, width=52, height=105, anchor={23, 1} },
	ryu_hit_1 = {x=366, y=115, width=79, height=104, anchor={31, 4}},
	ryu_hit_2 = {x=449, y=117, width=60, height=102, anchor={6, 4}},
	ryu_hit_3 = {x=3, y=221, width=90, height=106, anchor={8, 4}},
	ryu_hit_4 = {x=99, y=218, width=85, height=109, anchor ={4, 4}},
	ryu_hit_5 = {x=189, y=227, width=77, height=100, anchor = {5, 4}},
	ryu_hit_6 = {x=269, y=224, width=58, height=104, anchor = {18, 7}},
	-- ryu_jump_begin_1 = {x=332, y=222, width=54, height=124, anchor = {23, 3}},
	-- ryu_jump_begin_2 = {x=388, y=224, width=51, height=105, anchor = {19, 7}},
	-- ryu_jump_begin_3 = {x=443, y=225, width=58, height=80, anchor= {21, 25}},
	-- ryu_jump_begin_4 = {x=4, y=333, width=56, height=72, anchor ={21, 30}},
	-- ryu_jump_begin_5 = {x=65, y=333, width=53, height=67, anchor = {24, 34}},
	-- ryu_jump_end_1 = {x=123, y=329, width=56, height=71, anchor ={21, 34}},
	-- ryu_jump_end_2 = {x=183, y=331, width=58, height=88, anchor = {21, 23}},
	-- ryu_jump_end_3 = {x=247, y=331, width=51, height=115, anchor = {19, 8}},
	-- ryu_jump_end_4 = {x=303, y=349, width=51, height=126, anchor = {23, 5}}
	ryu_jump_begin_1 = {x=332, y=222, width=54, height=124, anchor = {23, 4}},
	ryu_jump_begin_2 = {x=388, y=224, width=51, height=105, anchor = {19, 4}},
	ryu_jump_begin_3 = {x=443, y=225, width=58, height=80, anchor= {21, 4}},
	ryu_jump_begin_4 = {x=4, y=333, width=56, height=72, anchor ={21, 4}},
	ryu_jump_begin_5 = {x=65, y=333, width=53, height=67, anchor = {24, 4}},
	ryu_jump_end_1 = {x=123, y=329, width=56, height=71, anchor ={21, 4}},
	ryu_jump_end_2 = {x=183, y=331, width=58, height=88, anchor = {21, 4}},
	ryu_jump_end_3 = {x=247, y=331, width=51, height=115, anchor = {19, 4}},
	ryu_jump_end_4 = {x=303, y=349, width=51, height=126, anchor = {23, 4}}
}

local dt=0.1
models["ryu"] = {
    sheet = "pfo.png",
    type = "boxed_sprite",
    ppu=1,
	animations = {
		{ name = "idle", frames = { 
			-- boxes are provided as (xmin, ymin, xmax, ymax)
			{duration = dt, quads = {{ id = s.ryu_idle_1 }}, boxes = { {-25, 0, 26, 92 }}},
			{duration = dt, quads = {{ id = s.ryu_idle_2 }}, boxes = { {-25, 0, 26, 90 }}},
			{duration = dt, quads = {{ id = s.ryu_idle_3 }}, boxes = { {-25, 0, 26, 92 }}},
			{duration = dt, quads = {{ id = s.ryu_idle_4 }}, boxes = { {-25, 0, 26, 95 }}},
			{duration = dt, quads = {{ id = s.ryu_idle_5 }}, boxes = { {-25, 0, 26, 96 }}},
			{duration = dt, quads = {{ id = s.ryu_idle_6 }}, boxes = { {-25, 0, 26, 93 }}},
		}},
		-- { name = "walk", frames = {
		-- 	{duration = dt, quads = {{ id = s.ryu_walk_1 }}},
		-- 	{duration = dt, quads = {{ id = s.ryu_walk_2 }}},
		-- 	{duration = dt, quads = {{ id = s.ryu_walk_3 }}},
		-- 	{duration = dt, quads = {{ id = s.ryu_walk_4 }}},
		-- 	{duration = dt, quads = {{ id = s.ryu_walk_5 }}},
		-- 	{duration = dt, quads = {{ id = s.ryu_walk_6 }}},
		-- 	{duration = dt, quads = {{ id = s.ryu_walk_7 }}},
		-- 	{duration = dt, quads = {{ id = s.ryu_walk_8 }}},
		-- }},
		-- { name = "lowkick", frames = {
		-- 	{duration = 0.5*dt, quads = {{ id = s.ryu_hit_1 }}},
		-- 	{duration = 0.5*dt, quads = {{ id = s.ryu_hit_2 }}},
		-- 	{duration = dt, quads = {{ id = s.ryu_hit_3 }}s},
		-- 	{duration = 0.5*dt, quads = {{ id = s.ryu_hit_4 }}},
		-- 	{duration = 0.5*dt, quads = {{ id = s.ryu_hit_5 }}},
		-- 	{duration = 0.5*dt, quads = {{ id = s.ryu_hit_6 }}},
		-- }},
  --       { name = "jumpup", loop = false, frames = { 
		-- 	{duration = dt, quads = {{ id = s.ryu_jump_begin_1 }}},
		-- 	{duration = dt, quads = {{ id = s.ryu_jump_begin_2 }}},
		-- 	{duration = dt, quads = {{ id = s.ryu_jump_begin_3 }}},
		-- 	{duration = dt, quads = {{ id = s.ryu_jump_begin_4 }}},
		-- 	{duration = dt, quads = {{ id = s.ryu_jump_begin_5 }}},
		-- }},
  --       { name = "jumpdown", loop = false, frames = { 
		-- 	{duration = dt, quads = {{ id = s.ryu_jump_end_1 }}},
		-- 	{duration = dt, quads = {{ id = s.ryu_jump_end_2 }}},
		-- 	{duration = dt, quads = {{ id = s.ryu_jump_end_3 }}},
		-- 	{duration = dt, quads = {{ id = s.ryu_jump_end_4 }}},
		-- }},
		--{ name = "die", frames = { { duration = dt, quads = {{ id = s.mario_die }}}}}
	}
}

-- models["goomba"] = {
--     sheet = "smb1.png",
--     type = "sprite",
--     ppu=1,
-- 	animations = {
-- 		{ name = "walk", frames = {
-- 			{ duration = dt, quads = {{ id = s.goomba_walk_1 } }},
-- 			{ duration = dt, quads = {{ id = s.goomba_walk_2 } }},
-- 		}},
-- 		{ name = "jump", frames = {
-- 			{ duration = dt, quads = {{ id = s.goomba_walk_1 } }},
-- 			{ duration = dt, quads = {{ id = s.goomba_walk_2 } }},
-- 		}},
-- 		{ name = "die", frames = { { duration = dt, quads = {{ id = s.goomba_die }}}}}

-- 	}

-- }

-- models["supermario"] = {

	
-- }
-- 		{
-- 			name = "large.nofire.idle",
-- 			frames = {
-- 				{ duration = dt, quads = {{ id = s.mario_idle_big }}}
-- 			}
-- 		},
-- 		{
-- 			name = "large.nofire.walk",
-- 			frames = {
-- 				{ duration = dt, quads = {{ id = s.mario_walk_big_1 } }},
-- 				{ duration = dt, quads = {{ id = s.mario_walk_big_2 } }},
-- 				{ duration = dt, quads = {{ id = s.mario_walk_big_3 } }},
-- 			}
-- 		},
-- 		{
-- 			name = "large.nofire.jump",
-- 			frames = {
-- 				{ duration = dt, quads = {{ id = s.mario_jump_big }}},
-- 			}
-- 		},
-- 		{
-- 			name = "large.nofire.duck",
-- 			frames = {
-- 				{ duration = dt, quads = {{ id = s.mario_duck_big }}},
-- 			}
-- 		},

-- 	}
-- }