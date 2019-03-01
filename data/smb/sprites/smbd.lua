local dt = 0.1

require("sprites/smbs")

local s = spritesheets["smb"]

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
			name = "small.walk",
			frames = {
				{ duration = dt, quads = {{ id = s.mario_walk_1 } }},
				{ duration = dt, quads = {{ id = s.mario_walk_2 } }},
				{ duration = dt, quads = {{ id = s.mario_walk_3 } }},
			}
		},
		{
			name = "small.jump",
			frames = {
				{ duration = dt, quads = {{ id = s.mario_jump }}},
			}
		},
	}
}

