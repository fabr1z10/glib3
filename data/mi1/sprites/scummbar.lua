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

sprites.door_scummbar_kitchen = 
{
    id = "door_scummbar_kitchen",
    sheet = "gfx/anims2.png",
    type="sprite",
    ppu=1,
    animations = {
    { name = "close", frames = { {duration = dt, quads = { { x = 44, y = 199, width = 35, height = 69, anchor = {0, 0}}}}}},
    { name = "open", frames = { {duration = dt, quads = { { x = 44, y = 270, width = 35, height = 69, anchor = {0, 0}}}}}}
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

sprites.estevan = {
	id = "estevan",
	sheet = "gfx/anims.png",
    type="sprite",
    ppu=1,
    animations = {
    	{ 
			name = "idle", 
			frames = { 
				{duration = dt, quads = { { x = 183, y = 455, width = 35, height = 27, anchor = {0, 0}}}},
			}
		},
     	{ 
			name = "drink", 
			frames = { 
				{duration = dt, quads = { { x = 220, y = 455, width = 39, height = 27, anchor = {0, 0}}}},
				{duration = dt, quads = { { x = 261, y = 455, width = 37, height = 27, anchor = {0, 0}}}},
				{duration = dt, quads = { { x = 220, y = 455, width = 39, height = 27, anchor = {0, 0}}}},
			}
		}
	}
}

sprites.loompirate =
{
	id = "loompirate",
	sheet = "gfx/anims.png",
   	type="sprite",
   	ppu=1,
  	animations = {
  		{ 
			name = "idle", frames = { 
				{duration = dt, quads = { { x = 352, y = 473, width = 29, height = 38, anchor = {0, 0}}}},
			}
		},
    	{ 
			name = "idle2", frames = { 
				{duration = dt, quads = { { x = 414, y = 474, width = 29, height = 37, anchor = {0, 0}}}},
			}
		},
       	{ 
			name = "move", frames = { 
				{duration = dt, quads = { { x = 383, y = 474, width = 29, height = 37, anchor = {0, 0}}}},
			}
		},
    }
}

sprites.fireplace = 
{
    id = "fireplace",
    sheet = "gfx/anims.png",
    type="sprite",
    ppu=1,
    animations = {
  		{ name = "default", frames = { 
			{duration = dt, quads = { { x = 262, y = 280, width = 32, height = 26, anchor = {0, 0}}}},
			{duration = dt, quads = { { x = 296, y = 280, width = 32, height = 26, anchor = {0, 0}}}},
			{duration = dt, quads = { { x = 330, y = 280, width = 32, height = 26, anchor = {0, 0}}}},
		}
	}}
}

sprites.cook = {
    id="cook",
    sheet="gfx/anims.png",
    type="sprite",
    ppu=1,
    animations = {
    	{
            name = "idle_front",             
            frames = { 
            {
                duration = dt,
                quads = {
                    { x = 316, y = 213, width = 31, height = 48, anchor = {15, 0}}
                }
            }}
        },
        {
            name = "idle_right",             
            frames = {
            {
                duration = dt,
                quads = {
                    { x = 438, y = 115, width = 28, height = 48, anchor = {14, 0}}
                }
            }}
        },
        {
            name = "idle_back",             
            frames = {
            {
                duration = dt,
                quads = {
                    { x = 462, y = 165, width = 36, height = 48, anchor = {18, 0}}
                }
            }}
        },
        {
            name = "walk_right",             
            frames = {
              { duration = dt, quads = {{ x = 349, y = 216, width = 25, height = 48, anchor = {12, 0}}}},
              { duration = dt, quads = {{ x = 376, y = 216, width = 31, height = 48, anchor = {15, 0}}}},
              { duration = dt, quads = {{ x = 409, y = 215, width = 20, height = 49, anchor = {10, 0}}}},
              { duration = dt, quads = {{ x = 431, y = 215, width = 28, height = 49, anchor = {14, 0}}}},
              { duration = dt, quads = {{ x = 460, y = 216, width = 27, height = 48, anchor = {14, 0}}}},
              { duration = dt, quads = {{ x = 489, y = 216, width = 22, height = 48, anchor = {11, 0}}}}
            }
        }, 
        {
            name = "talk_right",             
            frames = {
              { duration = dt, quads = {{ x = 349, y = 116, width = 28, height = 47, anchor = {14, 0}}}},
              { duration = dt, quads = {{ x = 379, y = 115, width = 28, height = 48, anchor = {14, 0}}}}, 
              { duration = dt, quads = {{ x = 408, y = 115, width = 28, height = 48, anchor = {14, 0}}}},
              { duration = dt, quads = {{ x = 438, y = 115, width = 28, height = 48, anchor = {14, 0}}}},
              { duration = dt, quads = {{ x = 467, y = 115, width = 29, height = 48, anchor = {14, 0}}}}
            }
        },   
    }
}