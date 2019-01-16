local dt = 0.1

sprites["bridge.troll.head"] = {
    id="bridge.troll.head",
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
	                   	{ x = 38, y = 2, width = 21, height = 15, anchor = {4, 0}}
					}
	            }
			}
		},
		{
	   		name = "talk",             
	        frames = { 
	 	    	{ duration = dt, quads = {{ x = 62, y = 2, width = 21, height = 16, anchor = {4, 1}}}},
	 	    	{ duration = dt, quads = {{ x = 86, y = 2, width = 21, height = 16, anchor = {4, 1}}}},
	 	    	{ duration = dt, quads = {{ x = 62, y = 2, width = 21, height = 16, anchor = {4, 1}}}},
	 	    	{ duration = dt, quads = {{ x = 40, y = 19, width = 21, height = 17, anchor = {4, 2}}}},
	 	    	{ duration = dt, quads = {{ x = 67, y = 19, width = 20, height = 17, anchor = {4, 2}}}},
			}
		},
	},

}

sprites["bridge.troll.body"] = {
    id="bridge.troll.body",
    sheet="gfx/troll.png",
	type="sprite",
    ppu=1,
	addinfo = {
		{ anim = "idle", data = { pos = { { name = "head", offset = {0, 26}, angle = 0 }}}}
	},
    animations = {
        {
            name = "idle",             
            frames = { 
 	    	  	{
			    	duration = dt,
                	quads = {
			    		{ x = 1, y = 2, width = 36, height = 32, anchor = {13, 0}},
					}
            	}
			}
		},
		{
            name = "take_fish",             
            frames = { 
 	    	  	{
			    	duration = dt,
                	quads = {
			    		{ x = 1, y = 2, width = 36, height = 32, anchor = {13, 0}},
					}
            	},
 	    	  	{
			    	duration = dt,
                	quads = {
			    		{ x = 0, y = 35, width = 27, height = 34, anchor = {12, 1}},
					}
            	},
 	    	  	{
			    	duration = dt,
                	quads = {
			    		{ x = 28, y = 37, width = 46, height = 32, anchor = {24, 0}},
					}
            	},
 	    	  	{
			    	duration = dt,
                	quads = {
			    		{ x = 76, y = 37, width = 50, height = 32, anchor = {24, 0}},
					}
            	},
 	    	  	{
			    	duration = dt,
                	quads = {
			    		{ x = 76, y = 37, width = 50, height = 32, anchor = {24, 0}},
					}
            	},
			}
		},
		{
            name = "wait_fish",             
            frames = { 
 	    	  	{
			    	duration = dt,
                	quads = {
			    		{ x = 76, y = 37, width = 50, height = 32, anchor = {24, 0}},
					}
            	},
			}
		},
		{
            name = "hold_fish",             
            frames = { 
 	    	  	{
			    	duration = dt,
                	quads = {
			    		{ x = 76, y = 37, width = 50, height = 32, anchor = {24, 0}},
						{ x = 88, y = 19, z=1, width=14, height=8, anchor = {-12, -12}} -- fish
					}
            	},
 	    	  	{
			    	duration = dt,
                	quads = {
			    		{ x = 1, y = 70, width = 47, height = 33, anchor = {24, 0}},
						{ x = 88, y = 19, z=1, width=14, height=8, anchor = {-10, -10}} -- fish
					}
            	},
 	    	  	{
			    	duration = dt,
                	quads = {
			    		{ x = 49, y = 71, width = 42, height = 32, anchor = {24, 0}},
						{ x = 88, y = 19, z=1, width=14, height=8, anchor = {-8, -8}} -- fish
					}
            	},
			}
		},
		{
            name = "idle_fish",             
            frames = { 
 	    	  	{
			    	duration = dt,
                	quads = {
			    		{ x = 49, y = 71, width = 42, height = 32, anchor = {24, 0}},
						{ x = 88, y = 19, z=1, width=14, height=8, anchor = {-8, -8}} -- fish
					}
            	},
			}
		}
   	}
}
