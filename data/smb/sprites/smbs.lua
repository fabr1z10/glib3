local models = engine.assets.models

local s = {
	mario_idle = {x=0, y=0, width=16, height=16, anchor={8,0} },
	mario_idle_big = {x=80, y=16, width=16, height=32, anchor={8,0} },
	mario_walk_1 = {x=16, y=0, width=16, height=16, anchor={8,0} },
	mario_walk_2 = {x=32, y=0, width=16, height=16, anchor={8,0} },
	mario_walk_3 = {x=48, y=0, width=16, height=16, anchor={8,0} },
	mario_walk_big_1 = {x=96, y=16, width=16, height=32, anchor={8,0} },
	mario_walk_big_2 = {x=112, y=16, width=16, height=32, anchor={8,0} },
	mario_walk_big_3 = {x=128, y=16, width=16, height=32, anchor={8,0} },
	mario_jump = {x=80, y=0, width=16, height=16, anchor={8,0}},
	mario_jump_big = {x=144, y=16, width=16, height=32, anchor={8,0}},
	mario_duck_big = {x=96, y=128, width=16, height=32, anchor={8,0}},
	mario_die = {x = 96, y=0, width=16, height=16, anchor={8, 0}},
	brick = {x=240, y=0, width=16, height=16 },
	brick_piece = {x=64, y=16, width=16, height=16, anchor ={8,0}},
	mushroom = {x=48, y=16, width=16, height=16, anchor={8,0}},
	mushroom1up = {x=144, y=48, width=16, height=16, anchor={8,0}},
	bonus_brick_1 = {x=160, y=0, width=16, height=16 },
	bonus_brick_2 = {x=176, y=0, width=16, height=16 },
	bonus_brick_3 = {x=192, y=0, width=16, height=16 },
	bonus_brick_taken = {x=224, y=0, width=16, height=16},
	goomba_walk_1 = {x=112, y=0, width=16, height=16, anchor={8,0}},
	goomba_walk_2 = {x=128, y=0, width=16, height=16, anchor={8,0}},
	goomba_die = {x=144, y=0, width=16, height=16, anchor={8,0}}

}
local dt=0.1

models["mario"] = {
    sheet = "smb1.png",
    type = "boxed_sprite",
    ppu=1,
	animations = {
		{ name = "idle", box = {-8, 0, 8, 16}, frames = { {duration = dt, quads = {{ id = s.mario_idle }}}}},
		{ name = "walk", box = {-8, 0, 8, 16}, frames = {
			{ duration = dt, quads = {{ id = s.mario_walk_1 } }},
			{ duration = dt, quads = {{ id = s.mario_walk_2 } }},
			{ duration = dt, quads = {{ id = s.mario_walk_3 } }},
		}},
		{ name = "jump", box = {-8, 0, 8, 16}, frames = { { duration = dt, quads = {{ id = s.mario_jump }}}}},
		{ name = "die", frames = { { duration = dt, quads = {{ id = s.mario_die }}}}}

	}
}

models["goomba"] = {
    sheet = "smb1.png",
    type = "sprite",
    ppu=1,
	animations = {
		{ name = "walk", frames = {
			{ duration = dt, quads = {{ id = s.goomba_walk_1 } }},
			{ duration = dt, quads = {{ id = s.goomba_walk_2 } }},
		}},
		{ name = "jump", frames = {
			{ duration = dt, quads = {{ id = s.goomba_walk_1 } }},
			{ duration = dt, quads = {{ id = s.goomba_walk_2 } }},
		}},
		{ name = "die", frames = { { duration = dt, quads = {{ id = s.goomba_die }}}}}

	}

}

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