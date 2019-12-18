local models = engine.assets.models
local dt=0.1

local s = {
	bub_idle_1 = {x=0,y=48,width=16,height=16, anchor={8,0}},
	bub_idle_2 = {x=16,y=48,width=16,height=16, anchor={8,0}},
	bub_walk_1 = {x=32,y=48,width=16,height=16, anchor={8,0}},
	bub_walk_2 = {x=48,y=48,width=16,height=16, anchor={8,0}},
	bub_walk_3 = {x=64,y=48,width=16,height=16, anchor={8,0}},
	bub_shoot_1 = {x=96, y=48, width=16, height=16, anchor={8,0}},	
	bub_shoot_2 = {x=112, y=48, width=16, height=16, anchor={8,0}},
	bub_jump = {x=80,y=48,width=16,height=16, anchor={8,0}},
	zenchan_1 = {x=0,y=64,width=16,height=16,anchor={8,0}},
	zenchan_2 = {x=16,y=64,width=16,height=16,anchor={8,0}},
	zenchan_3 = {x=32,y=64,width=16,height=16,anchor={8,0}},
	bubble_1 = {x=8,y=32,width=8,height=8, anchor={4,4}},
	bubble_2 = {x=16, y=32,width=8,height=8, anchor={4,4}},
	bubble_3 = {x=24, y=32,width=10,height=10, anchor={5,5}},
	bubble_4 = {x=35, y=32,width=10,height=10, anchor={5,5}},
	bubble_5 = {x=46, y=32,width=12,height=14, anchor={6,7}},
	bubble_6 = {x=64, y=32,width=16,height=16, anchor={8,8}},

}

local box = {-8,0,8,16}

models["bub"] = {
    sheet = "tiles.png",
	type = "boxed_sprite",
    ppu=1,
	animations = {
		{ name = "idle", box=box,frames = {
			{ duration = dt, quads = {{ id = s.bub_idle_1 } }},
			{ duration = dt, quads = {{ id = s.bub_idle_2 } }},
		}},
		{ name = "walk", box=box, frames = {
			{ duration = dt, quads = {{ id = s.bub_idle_2 } }},
			{ duration = dt, quads = {{ id = s.bub_walk_1 } }},
			{ duration = dt, quads = {{ id = s.bub_walk_2 } }},
			{ duration = dt, quads = {{ id = s.bub_walk_3 } }},
		}},
		{ name = "jumpup", box=box, frames = {
			{ duration = dt, quads = {{ id = s.bub_jump } }},
		}},
		{ name = "jumpdown", box=box, frames = {
			{ duration = dt, quads = {{ id = s.bub_jump } }},
		}},	
		{ name = "shoot", box=box,frames = {
			{ duration = dt, quads = {{ id = s.bub_shoot_1 } }},
			{ duration = dt, quads = {{ id = s.bub_shoot_2 } }},
		}},

	}
}

models["zenchan"] = {
    sheet = "tiles.png",
	type = "boxed_sprite",
    ppu=1,
	animations = {
		{ name = "idle", box=box,frames = {
			{ duration = dt, quads = {{ id = s.zenchan_1 } }},
			{ duration = dt, quads = {{ id = s.zenchan_2 } }},
			{ duration = dt, quads = {{ id = s.zenchan_3 } }},
			{ duration = dt, quads = {{ id = s.zenchan_2 } }},
		}},
		{ name = "walk", box=box, frames = {
			{ duration = dt, quads = {{ id = s.zenchan_1 } }},
			{ duration = dt, quads = {{ id = s.zenchan_2 } }},
			{ duration = dt, quads = {{ id = s.zenchan_3 } }},
			{ duration = dt, quads = {{ id = s.zenchan_2 } }},
		}},
		{ name = "jumpup", box=box, frames = {
			{ duration = dt, quads = {{ id = s.zenchan_1 } }},
			{ duration = dt, quads = {{ id = s.zenchan_2 } }},
			{ duration = dt, quads = {{ id = s.zenchan_3 } }},
			{ duration = dt, quads = {{ id = s.zenchan_2 } }},
		}},
		{ name = "jumpdown", box=box, frames = {
			{ duration = dt, quads = {{ id = s.zenchan_1 } }},
			{ duration = dt, quads = {{ id = s.zenchan_2 } }},
			{ duration = dt, quads = {{ id = s.zenchan_3 } }},
			{ duration = dt, quads = {{ id = s.zenchan_2 } }},
		}},		
	}
}

models["bubble"] = {
    sheet = "tiles.png",
	type = "boxed_sprite",
    ppu=1,
	animations = {
		{ name = "default", box=box, loop = false, frames = {
			{ duration = dt, quads = {{ id = s.bubble_1 } }},
			{ duration = dt, quads = {{ id = s.bubble_2 } }},
			{ duration = dt, quads = {{ id = s.bubble_3 } }},
			{ duration = dt, quads = {{ id = s.bubble_4 } }},
			{ duration = dt, quads = {{ id = s.bubble_5 } }},
			{ duration = dt, quads = {{ id = s.bubble_6 } }},
		}},
	}
}


