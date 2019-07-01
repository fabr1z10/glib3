local models = engine.assets.models

local s = {
	goomba_walk_1 = {x=112, y=0, width=16, height=16, anchor = {8, 0}},
	goomba_walk_2 = {x=128, y=0, width=16, height=16, anchor = {8, 0}},
}

local dt=0.1

models["goomba"] = {
    sheet = "smb1.png",
    type = "boxed_sprite",
    ppu=1,
	animations = {
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