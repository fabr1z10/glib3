local models = engine.assets.models
local dt=0.1

local s = {
	bub_idle_1 = {x=0,y=48,width=16,height=16, anchor={8,0}},
	bub_idle_2 = {x=16,y=48,width=16,height=16, anchor={8,0}},
	bub_walk_1 = {x=32,y=48,width=16,height=16, anchor={8,0}},
	bub_walk_2 = {x=48,y=48,width=16,height=16, anchor={8,0}},
	bub_walk_3 = {x=64,y=48,width=16,height=16, anchor={8,0}},
	bub_jump = {x=80,y=48,width=16,height=16, anchor={8,0}},
	zenchan_1 = {x=0,y=64,width=16,height=16,anchor={8,0}},
	zenchan_2 = {x=16,y=64,width=16,height=16,anchor={8,0}},

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
		}},
		{ name = "walk", box=box, frames = {
			{ duration = dt, quads = {{ id = s.zenchan_1 } }},
			{ duration = dt, quads = {{ id = s.zenchan_2 } }},
		}},
		{ name = "jumpup", box=box, frames = {
			{ duration = dt, quads = {{ id = s.zenchan_1 } }},
			{ duration = dt, quads = {{ id = s.zenchan_2 } }},
		}},
		{ name = "jumpdown", box=box, frames = {
			{ duration = dt, quads = {{ id = s.zenchan_1 } }},
			{ duration = dt, quads = {{ id = s.zenchan_2 } }},
		}},		
	}
}

