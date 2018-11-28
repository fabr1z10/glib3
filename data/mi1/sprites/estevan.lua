local dt = 0.1

sprites.estevan2 = {
	id = "estevan2",
    sheet = "gfx/faces.png",
    type="sprite",
    ppu=1,
    animations = {
    	{ name = "idle", frames = { {duration = dt, quads = { { x = 268, y = 79, width = 92, height = 94, anchor = {0, 0}}}}}},
        { name = "blink", frames = { 
			{duration = dt, quads = { { x = 174, y = 79, width = 92, height = 94, anchor = {0, 0}}}},
			{duration = dt, quads = { { x = 80, y = 174, width = 92, height = 94, anchor = {0, 0}}}},
			{duration = dt, quads = { { x = 174, y = 79, width = 92, height = 94, anchor = {0, 0}}}},
		}},
        { name = "scared", frames = { {duration = dt, quads = { { x = 80, y = 79, width = 92, height = 94, anchor = {0, 0}}}}}},
	}
}