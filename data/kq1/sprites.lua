local dt = 0.1
sprites = {
	-- start graham
	graham = {
		id = "graham",
		sheet = "gfx/sprites.png",
		type = "sprite",
		ppu = 1,
		animations = {
		    {
		        name = "idle_right", frames = 
				{ 
					{ duration = dt, quads = { { x = 106, y = 1, width = 12, height = 32, anchor = {6, 0}}}}
				}
		    },
	        {
	           name="idle_back",
	           frames=
	           { 
		           { duration = dt, quads = { { x = 106, y = 35, width = 10, height = 32, anchor = {5, 0}}}}
			   }				
	        },
			{
	           name="idle_front",
	           frames=
	           { 
		           { duration = dt, quads = { { x = 106, y = 69, width = 10, height = 31, anchor = {5, 0}}}}
			   }				
	        },	
	        {
	           name="walk_right",
	           frames=
	           { 
		           { duration = dt, quads = { { x = 106, y = 1, width = 12, height = 32, anchor = {6, 0}}}},
				   { duration = dt, quads = { { x = 119, y = 1, width = 10, height = 32, anchor = {4, 0}}}},
				   { duration = dt, quads = { { x = 130, y = 2, width = 12, height = 31, anchor = {6, 0}}}},
				   { duration = dt, quads = { { x = 143, y = 2, width = 12, height = 31, anchor = {6, 0}}}},
				   { duration = dt, quads = { { x = 156, y = 1, width = 10, height = 32, anchor = {4, 0}}}},
				   { duration = dt, quads = { { x = 167, y = 2, width = 12, height = 31, anchor = {6, 0}}}}
			   }				
	        },		
	        {
	           name="walk_back",
	           frames=
	           { 
		           { duration = dt, quads = { { x = 106, y = 35, width = 10, height = 32, anchor = {5, 0}}}},
				   { duration = dt, quads = { { x = 118, y = 36, width = 10, height = 31, anchor = {5, 0}}}},
				   { duration = dt, quads = { { x = 130, y = 36, width = 10, height = 31, anchor = {5, 0}}}},
				   { duration = dt, quads = { { x = 142, y = 35, width = 10, height = 32, anchor = {5, 0}}}},
				   { duration = dt, quads = { { x = 154, y = 36, width = 10, height = 31, anchor = {5, 0}}}},
				   { duration = dt, quads = { { x = 166, y = 36, width = 10, height = 31, anchor = {5, 0}}}}
			   }				
	        },	
			{
	           name="walk_front",
	           frames=
	           { 
		           { duration = dt, quads = { { x = 106, y = 69, width = 10, height = 31, anchor = {5, 0}}}},
				   { duration = dt, quads = { { x = 118, y = 68, width = 10, height = 32, anchor = {5, 0}}}},
				   { duration = dt, quads = { { x = 130, y = 69, width = 10, height = 31, anchor = {5, 0}}}},
				   { duration = dt, quads = { { x = 142, y = 69, width = 10, height = 31, anchor = {5, 0}}}},
				   { duration = dt, quads = { { x = 154, y = 68, width = 10, height = 32, anchor = {5, 0}}}},
				   { duration = dt, quads = { { x = 166, y = 69, width = 10, height = 31, anchor = {5, 0}}}}
			   }				
	        },
	        {
	           name="swim_right",
	           frames=
	           { 
		           { duration = dt, quads = { { x = 223, y = 1, width = 26, height = 11, anchor = {10, 0}}}},
				   { duration = dt, quads = { { x = 223, y = 13, width = 22, height = 11, anchor = {10, 0}}}},
				   { duration = dt, quads = { { x = 223, y = 25, width = 24, height = 10, anchor = {10, 0}}}},
				   { duration = dt, quads = { { x = 223, y = 36, width = 24, height = 10, anchor = {8, 0}}}},
			   }				
	        },		
	        {
	           name="swim_back",
	           frames=
	           { 
		            { duration = dt, quads = { { x = 247, y = 81, width = 8, height = 15, anchor = {4, 0}}}},
				    { duration = dt, quads = { { x = 223, y = 97, width = 8, height = 15, anchor = {4, 0}}}},
				    { duration = dt, quads = { { x = 233, y = 97, width = 8, height = 15, anchor = {4, 0}}}},
				    { duration = dt, quads = { { x = 242, y = 97, width = 12, height = 13, anchor = {6, 0}}}},
				    { duration = dt, quads = { { x = 223, y = 113, width = 8, height = 15, anchor = {6, 0}}}},
				    { duration = dt, quads = { { x = 233, y = 113, width = 8, height = 15, anchor = {6, 0}}}},
				    { duration = dt, quads = { { x = 243, y = 113, width = 8, height = 15, anchor = {6, 0}}}},
					{ duration = dt, quads = { { x = 223, y = 129, width = 12, height = 13, anchor = {8, 0}}}}
			   }				
	        },	
			{
	           name="swim_front",
	           frames=
	           { 
		            { duration = dt, quads = { { x = 223, y = 47, width = 8, height = 14, anchor = {4, 0}}}},
				    { duration = dt, quads = { { x = 233, y = 47, width = 8, height = 14, anchor = {4, 0}}}},
				    { duration = dt, quads = { { x = 243, y = 47, width = 8, height = 15, anchor = {4, 0}}}},
				    { duration = dt, quads = { { x = 223, y = 64, width = 12, height = 15, anchor = {6, 0}}}},
				    { duration = dt, quads = { { x = 237, y = 64, width = 8, height = 14, anchor = {6, 0}}}},
				    { duration = dt, quads = { { x = 247, y = 64, width = 8, height = 14, anchor = {6, 0}}}},
					{ duration = dt, quads = { { x = 223, y = 81, width = 8, height = 15, anchor = {6, 0}}}},
					{ duration = dt, quads = { { x = 233, y = 81, width = 12, height = 15, anchor = {8, 0}}}},
			   }				
	        },
			{
	           name="drown",
	           frames=
	           { 
		            { duration = dt, quads = { { x = 182, y = 2, width = 36, height = 10, anchor = {16, 0}}}},
				    { duration = dt, quads = { { x = 182, y = 13, width = 38, height = 15, anchor = {18, 0}}}},
				    { duration = dt, quads = { { x = 182, y = 29, width = 38, height = 15, anchor = {18, 0}}}},
				    { duration = dt, quads = { { x = 182, y = 45, width = 30, height = 12, anchor = {16, 0}}}},
				    { duration = dt, quads = { { x = 182, y = 58, width = 32, height = 10, anchor = {16, 0}}}},
				    { duration = dt, quads = { { x = 182, y = 69, width = 38, height = 12, anchor = {18, 0}}}},
				    { duration = dt, quads = { { x = 182, y = 82, width = 32, height = 12, anchor = {16, 0}}}},
					{ duration = dt, quads = { { x = 182, y = 95, width = 34, height = 11, anchor = {16, 0}}}},
					{ duration = dt, quads = { { x = 182, y = 107, width = 38, height = 11, anchor = {16, 0}}}},
			   }				
	        },	
		}
	}
	-- end graham
}
