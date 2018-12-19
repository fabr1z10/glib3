room =  {
	engines = {
		{ type = "scheduler" }
	},
	scene = {
		{
			tag = "main",
			camera = {
				tag = "maincam",
				type="perspective",
				pos = {0, 2, 3}
			},
			children = {
				{
					pos = {0, 0, -5},
					components = {
						{ type="gfx3d", shape="plane", width = 10, depth = 10}
					}
				}
			}
		}		
	}
}
