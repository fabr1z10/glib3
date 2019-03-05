local dt = 0.1

require("sprites/smbs")

local s = spritesheets["smb"]

models["basicbrick"] = { sheet="sprites/smb1.png", type="sprite", ppu=1, animations = { { name="idle", frames = { {duration=dt, quads ={{id=s.brick}}}}}}}
models["brick_piece"] = { sheet="sprites/smb1.png", type="sprite", ppu=1, animations = { { name="idle", frames = { {duration=dt, quads ={{id=s.brick_piece}}}}}}}
models["mushroom"] = { sheet="sprites/smb1.png", type="sprite", ppu=1, animations = { { name="idle", frames = { {duration=dt, quads ={{id=s.mushroom}}}}}}}
models["bonusbrick"] = { 
	sheet="sprites/smb1.png", 
	type="sprite", 
	ppu=1, 
    animations = { 
		{ 
			name="default", 
			frames = { 
				{duration=dt, quads ={{id=s.bonus_brick_1}}},
				{duration=dt, quads ={{id=s.bonus_brick_2}}},
				{duration=dt, quads ={{id=s.bonus_brick_3}}},
				{duration=dt, quads ={{id=s.bonus_brick_2}}}
			}
		},
		{ 
			name="taken", 
			frames = { 
				{duration=dt, quads ={{id=s.bonus_brick_taken}}}
			}
		},	
	}
}



models["mario"] = {
    sheet = "sprites/smb1.png",
    type = "sprite",
    ppu=1,
	animations = {
		{
			name = "small.idle",
			frames = {
				{ duration = dt, quads = {{ id = s.mario_idle }}}
			}
		},
		{
			name = "large.nofire.idle",
			frames = {
				{ duration = dt, quads = {{ id = s.mario_idle_big }}}
			}
		},
		{
			name = "small.walk",
			frames = {
				{ duration = dt, quads = {{ id = s.mario_walk_1 } }},
				{ duration = dt, quads = {{ id = s.mario_walk_2 } }},
				{ duration = dt, quads = {{ id = s.mario_walk_3 } }},
			}
		},
		{
			name = "large.nofire.walk",
			frames = {
				{ duration = dt, quads = {{ id = s.mario_walk_big_1 } }},
				{ duration = dt, quads = {{ id = s.mario_walk_big_2 } }},
				{ duration = dt, quads = {{ id = s.mario_walk_big_3 } }},
			}
		},
		{
			name = "small.jump",
			frames = {
				{ duration = dt, quads = {{ id = s.mario_jump }}},
			}
		},
		{
			name = "large.nofire.jump",
			frames = {
				{ duration = dt, quads = {{ id = s.mario_jump_big }}},
			}
		},
		{
			name = "large.nofire.duck",
			frames = {
				{ duration = dt, quads = {{ id = s.mario_duck_big }}},
			}
		},

	}
}

