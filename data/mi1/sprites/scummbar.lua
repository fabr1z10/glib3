local dt = 0.1

sprites.door_scummbar_village = {
    id = "door_scummbar_village",
    sheet = "gfx/anims2.png",
    type="sprite",
    ppu=1,
    animations = 
	{
     	{ name = "close", frames = { {duration = dt, quads = { { x = 2, y = 243, width = 38, height = 47, anchor = {0, 0}}}}}},
      	{ name = "open", frames = { {duration = dt, quads = { { x = 2, y = 195, width = 38, height = 47, anchor = {0, 0}}}}}}
    }
}

sprites.mancomb =  {
	id = "mancomb",
	sheet = "gfx/anims.png",
    type="sprite",
    ppu=1,
    animations = 
	{
    	{ name = "idle", frames = { {duration = dt, quads = { { x = 6, y = 405, width = 33, height = 40, anchor = {0, 0}}}}}},
        { name = "drink", frames = { {duration = dt*2, quads = { { x = 3, y = 446, width = 36, height = 40, anchor = {0, 0}}}}}}
	}
}