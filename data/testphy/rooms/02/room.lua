room = {
	engines = {
		{ type = "bulletengine", gravity = {0, -20, 0}},
		{
		 	type = "keylistener",
		 	keys = {
		 		{ key = 299, func = function() monkey.endroom() end}
		 	}
		},
	},
	scene = {
			{
				tag = "main",
				camera = {
					tag = "maincam",
					type="perspective",
					pos = {0, 10, 100},
					direction = {0,0,-1}
				},
				children = {
					{
						components = {
							{ type = 'directional.light', ambient = {0, 0, 0}, diffuse = {255, 255, 255}, direction = {0,-1,-0.3} }
						}
					},
					{ 
						tag = 'gnd',
						pos = {0, -56, 0},
						components = {
							{ type = 'rigidbody', mass = 0, restitution=1, shape = { type = 'btbox', half_extents = {50, 50, 50} } },
							{ type = 'gfx', model = 'box1'}
						}							
					},
					{ 
						tag = 'ball',
						pos = {0, 30, 0},
						components = {
							{ type = 'rigidbody', mass = 1, restitution=0.5, shape = { type = 'btsphere', radius = 10 } },
							{ type = 'gfx', model = 'box2' },
							{ type = 'keyinput' },
							{ type = 'c3d' }
						}							
					},

				
				}
			},	
	}
}