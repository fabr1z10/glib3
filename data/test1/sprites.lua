local dt = 0.1
sprites = {
	-- start graham
	player = {
		id = "player",
		sheet = "gfx/ab.png",
		type = "sprite",
		ppu = 1,
		animations = {
		    {
		        name = "idle", frames = 
				{ 
					{ duration = dt, quads = { { x = 6, y = 11, width = 43, height = 71, anchor = {19, 0}}}}
				}
		    },
	        {
	           name="walk",
	           frames=
	           { 
		           { duration = dt, quads = { { x = 55, y = 10, width = 24, height = 72, anchor = {20, 0}}}},
				   { duration = dt, quads = { { x = 84, y = 11, width = 48, height = 71, anchor = {30, 0}}}},
		           { duration = dt, quads = { { x = 55, y = 10, width = 24, height = 72, anchor = {20, 0}}}},
				   { duration = dt, quads = { { x = 136, y = 11, width = 49, height = 71, anchor = {30, 0}}}}
			   }				
	        },		
	        {
	           name="punch",
	           frames=
	           { 
		           { duration = dt, quads = { { x = 187, y = 11, width = 62, height = 71, anchor = {33, 0}}}},
				   { duration = dt, quads = { { x = 253, y = 11, width = 40, height = 71, anchor = {23, 0}}}},
				   { duration = dt, quads = { { x = 298, y = 12, width = 64, height = 70, anchor = {24, 0}}}}
			   }				
	        },		
	        {
	           name="kick",
	           frames=
	           { 
		            { duration = dt, quads = { { x = 3, y = 87, width = 61, height = 69, anchor = {41, 0}}}},
				    { duration = dt, quads = { { x = 68, y = 87, width = 43, height = 69, anchor = {19, 0}}}},
				    { duration = dt, quads = { { x = 114, y = 88, width = 76, height = 68, anchor = {25, 0}}}},
			   }				
	        },	
		}
	}
	-- end graham
}
