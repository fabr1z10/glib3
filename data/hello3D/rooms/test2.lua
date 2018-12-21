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
				pos = {0, 0, 0}
			},
			children = {
				{
					pos = {0, 0, 0},
					components = {
						{ type ="light", color={255, 255, 255}}
					}
				},
				{
					pos = {0, 0, 0},
					components = {
						--{ type="gfx3d", shape="plane", width = 10, depth = 10, color = {128, 128, 0, 255}},
						{ type="gfx3d", shape="plane", width = 1000, depth = 1000, image="gfx/1.png"},
						--{ type="collider", shape = {type="rect", width=10, height=10, offset={-5,-5}}, tag=1, flag=1, mask=2}
					}
				},
				{
					pos = {0, 0, 0.1},
					components = {
						{ type="gfx3d", shape="plane", width = 1, depth = 2, color = {0, 0, 128, 255}},
						{ type="collider", shape = {type="rect", width=1, height=2, offset={-0.5,-1}}, tag=2, flag=2, mask=1},
						{ type="raycastcontroller" },
						{ type="follow3d", cam="maincam", distance = 10, elevation = 3}
					}

				}
			}
		}		
	}
}
