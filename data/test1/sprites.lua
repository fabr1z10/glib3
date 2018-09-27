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
	        {
	           name="cr",
	           frames=
	           { 
		            { duration = 2*dt, quads = { { x = 28, y = 162, width = 42, height = 74, anchor = {21, 0}}}},
				   { duration = 3*dt, quads = { { x = 84, y = 11, width = 48, height = 71, anchor = {18, 0}}}},
			   }				
	        },	
		
		}
	},
	character_1 = {
		id = "character_1",
		sheet = "gfx/enemies.png",
		type = "sprite",
		ppu = 1,
		animations = {
		    {
		        name = "idle", frames = 
				{ 
					{ duration = dt, quads = { { x = 57, y = 2, width = 18, height = 62, anchor = {9, 0}}}}
				}
		    },
	        {
	           name="walk",
	           frames=
	           { 
		           { duration = dt, quads = { { x = 5, y = 2, width = 24, height = 62, anchor = {12, 0}}}},
				   { duration = dt, quads = { { x = 31, y = 1, width = 24, height = 63, anchor = {12, 0}}}},
		           { duration = dt, quads = { { x = 57, y = 2, width = 18, height = 62, anchor = {9, 0}}}},
				   { duration = dt, quads = { { x = 77, y = 1, width = 20, height = 63, anchor = {10, 0}}}}
			   }				
	        },	
		    {
		        name = "body", frames = 
				{ 
					{ duration = dt, quads = { { x = 100, y = 1, width = 20, height = 49, anchor = {10, 0}}}}
				}
		    },	
		    {
		        name = "head", frames = 
				{ 
					{ duration = dt, quads = { { x = 99, y = 50, width = 10, height = 15, anchor = {5, 0}}}}
				}
		    },
		    {
		        name = "legs", frames = 
				{ 
					{ duration = dt, quads = { { x = 112, y = 52, width = 11, height = 29, anchor = {6, 0}}}}
				}
		    },
		}
	},
	piece1 = {
		id="piece1",
		sheet = "gfx/ab.png",
		type = "sprite",
		ppu = 1,
		animations = {
		    {
		        name = "default", frames = 
				{ 
					{ duration = dt, quads = { { x = 5, y = 161, width = 12, height = 5, anchor = {6, 2}}}}
				}
		    },
		}
	},
	expl1 = {
		id="expl1",
		sheet = "gfx/enemies.png",
		type = "sprite",
		ppu = 1,
		animations = {
		    {
		        name = "default", frames = 
				{ 
					{ duration = dt, quads = { { x = 123, y = 0, width = 44, height = 44, anchor = {22, 0}}}},
					{ duration = dt, quads = { { x = 170, y = 1, width = 48, height = 48, anchor = {24, 0}}}},
					{ duration = dt, quads = { { x = 223, y = 2, width = 53, height = 52, anchor = {26, 0}}}},
					{ duration = dt, quads = { { x = 280, y = 1, width = 55, height = 47, anchor = {27, 0}}}},
					{ duration = dt, quads = { { x = 339, y = 2, width = 57, height = 40, anchor = {28, 0}}}},
					{ duration = dt, quads = { { x = 401, y = 3, width = 57, height = 33, anchor = {28, 0}}}},
					{ duration = dt, quads = { { x = 399, y = 39, width = 57, height = 22, anchor = {28, 0}}}}
				}
		    },
			{
		        name = "stop", frames = 
				{ 
					{ duration = dt, quads = { { x = 399, y = 39, width = 57, height = 22, anchor = {28, 0}}}}
				}

			}
		}
	},

	-- end graham
}
