local dt = 0.1

sprites["bridge.troll"] = {
    id="bridge.troll",
    sheet="gfx/troll.png",
	type="sprite",
    ppu=1,
    animations = {
        {
            name = "idle",             
            frames = { 
 	    	  	{
			    	duration = dt,
                	quads = {
			    		{ x = 1, y = 2, width = 36, height = 32, anchor = {13, 0}},
                    	{ x = 38, y = 2, width = 21, height = 15, anchor = {6, -29}}
					}
            	}
			}
		},
   	}
}
