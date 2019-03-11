local dt = 0.1

sprites.lookout = {
       id="lookout",
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
			    		{ x = 215, y = 1, width = 23, height = 44, anchor = {12, 0}},
                    	{ x = 129, y = 1, width = 9, height = 14, anchor = {6, -29}}
					}
            	}
			}
		},
  			{
           	name = "idle_right",             
           	frames = {
    	  		{
					duration = dt,
               	    quads = {
		    			{ x = 105, y = 1, width = 20, height = 37, anchor = {10, 0}},
                   		{ x = 126, y = 18, z= 0.001,width = 12, height = 13, anchor = {2, -30}}
				    }
           		}
			}
	    },
		{
           	name = "idle_back",             
           	frames = {
           		{
               		duration = dt,
               		quads = {
                   		{ x = 190, y = 1, width = 22, height = 35, anchor = {11, 0}},
                   		{ x = 168, y = 10, z= 0.001,width = 9, height = 9, anchor = {0, -31}}
               		}
           		}
			}
       	},
        {
           	name = "talk_front",             
           	frames = {
             		{ duration = dt, quads = {{ x = 215, y = 1, width = 23, height = 44, anchor = {12, 0}}, { x = 129, y = 1, z= 0.001,width = 9, height = 14, anchor = {6, -29}}}},
             		{ duration = dt, quads = {{ x = 215, y = 1, width = 23, height = 44, anchor = {12, 0}}, { x = 143, y = 1, z= 0.001,width = 9, height = 15, anchor = {6, -29}}}}
           	}
       	}, 
       	{
           	name = "talk_right",             
           	frames = {
             		{ duration = dt, quads = {{ x = 105, y = 1, width = 20, height = 37, anchor = {10, 0}}, { x = 126, y = 18, z= 0.001,width = 12, height = 13, anchor = {2, -30}}}},
             		{ duration = dt, quads = {{ x = 105, y = 1, width = 20, height = 37, anchor = {10, 0}}, { x = 140, y = 18, z= 0.001,width = 12, height = 14, anchor = {2, -30}}}}
           	}
       	},                
       	{
           	name = "talk_back",             
           	frames = {
             		{ duration = dt, quads = {{ x = 190, y = 1, width = 22, height = 35, anchor = {11, 0}}}}
           	}
       	}        
   	}
}
sprites.fire = {
       id = "fire",
       sheet = "gfx/anims.png",
       type="sprite",
       ppu=1,
       animations = {
       {
      	    name = "default",             
           frames = 
           { 
    	  	{ duration = dt, quads = { { x = 1, y = 1, width = 24, height = 32, anchor = {0, 0}}}},
               { duration = dt, quads = { { x = 27, y = 1, width = 24, height = 32, anchor = {0, 0}}}},
               { duration = dt, quads = { { x = 53, y = 1, width = 24, height = 32, anchor = {0, 0}}}},
               { duration = dt, quads = { { x = 79, y = 1, width = 24, height = 32, anchor = {0, 0}}}}               
		}
       }
       }
   }
