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
	mario_slide = {x=176,y=64,width=16,height=16,anchor={8,0}},
	brick = {x=240, y=0, width=16, height=16 },
	brick_piece = {x=64, y=16, width=16, height=16},
	mushroom = {x=48, y=16, width=16, height=16, anchor={8,0}},
	mushroom1up = {x=144, y=48, width=16, height=16, anchor={8,0}},
	starman = {x=128, y=48, width=16, height=16, anchor= {8,0}},
	bonus_brick_1 = {x=160, y=0, width=16, height=16 },
	bonus_brick_2 = {x=176, y=0, width=16, height=16 },
	bonus_brick_3 = {x=192, y=0, width=16, height=16 },
	bonus_brick_taken = {x=224, y=0, width=16, height=16},
	goomba_walk_1 = {x=112, y=0, width=16, height=16, anchor={8,0}},
	goomba_walk_2 = {x=128, y=0, width=16, height=16, anchor={8,0}},
	goomba_die = {x=144, y=0, width=16, height=16, anchor={8,0}},
	koopa_walk_1 = {x=0, y=16, width=16, height=32, anchor={8,0}},
	koopa_walk_2 = {x=16, y=16, width=16, height=32, anchor={8,0}},
	koopa_hide_1 = {x=32, y=32, width=16, height=16, anchor={8,0}},
	koopa_hide_2 = {x=32, y=16, width=16, height=16, anchor={8,0}},
	pickup_coin_1 = {x=128,y=64,width=16,height=16,anchor={0,0}},
	pickup_coin_2 = {x=144,y=64,width=16,height=16,anchor={0,0}},
	pickup_coin_3 = {x=160,y=64,width=16,height=16,anchor={0,0}},
	flying_coin_1 = {x=160,y=16,width=16,height=16,anchor={8,0}},
	flying_coin_2 = {x=176,y=16,width=16,height=16,anchor={8,0}},
	flying_coin_3 = {x=192,y=16,width=16,height=16,anchor={8,0}},
	flying_coin_4 = {x=208,y=16,width=16,height=16,anchor={8,0}},
	score_100 = {x=0, y=80, width=16,height=16, anchor={8,0}},
	empty = {x=176,y=80,width=16,height=16,anchor={0,0}},
	end_level_flag = {x=224,y=64,width=16,height=16}


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
		{ name = "die", frames = { { duration = dt, quads = {{ id = s.mario_die }}}}},
		{ name = "slide", frames = { { duration = dt, quads = {{ id = s.mario_slide }}}}},
		{ name = "idle_big", box = {-8, 0, 8, 24}, frames = { {duration = dt, quads = {{ id = s.mario_idle_big }}}}},
		{ name = "walk_big", box = {-8, 0, 8, 24}, frames = {
			{ duration = dt, quads = {{ id = s.mario_walk_big_1 } }},
			{ duration = dt, quads = {{ id = s.mario_walk_big_2 } }},
			{ duration = dt, quads = {{ id = s.mario_walk_big_3 } }},
		}},
		{ name = "jump_big", box = {-8, 0, 8, 24}, frames = { { duration = dt, quads = {{ id = s.mario_jump_big }}}}},

	}
}

models["goomba"] = {
    sheet = "smb1.png",
    type = "boxed_sprite",
    ppu=1,
	animations = {
		{ name = "walk", box={-8,0,8,16}, frames = {
			{ duration = dt, quads = {{ id = s.goomba_walk_1 } }},
			{ duration = dt, quads = {{ id = s.goomba_walk_2 } }},
		}},
		{ name = "jump", box={-8,0,8,16}, frames = {
			{ duration = dt, quads = {{ id = s.goomba_walk_1 } }},
			{ duration = dt, quads = {{ id = s.goomba_walk_2 } }},
		}},
		{ name = "die", box={-8,0,8,16}, frames = { 
			{ duration = dt, quads = {{ id = s.goomba_die }}}
		}}
	}
}

