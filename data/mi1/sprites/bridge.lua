local dt = 0.5

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
	   		name = "look_around",             
	        frames = { 
	 	    	{ duration = dt, quads = { { x = 133, y = 17, width = 20, height = 15, anchor = {13, 0}}}},
	 	    	{ duration = dt, quads = { { x = 111, y = 1, width = 20, height = 15, anchor = {10, 0}}}},
	 	    	{ duration = dt, quads = { { x = 132, y = 1, width = 20, height = 15, anchor = {7, 0}}}},
	 	    	{ duration = dt, quads = { { x = 153, y = 1, width = 18, height = 16, anchor = {7, 0}}}},
	 	    	{ duration = dt, quads = { { x = 132, y = 1, width = 20, height = 15, anchor = {7, 0}}}},
	 	    	{ duration = dt, quads = { { x = 111, y = 1, width = 20, height = 15, anchor = {10, 0}}}},
	 	    	{ duration = dt, quads = { { x = 133, y = 17, width = 20, height = 15, anchor = {13, 0}}}},
				{ duration = 3*dt, quads = { { x = 155, y = 17, width = 18, height = 16, anchor = {13, 0}}}},
			}
		},
		{
	   		name = "look_front",             
	        frames = { 
	 	    	{ duration = 5*dt, quads = { { x = 111, y = 1, width = 20, height = 15, anchor = {11, 0}}}},
	 	    	{ duration = dt, quads = { { x = 199, y = 1, width = 20, height = 15, anchor = {11, 0}}}},
	 	    	{ duration = dt, quads = { { x = 221, y = 1, width = 20, height = 16, anchor = {11, 1}}}},
				{ duration = dt, quads = { { x = 199, y = 17, width = 20, height = 16, anchor = {11, 1}}}},
				{ duration = dt, quads = { { x = 221, y = 18, width = 20, height = 14, anchor = {11, -1}}}},
				{ duration = dt, quads = { { x = 215, y = 34, width = 20, height = 12, anchor = {11, -1}}}},
				{ duration = 5*dt, quads = { { x = 236, y = 34, width = 20, height = 12, anchor = {11, -1}}}},
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

sprites["bridge.fish"] = {
	id="bridge.fish",
	sheet="gfx/troll.png",
	type="sprite",
	ppu=1,
	animations = {
		{
			name="idle",
			loop = false,
			frames = {
				{ duration=dt, quads = { { x = 88, y = 19, z=1, width=14, height=8, anchor = {-12, -12}}}},
				{ duration=dt, quads = { { x = 88, y = 19, z=1, width=14, height=8, anchor = {-10, -10}}}},
				{ duration=dt, quads = { { x = 88, y = 19, z=1, width=14, height=8, anchor = {-8, -8 }}}}
			}
		}
	}
}

sprites["bridge.troll.body"] = {
    id="bridge.troll.body",
    sheet="gfx/troll.png",
	type="sprite",
    ppu=1,
	addinfo = {
		{ anim = "idle", data = { pos = { { name = "head", offset = {0, 26, 1}, angle = 0 }}}},
		{ anim = "idle_front", data = { pos = { { name = "head", offset = {0, 27, 1}, angle = 0 }}}},
		{ anim = "eat_s1", data = { pos = { { name = "head", offset = {0, 31, 1}, angle = 0 }}}}
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
            name = "idle_front",             
            frames = { 
 	    	  	{
			    	duration = dt,
                	quads = {
			    		{ x = 94, y = 71, width = 37, height = 32, anchor = {19, 0}},
					}
            	}
			}
		},
		{
            name = "take_fish", 
			loop = false,            
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
            name = "hold_fish",             
			loop = false,
            frames = { 
 	    	  	{
			    	duration = dt,
                	quads = {
			    		{ x = 76, y = 37, width = 50, height = 32, anchor = {24, 0}},
						
					}
            	},
 	    	  	{
			    	duration = dt,
                	quads = {
			    		{ x = 1, y = 70, width = 47, height = 33, anchor = {24, 0}},
					}
            	},
 	    	  	{
			    	duration = dt,
                	quads = {
			    		{ x = 49, y = 71, width = 42, height = 32, anchor = {24, 0}},
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
		},
		{
			name = "eat_s1",
			frames = {
				{ duration = dt, quads = {
					{x=127, y=34, width=29,height=35, anchor={16,0}},
					{x=156, y=34, width=15,height=21, anchor={-5,-14}},  -- left arm
				}},
				{ duration = dt, quads = {
					{x=127, y=34, width=29,height=35, anchor={16,0}},
					{x=172, y=34, width=18,height=19, anchor={-5,-16}},  -- left arm
				}},
				{ duration = dt, quads = {
					{x=127, y=34, width=29,height=35, anchor={16,0}},
					{x=191, y=34, width=21,height=14, anchor={-5,-21}},  -- left arm
				}},
				{ duration = dt, quads = {
					{x=127, y=34, width=29,height=35, anchor={16,0}},
					{x=159, y=56, width=15,height=12, anchor={-5,-23}},  -- left arm
				}},
				{ duration = dt, quads = {
					{x=127, y=34, width=29,height=35, anchor={16,0}},
					{x=178, y=55, width=10,height=13, anchor={-5,-23}},  -- left arm
				}},
				{ duration = dt, quads = {
					{x=127, y=34, width=29,height=35, anchor={16,0}},
					{x=191, y=54, width=14,height=12, anchor={-1,-25}},  -- left arm
				}},
				{ duration = dt, quads = {
					{x=127, y=34, width=29,height=35, anchor={16,0}},
					{x=207, y=53, width=13,height=14, anchor={-1,-25}},  -- left arm
				}},
				{ duration = dt, quads = {
					{x=127, y=34, width=29,height=35, anchor={16,0}},
					{x=222, y=49, width=13,height=18, anchor={-1,-25}},  -- left arm
				}},
				{ duration = dt, quads = {
					{x=127, y=34, width=29,height=35, anchor={16,0}},
					{x=178, y=55, width=10,height=13, anchor={-5,-23}},  -- left arm
				}},
				{ duration = 6*dt, quads = {
					{x=133, y=70, width=29, height=35, anchor={16,0}},
					{x=164, y=70, width=14, height=20, anchor={16,-15}}
				}},

			}
		}
   	}
}
