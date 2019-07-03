-- 1st person engine
room =  {
	engines = {
		{ type = "scheduler" },
		{ 
			type = "collision", 
			size = {128, 128}, 
			response = {
				{ tag = {1, 2}, onenter=function(e,f) 

						print ("CIAO")
				 end}
			}
		}
	},
	scene = {
		{
			tag = "main",
			camera = {
				tag = "maincam",
				type="perspective",
				pos = {0, 0, 100}
			},
			children = {
				{ pos = {0, 0, 0}, components = { { type ="light", class="ambient", color ={32, 32, 32}}}},
				{ pos = {0,0,0}, components = {{type="light", class="directional", color={255, 255, 255}, dir = {1, 0, 1}}}},
				{
					tag = "heightmap",
					type = "heightmap",
					pos = {0, 0, 0},
					image="gfx/heightmap3.png", 
					size = {20, 20}, 
					height_bounds = {-20, 400},
					texture = "gfx/grass.jpg"
				},		
				-- 		{ type="road", n = 1, image = "gfx/r1.jpg", points = {
				-- 			{ id = 0, pos = { 1,1,0 }, width = 10 },
				-- 			{ id = 1, pos = { 1,100, 50}, width = 10 },
				-- 			{ id = 2, pos = {21, 120, 1}, width=10},
				-- 			{id=3, pos = {80, 50, 0}, width = 10 },
				-- 			{id=4, pos ={40, -20, 0}, width = 10},
				-- 		}, edges = {
				-- 			{ from = 0, to = 1, angles = {90, 90}},
				-- 			{ from = 1, to = 2, angles = {90, 0}},
				-- 			{ from = 2, to = 3, angles ={0,90}},
				-- 			{ from = 3, to = 4, angles = {90,0}},
				-- 			{ from = 4, to = 0, angles = {0, 90}}
				-- 		} },
				-- 		--{ type="collider", shape = {type="rect", width=10, height=10, offset={-5,-5}}, tag=1, flag=1, mask=2}
				-- 	}
				-- },
				{
					pos = {2, 2, 0},
					components = {
						--{ type="gfx3d", shape="plane", width = 10, depth = 10, color = {128, 128, 0, 255}},
						{ type="gfx3d", shape="plane", width = 20, depth = 20, offset={-10,0}, image="gfx/tree.png", plane="xz"},
						{ type="billboard", cam="maincam"}
					}
				},
				{
					pos = {0, 0, 0.1},
					components = {
						{ type="gfx3d", shape="plane", width = 1, depth = 2, color = {0, 0, 128, 255}},
						{ type="collider", shape = {type="rect", width=1, height=2, offset={-0.5,-1}}, tag=2, flag=2, mask=1},
						{ type="raycastcontroller", heightmap = "heightmap" },
						{ type="follow3d", cam="maincam", distance = 10, elevation = 3}
					}

				}
			}
		}		
	}
}
