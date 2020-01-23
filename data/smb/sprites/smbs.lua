local models = engine.assets.models

local s = {
	mario_idle = {x=0, y=0, width=16, height=16, anchor={8,0} },
	mario_idle_big = {x=80, y=16, width=16, height=32, anchor={8,0} },
	mario_idle_fire = {x=0, y=112, width=16, height=32, anchor={8,0}},
	mario_walk_1 = {x=16, y=0, width=16, height=16, anchor={8,0} },
	mario_walk_2 = {x=32, y=0, width=16, height=16, anchor={8,0} },
	mario_walk_3 = {x=48, y=0, width=16, height=16, anchor={8,0} },
	mario_walk_big_1 = {x=96, y=16, width=16, height=32, anchor={8,0} },
	mario_walk_big_2 = {x=112, y=16, width=16, height=32, anchor={8,0} },
	mario_walk_big_3 = {x=128, y=16, width=16, height=32, anchor={8,0} },
	mario_walk_fire_1 = {x=16, y=112, width=16, height=32, anchor={8,0} },
	mario_walk_fire_2 = {x=32, y=112, width=16, height=32, anchor={8,0} },
	mario_walk_fire_3 = {x=48, y=112, width=16, height=32, anchor={8,0} },
	mario_jump = {x=80, y=0, width=16, height=16, anchor={8,0}},
	mario_jump_big = {x=144, y=16, width=16, height=32, anchor={8,0}},
	mario_jump_fire = {x=64, y=128, width=16, height=32, anchor={8,0}},
	mario_duck_big = {x=96, y=128, width=16, height=32, anchor={8,0}},
	mario_die = {x = 96, y=0, width=16, height=16, anchor={8, 0}},
	mario_slide = {x=176,y=64,width=16,height=16,anchor={8,0}},
	mario_slide_big = {x=192,y=64, width=16, height=32, anchor= {8,0}},
	brick = {x=240, y=0, width=16, height=16 },
	brick_piece = {x=64, y=16, width=16, height=16},
	brick_dark = {x=160,y=48,width=16,height=16},
	brick_piece_dark = {x=224, y=80, width=16, height=16},
	mushroom = {x=48, y=16, width=16, height=16, anchor={8,0}},
	mushroom1up = {x=144, y=48, width=16, height=16, anchor={8,0}},
	flower_1 = {x=176,y=96,width=16,height=16,anchor={8,0}},
	flower_2 = {x=192,y=96,width=16,height=16,anchor={8,0}},
	flower_3 = {x=208,y=96,width=16,height=16,anchor={8,0}},
	flower_4 = {x=224,y=96,width=16,height=16,anchor={8,0}},
	starman = {x=128, y=48, width=16, height=16, anchor= {8,0}},
	bonus_brick_1 = {x=160, y=0, width=16, height=16 },
	bonus_brick_2 = {x=176, y=0, width=16, height=16 },
	bonus_brick_3 = {x=192, y=0, width=16, height=16 },
	bonus_brick_taken = {x=224, y=0, width=16, height=16},
	bonus_brick_taken_dark = {x=240, y=96, width=16, height=16},
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
	end_level_flag = {x=224,y=64,width=16,height=16},
	castle_flag = {x=240,y=64,width=16,height=16},
	coin_counter_1 = {x=128,y=80,width=16,height=16},
	coin_counter_2 = {x=144,y=80,width=16,height=16},
	coin_counter_3 = {x=160,y=80,width=16,height=16},
	mario_fire_1 = {x=176,y=112,width=16,height=16,anchor={8,8}},
	mario_fire_2 = {x=192,y=112,width=16,height=16,anchor={8,8}},
	mario_fire_3 = {x=208,y=112,width=16,height=16,anchor={8,8}},
	mario_fire_4 = {x=224,y=112,width=16,height=16,anchor={8,8}},
	enemy_fire_1 = {x=180,y=116,width=8,height=8,anchor={4,4}},
	enemy_fire_2 = {x=196,y=116,width=8,height=8,anchor={4,4}},
	enemy_fire_3 = {x=212,y=116,width=8,height=8,anchor={4,4}},
	enemy_fire_4 = {x=228,y=116,width=8,height=8,anchor={4,4}},
	plant_1 = {x=128,y=96,width=16,height=32,anchor={8,0}},
	plant_2 = {x=144,y=96,width=16,height=32,anchor={8,0}},






}

local dt=0.1


local mario_box = {-8,0,8,16}
local supermario_box = {-8,0,8,16}


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
	}
}

