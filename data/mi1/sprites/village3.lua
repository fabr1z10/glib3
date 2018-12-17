local dt = 0.1

sprites["village3.shop_door"] = {
	id = "village3.shop_door",
    sheet = "gfx/anims.png",
    type="sprite",
    ppu=1,
    animations = {
        {
       	    name = "open",             
            frames = 
            { 
	    	  	{ duration = dt, quads = { { x=78, y=150, width=20, height=31, anchor = {0, 0}}}}             
		    }
        },
        {
       	    name = "close",             
            frames = 
            { 
	    	  	{ duration = dt, quads = { { x=101, y=150, width=20, height=31, anchor = {0, 0}}}}             
		    }
        },
	}		
}