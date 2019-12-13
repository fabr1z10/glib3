local models = engine.assets.models
local dt=0.1

local s = {
	wboy_idle_1 = {x=0,y=67,width=17,height=29, anchor={12,1}},
	wboy_idle_2 = {x=19,y=66,width=17,height=30, anchor={12,1}},
	wboy_walk_1 = {x=38,y=67,width=19,height=29,anchor={11,1}},
	wboy_walk_2 = {x=58,y=67,width=16,height=29,anchor={11,1}},
	wboy_walk_3 = {x=76,y=66,width=16,height=30,anchor={11,1}},
	wboy_walk_4 = {x=94,y=66,width=21,height=30,anchor={11,1}},
	apple = {x=35,y=52,width=9,height=12},
	snail_1 = {x=81,y=12,width=21,height=20,anchor={10,1}},	
	snail_2 = {x=103,y=15,width=21,height=17,anchor={10,1}},

}

local box = {-10,0,10,20}
models["wboy"] = {
    sheet = "tiles.png",
	type = "boxed_sprite",
    ppu=1,
	animations = {
		{ name = "idle", box=box,frames = {
			{ duration = dt, quads = {{ id = s.wboy_idle_1 } }},
			{ duration = dt, quads = {{ id = s.wboy_idle_2 } }},
		}},
		{ name = "walk", box=box, frames = {
			{ duration = dt, quads = {{ id = s.wboy_walk_1 } }},
			{ duration = dt, quads = {{ id = s.wboy_walk_2 } }},
			{ duration = dt, quads = {{ id = s.wboy_walk_3 } }},
			{ duration = dt, quads = {{ id = s.wboy_walk_4 } }},
			{ duration = dt, quads = {{ id = s.wboy_walk_3 } }},
			{ duration = dt, quads = {{ id = s.wboy_walk_2 } }},
		}},
		{ name = "jumpup", box=box, frames = {
			{ duration = dt, quads = {{ id = s.wboy_walk_4 } }},
		}},
		{ name = "jumpdown", box=box, frames = {
			{ duration = dt, quads = {{ id = s.wboy_walk_4 } }},
		}},		
	}
}

models["apple"] = {
    sheet = "tiles.png",
	type = "sprite",
    ppu=1,
	animations = {
		{ name = "idle", frames = { { duration = dt, quads = {{ id = s.apple } }}}}
	}
}

models["snail"] = {
    sheet = "tiles.png",
	type = "boxed_sprite",
    ppu=1,
	animations = {
		{ name = "idle", box={-10,0,10,10}, frames = { 
			{ duration = dt, quads = {{ id = s.snail_1 }}},
			{ duration = dt, quads = {{ id = s.snail_2 }}},
		}},
		{ name = "walk", box={-10,0,10,10}, frames = { 
			{ duration = dt, quads = {{ id = s.snail_1 } }},
			{ duration = dt, quads = {{ id = s.snail_2 } }},
		}},
		{ name = "jump", box={-10,0,10,10}, frames = { 
			{ duration = dt,quads = {{ id = s.snail_1 } }},
			{ duration = dt,quads = {{ id = s.snail_2 } }},
		}},
	}
}