models["koopa"] = {
    sheet = "smb1.png",
    type = "boxed_sprite",
    ppu=1,
	animations = {
		{ name = "walk", box={-8,0,8,24}, frames = {
			{ duration = dt, quads = {{ id = s.koopa_walk_1 } }},
			{ duration = dt, quads = {{ id = s.koopa_walk_2 } }},
		}},
		{ name = "jump", box={-8,0,8,24}, frames = {
			{ duration = dt, quads = {{ id = s.koopa_walk_1 } }},
			{ duration = dt, quads = {{ id = s.koopa_walk_2 } }},
		}},
		{ name = "hide", box={-8,0,8,16}, frames = { 
			{ duration = dt, quads = {{ id = s.koopa_hide_1 }}}
		}},
		{ name = "hide_blink", box={-8,0,8,16}, frames = { 
			{ duration = dt, quads = {{ id = s.koopa_hide_1 }}},
			{ duration = dt, quads = {{ id = s.koopa_hide_2 }}},
		}}
	}
}

models["basicbrick"] = glib.basic_model ("smb1.png", s.brick)
models["score_100"] = glib.basic_model ("smb1.png", s.score_100)
models["brickpiece"] = glib.basic_model ("smb1.png", s.brick_piece)
models["end_level_flag"] = glib.basic_model ("smb1.png", s.end_level_flag)


models["mushroom"] = {
    sheet = "smb1.png",
    type = "boxed_sprite",
    ppu=1,
	animations = {
		{ name = "walk", box = {-8, 0, 8, 16}, frames = {
			{ duration = dt, quads = {{ id = s.mushroom } }},
		}},
	}
}

models["mushroom1up"] = {
    sheet = "smb1.png",
    type = "boxed_sprite",
    ppu=1,
	animations = {
		{ name = "walk", box = {-8, 0, 8, 16}, frames = {
			{ duration = dt, quads = {{ id = s.mushroom1up } }},
		}},
	}
}

models["starman"] = {
    sheet = "smb1.png",
    type = "boxed_sprite",
    ppu=1,
	animations = {
		{ name = "walk", box = {-8, 0, 8, 16}, frames = {
			{ duration = dt, quads = {{ id = s.starman } }},
		}},
	}
}
models["bonusbrick"] = {
    sheet = "smb1.png",
    type = "sprite",
    ppu=1,
	animations = {
		{ name = "default", frames = {
			{ duration = dt, quads = {{ id = s.bonus_brick_1 } }},
			{ duration = dt, quads = {{ id = s.bonus_brick_2 } }},
			{ duration = dt, quads = {{ id = s.bonus_brick_3 } }},
			{ duration = dt, quads = {{ id = s.bonus_brick_2 } }},			
		}},
		{ name = "taken", frames = {
			{ duration = dt, quads = {{ id = s.bonus_brick_taken } }},
		}},

	}
}

models["bonusbrick2"] = {
    sheet = "smb1.png",
    type = "sprite",
    ppu=1,
	animations = {
		{ name = "default", frames = {
			{ duration = dt, quads = {{ id = s.brick } }},
		}},
		{ name = "taken", frames = {
			{ duration = dt, quads = {{ id = s.bonus_brick_taken } }},
		}},

	}
}

models["hiddenbrick"] = {
    sheet = "smb1.png",
    type = "sprite",
    ppu=1,
	animations = {
		{ name = "default", frames = {
			{ duration = dt, quads = {{ id = s.empty } }},
		}},
		{ name = "taken", frames = {
			{ duration = dt, quads = {{ id = s.bonus_brick_taken } }},
		}},

	}
}



models["pickup_coin"] = {
    sheet = "smb1.png",
    type = "boxed_sprite",
    ppu=1,
	animations = {
		{ name = "default", box = {-8, 0, 8, 16}, frames = {
			{ duration = dt, quads = {{ id = s.pickup_coin_1 } }},
			{ duration = dt, quads = {{ id = s.pickup_coin_2 } }},
			{ duration = dt, quads = {{ id = s.pickup_coin_3 } }},
			{ duration = dt, quads = {{ id = s.pickup_coin_2 } }},
		}},
	}
}

models["flying_coin"] = {
    sheet = "smb1.png",
    type = "sprite",
    ppu=1,
	animations = {
		{ name = "default", frames = {
			{ duration = dt, quads = {{ id = s.flying_coin_1 } }},
			{ duration = dt, quads = {{ id = s.flying_coin_2 } }},
			{ duration = dt, quads = {{ id = s.flying_coin_3 } }},
			{ duration = dt, quads = {{ id = s.flying_coin_2 } }},
		}},
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