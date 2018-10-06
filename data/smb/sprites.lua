local dt = 0.1
sprites = {
	-- start graham
	mario = {
		id = "mario",
		sheet = "gfx/smb1.png",
		type = "sprite",
		ppu = 1,
		animations = {
		    {
		        name = "idle", frames = 
				{ 
					{ duration = dt, quads = { { x = 0, y = 0, width = 16, height = 16, anchor = {8, 0}}}}
				}
		    },
	        {
	           name="walk",
	           frames=
	           { 
					{ duration = dt, quads = { { x = 16, y = 0, width = 16, height = 16, anchor = {8, 0}}}},
					{ duration = dt, quads = { { x = 32, y = 0, width = 16, height = 16, anchor = {8, 0}}}},
					{ duration = dt, quads = { { x = 48, y = 0, width = 16, height = 16, anchor = {8, 0}}}},
			   }				
	        },		
	        {
	           name="jump",
	           frames=
	           { 
					{ duration = dt, quads = { { x = 80, y = 0, width = 16, height = 16, anchor = {8, 0}}}},
			   }				
	        },				
		}
	},
	basicbrick = {
		id = "basicbrick",
		sheet = "gfx/smb1.png",
		type = "sprite",
		ppu = 1,
		animations = {
		    {
		        name = "idle", frames = 
				{ 
					{ duration = dt, quads = { { x = 240, y = 0, width = 16, height = 16, anchor = {0, 0}}}}
				}
		    }		
		}
	},
	

}
