local dt = 0.1

sprites["voodoolady.door"] = {
	id = "voodoolady.door",
    sheet = "gfx/anims.png",
    type="sprite",
    ppu=1,
    animations = {
        { name = "close", frames = { {duration = dt, quads = { { x = 183, y = 221, width = 33, height = 58, anchor = {0, 0}}}}}},
        { name = "open", frames = { {duration = dt, quads = { { x = 218, y = 221, width = 33, height = 58, anchor = {0, 0}}}}}}
    }
}

models["voodoolady"] = {
	id ="voodoolady",
	type="model",
	components = {
		{ name="body", mesh="voodoolady.body" },
		{ name="head", mesh="voodoolady.head", pos = {0, 20, 0} }
	}
}

sprites["voodoolady.body"] = {
	id = "voodoolady.body",
	sheet = "gfx/anims.png",
    type="sprite",
    ppu=1,
    animations = {
        { name = "idle", frames = { 
			{duration = dt*10, quads = { { x = 184, y = 187, width = 42, height = 33, anchor = {20, 0}}}},
			{duration = dt, quads = { { x = 184, y = 141, width = 42, height = 33, anchor = {20, 0}}}},
			{duration = dt*10, quads = { { x = 229, y = 141, width = 42, height = 33, anchor = {20, 0}}}},
			{duration = dt, quads = { { x = 184, y = 141, width = 42, height = 33, anchor = {20, 0}}}},
			}
		},
        { name = "raisehands", frames = { 
			{duration = dt, quads = { { x = 146, y = 245, width = 35, height = 33, anchor = {12, 0}}}},
			{duration = dt, quads = { { x = 122, y = 142, width = 61, height = 33, anchor = {24, 0}}}},
			{duration = dt, quads = { { x = 77, y = 312, width = 40, height = 44, anchor = {14, 0}}}},
			{duration = dt, quads = { { x = 120, y = 313, width = 40, height = 43, anchor = {13, 0}}}},
			{duration = dt, quads = { { x = 77, y = 312, width = 40, height = 44, anchor = {14, 0}}}},
			{duration = dt, quads = { { x = 120, y = 313, width = 40, height = 43, anchor = {13, 0}}}},
			{duration = dt, quads = { { x = 77, y = 312, width = 40, height = 44, anchor = {14, 0}}}},
			{duration = dt, quads = { { x = 120, y = 313, width = 40, height = 43, anchor = {13, 0}}}},
			}
		},
	}
}

sprites["voodoolady.voodoolady"] = 	{	
	id ="voodoolady.voodoolady",
	sheet = "gfx/anims.png",
    type="sprite",
    ppu=1,
    animations = {
        { name = "idle", frames = { 
			{duration = dt, quads = { { x = 228, y = 175, width = 12, height = 15, anchor = {-20, -30}}}},
		}
			
		},
        { name = "talk", frames = { 
			{duration = dt, quads = { { x = 241, y = 175, width = 12, height = 15, anchor = {-20, -30}}}},
			{duration = dt, quads = { { x = 254, y = 175, width = 12, height = 15, anchor = {-20, -30}}}},
			{duration = dt, quads = { { x = 228, y = 191, width = 13, height = 15, anchor = {-20, -30}}}},
			{duration = dt, quads = { { x = 242, y = 191, width = 13, height = 15, anchor = {-20, -30}}}},
			{duration = dt, quads = { { x = 256, y = 191, width = 12, height = 15, anchor = {-20, -30}}}}
		}
		},

	}		
}

sprites["voodoolady.trunk"] = 
{
	id = "voodoolady.trunk",
	sheet = "gfx/anims.png",
    type="sprite",
    ppu=1,
    animations = {
        { name = "idle", frames = { 
			{duration = dt, quads = { { x = 2, y = 274, width = 81, height = 24, anchor = {0, 0}}}},
			}
	}}
}