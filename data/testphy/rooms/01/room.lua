room = {
	engines = {
		{ type = "bulletengine", gravity = {0, -10, 0}},

	},
	scene = {
			{
				tag = "main",
				camera = {
					tag = "maincam",
					type="perspective",
					pos = {0, 0, 200},
					direction = {0,0,-1}
				},
				children = {
					{ 
						tag = 'gnd',
						pos = {0, -56, 0},
						components = {
							{ type = 'rigidbody', mass = 0, shape = { type = 'btbox', half_extents = {50, 50, 50} } },
							{ type = 'gfx', model = 'box1'}
						}							
					},
					{ 
						tag = 'ball',
						pos = {0, 0, 0},
						components = {
							{ type = 'rigidbody', mass = 1, shape = { type = 'btsphere', radius = 1 } }
						}							
					},

					-- { type = "text", text = "HELLO WORLD!", font = "main", size = 8, color = {255, 255, 255, 255}, align = "center", pos = {160,100,0}},
					-- { type = "text", text = "Bottom left", font = "main", size = 8, color = {255, 255, 255, 255}, align = "bottomleft", pos = {0,0,0} },					
					-- { type = "text", text = "Bottom right", font = "main", size = 8, color = {255, 255, 255, 255}, align = "bottomright", pos = {320,0,0} },					
					-- { type = "text", text = "Top left", font = "main", size = 8, color = {255, 255, 255, 255}, align = "topleft", pos = {0,200,0} },					
					-- { type = "text", text = "Top right", font = "main", size = 8, color = {255, 255, 255, 255}, align = "topright", pos = {320,200,0} },					
					-- { 
					-- 	pos = {152, 72, 0},
					--  	components = {
					--  		{ type = "gfx", image="block1.png"}
					--  	}
					-- }
				
				}
			},	
	}
}