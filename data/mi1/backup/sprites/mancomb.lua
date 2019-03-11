local dt = 0.1

sprites.mancomb2 = {
	id = "mancomb2",
    sheet = "gfx/faces.png",
    type="sprite",
    ppu=1,
    animations = {
    	{ name = "idle", frames = { {duration = dt, quads = { { x = 80, y = 0, width = 78, height = 78, anchor = {0, 0}}}}}},
        { name = "blink", frames = { 
			{duration = dt, quads = { { x = 160, y = 0, width = 78, height = 78, anchor = {0, 0}}}},
			{duration = dt, quads = { { x = 0, y = 79, width = 78, height = 78, anchor = {0, 0}}}},
			{duration = dt, quads = { { x = 160, y = 0, width = 78, height = 78, anchor = {0, 0}}}},
		}},
        { name = "smile", frames = { {duration = dt, quads = { { x = 0, y = 0, width = 78, height = 78, anchor = {0, 0}}}}}},
	}      
}