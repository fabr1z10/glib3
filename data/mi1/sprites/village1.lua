local dt = 0.1

sprites.door_village_scummbar = {
    id = "door_village_scummbar",
    sheet = "gfx/anims.png",
    type="sprite",
    ppu=1,
    animations = {
	    {
	   	    name = "close",             
	        frames = 
	        { 
	 	  		{ duration = dt, quads = { { x = 93, y = 185, width = 31, height = 52, anchor = {0, 0}}}}              
	  		}
	    },
	    {
	   	    name = "open",             
	        frames = 
	        { 
	 	  		{ duration = dt, quads = { { x = 61, y = 185, width = 31, height = 52, anchor = {0, 0}}}}              
	  		}
	    }
    }
}