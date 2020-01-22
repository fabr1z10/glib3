room = {
	scene = {
			{
				tag = "main",
				camera = {
					tag = "maincam",
					type="ortho",
					size = {320, 200},
					bounds = {0, 0, 320, 200},
					viewport = {0, 0, 320, 200}
				},
				children = {
					{
						pos = {160,100,0},
						components = {
							{ type="text", id="HELLO WORLD!", font = "main", size = 8, color = {255,255,255,255}, align = "center", maxwidth = 100000 }
						},

					}
				
				}
			},	
	}
}