models["supermario"] = {
    sheet = "smb1.png",
    type = "boxed_sprite",
    ppu=1,
	animations = {
		{ name = "idle", box = {-8, 0, 8, 32}, frames = { {duration = dt, quads = {{ id = s.mario_idle_big }}}}},
		{ name = "walk", box = {-8, 0, 8, 32}, frames = {
			{ duration = dt, quads = {{ id = s.mario_walk_big_1 } }},
			{ duration = dt, quads = {{ id = s.mario_walk_big_2 } }},
			{ duration = dt, quads = {{ id = s.mario_walk_big_3 } }},
		}},
		{ name = "jump", box = {-8, 0, 8, 32}, frames = { { duration = dt, quads = {{ id = s.mario_jump_big }}}}},
		{ name = "slide", frames = { { duration = dt, quads = {{ id = s.mario_slide }}}}},
	}
}
models["supermario"] = {
    sheet = "smb1.png",
    type = "boxed_sprite",
    ppu=1,
	animations = {
		{ name = "idle", box = {-8, 0, 8, 32}, frames = { {duration = dt, quads = {{ id = s.mario_idle_big }}}}},
		{ name = "walk", box = {-8, 0, 8, 32}, frames = {
			{ duration = dt, quads = {{ id = s.mario_walk_big_1 } }},
			{ duration = dt, quads = {{ id = s.mario_walk_big_2 } }},
			{ duration = dt, quads = {{ id = s.mario_walk_big_3 } }},
		}},
		{ name = "jump", box = {-8, 0, 8, 32}, frames = { { duration = dt, quads = {{ id = s.mario_jump_big }}}}},
		{ name = "slide", frames = { { duration = dt, quads = {{ id = s.mario_slide_big }}}}},
	}
}

models["supermario_fire"] = {
    sheet = "smb1.png",
    type = "boxed_sprite",
    ppu=1,
	animations = {
		{ name = "idle", box = {-8, 0, 8, 32}, frames = { {duration = dt, quads = {{ id = s.mario_idle_fire }}}}},
		{ name = "walk", box = {-8, 0, 8, 32}, frames = {
			{ duration = dt, quads = {{ id = s.mario_walk_fire_1 } }},
			{ duration = dt, quads = {{ id = s.mario_walk_fire_2 } }},
			{ duration = dt, quads = {{ id = s.mario_walk_fire_3 } }},
		}},
		{ name = "jump", box = {-8, 0, 8, 32}, frames = { { duration = dt, quads = {{ id = s.mario_jump_fire }}}}},
		{ name = "slide", frames = { { duration = dt, quads = {{ id = s.mario_slide_big }}}}},
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
		{ name = "dead", box={-8,0,8,16}, frames = { 
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
models["basicbrick_dark"] = glib.basic_model ("smb1.png", s.brick_dark)
models["score_100"] = glib.basic_model ("smb1.png", s.score_100)
models["brickpiece"] = glib.basic_model ("smb1.png", s.brick_piece)
models["brickpiece_dark"] = glib.basic_model ("smb1.png", s.brick_piece_dark)
models["end_level_flag"] = glib.basic_model ("smb1.png", s.end_level_flag)
models["castle_flag"] = glib.basic_model ("smb1.png", s.castle_flag)


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

models["plant"] = {
    sheet = "smb1.png",
    type = "boxed_sprite",
    ppu=1,
	animations = {
		{ name = "walk", box = {-8, 0, 8, 16}, frames = {
			{ duration = dt, quads = {{ id = s.plant_1 } }},
			{ duration = dt, quads = {{ id = s.plant_2 } }},
		}},
	}
}

models["coin_counter"] = {
    sheet = "smb1.png",
    type = "sprite",
    ppu=1,
	animations = {
		{ name = "walk", frames = {
			{ duration = dt, quads = {{ id = s.coin_counter_1 } }},
			{ duration = dt, quads = {{ id = s.coin_counter_2 } }},
			{ duration = dt, quads = {{ id = s.coin_counter_3 } }},
			{ duration = dt, quads = {{ id = s.coin_counter_2 } }},
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

models["bonusbrick2_dark"] = {
    sheet = "smb1.png",
    type = "sprite",
    ppu=1,
	animations = {
		{ name = "default", frames = {
			{ duration = dt, quads = {{ id = s.brick_dark } }},
		}},
		{ name = "taken", frames = {
			{ duration = dt, quads = {{ id = s.bonus_brick_taken_dark } }},
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

models["flower"] = {
    sheet = "smb1.png",
    type = "boxed_sprite",
    ppu=1,
	animations = {
		{ name = "default", box = {-8, 0, 8, 16}, frames = {
			{ duration = dt, quads = {{ id = s.flower_1 } }},
			{ duration = dt, quads = {{ id = s.flower_2 } }},
			{ duration = dt, quads = {{ id = s.flower_3 } }},
			{ duration = dt, quads = {{ id = s.flower_4 } }},
		}},
	}
}

models["fire"] = {
    sheet = "smb1.png",
    type = "boxed_sprite",
    ppu=1,
	animations = {
		{ name = "walk", box = {-4,-4,4,4}, frames = {
			{ duration = dt, quads = {{ id = s.mario_fire_1 } }},
			{ duration = dt, quads = {{ id = s.mario_fire_2 } }},
			{ duration = dt, quads = {{ id = s.mario_fire_3 } }},
			{ duration = dt, quads = {{ id = s.mario_fire_4 } }},
		}},
	}
}

models["enemy_fire"] = {
    sheet = "smb1.png",
    type = "boxed_sprite",
    ppu=1,
	animations = {
		{ name = "walk", box = {-4,-4,4,4}, frames = {
			{ duration = dt, quads = {{ id = s.enemy_fire_1 } }},
			{ duration = dt, quads = {{ id = s.mario_fire_2 } }},
			{ duration = dt, quads = {{ id = s.mario_fire_3 } }},
			{ duration = dt, quads = {{ id = s.mario_fire_4 } }},
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