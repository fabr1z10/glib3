local models = engine.assets.models

local s = {
	goomba_walk_1 = {x=112, y=0, width=16, height=16, anchor = {8, 0}},
	goomba_walk_2 = {x=128, y=0, width=16, height=16, anchor = {8, 0}},
	fx_1_1 = {x=1,y=1,width=15,height=11, anchor={7,6}},
	fx_1_2 = {x=19,y=1,width=29,height=27,anchor={14,13}},
	fx_1_3 = {x=51,y=1,width=35,height=38, anchor={19,18}},
	fx_1_4 = {x=90,y=2,width=46,height=49,anchor={24,22}},
	fx_1_5 = {x=141,y=1,width=48,height=49,anchor={25,23}},
	fx_1_6 = {x=195,y=4,width=36,height=31,anchor={15,14}},
	fx_1_7 = {x=239,y=3,width=34,height=38, anchor={18,17}},
	fx_1_8 = {x=281,y=3,width=37, height=40, anchor={19,16}},
	fx_1_9 = {x=332, y=2, width=35, height=40, anchor={19,15}},
	fx_1_10 = {x=378, y=2, width=35, height=40, anchor={19,14}},
	fx_1_11 = {x=428, y=5, width=35, height=19, anchor={19,14}}	
}

local dt=0.1

models["goomba"] = {
    sheet = "smb1.png",
    type = "boxed_sprite",
    ppu=1,
	animations = {
		{ name = "idle", box = {-8, 0, 8, 16}, frames = {
		 	{duration = dt, quads = {{ id = s.goomba_walk_1 }}, boxes = {{-8,0,8,16}}},
		 	{duration = dt, quads = {{ id = s.goomba_walk_2 }}, boxes = {{-8,0,8,16}}},
		}},
		{ name = "walk", box = {-8, 0, 8, 16}, frames = {
		 	{duration = dt, quads = {{ id = s.goomba_walk_1 }}, boxes = {{-8,0,8,16}}},
		 	{duration = dt, quads = {{ id = s.goomba_walk_2 }}, boxes = {{-8,0,8,16}}},
		}},
		{ name = "jumpup", box = {-8, 0, 8, 16}, frames = {
		 	{duration = dt, quads = {{ id = s.goomba_walk_1 }}, boxes = {{-8,0,8,16}}},
		 	{duration = dt, quads = {{ id = s.goomba_walk_2 }}, boxes = {{-8,0,8,16}}},
		}},
		{ name = "jumpdown", box = {-8, 0, 8, 16}, frames = {
		 	{duration = dt, quads = {{ id = s.goomba_walk_1 }}, boxes = {{-8,0,8,16}}},
		 	{duration = dt, quads = {{ id = s.goomba_walk_2 }}, boxes = {{-8,0,8,16}}},
		}},

		--{ name = "die", frames = { { duration = dt, quads = {{ id = s.mario_die }}}}}
	}
}

models["fx_1"] = {
    sheet = "fx.png",
    type = "sprite",
    ppu=1,
	animations = {
		{ name = "default", frames = {
		 	{duration = dt, quads = {{ id = s.fx_1_1 }}},
		 	{duration = dt, quads = {{ id = s.fx_1_2 }}},
		 	{duration = dt, quads = {{ id = s.fx_1_3 }}},
		 	{duration = dt, quads = {{ id = s.fx_1_4 }}},
		 	{duration = dt, quads = {{ id = s.fx_1_5 }}},
		 	{duration = dt, quads = {{ id = s.fx_1_6 }}},
		 	{duration = dt, quads = {{ id = s.fx_1_7 }}},
		 	{duration = dt, quads = {{ id = s.fx_1_8 }}},
		 	{duration = dt, quads = {{ id = s.fx_1_9 }}},
		 	{duration = dt, quads = {{ id = s.fx_1_10 }}},
		 	{duration = dt, quads = {{ id = s.fx_1_11 }}},
		}},
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