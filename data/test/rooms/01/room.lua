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
					{ type = "text", text = "HELLO WORLD!", font = "main", size = 8, color = {255, 255, 255, 255}, align = "center", pos = {160,100,0}},
					{ type = "text", text = "Bottom left", font = "main", size = 8, color = {255, 255, 255, 255}, align = "bottomleft", pos = {0,0,0} },					
					{ type = "text", text = "Bottom right", font = "main", size = 8, color = {255, 255, 255, 255}, align = "bottomright", pos = {320,0,0} },					
					{ type = "text", text = "Top left", font = "main", size = 8, color = {255, 255, 255, 255}, align = "topleft", pos = {0,200,0} },					
					{ type = "text", text = "Top right", font = "main", size = 8, color = {255, 255, 255, 255}, align = "topright", pos = {320,200,0} },					
					{ 
						pos = {152, 72, 0},
					 	components = {
					 		{ type = "gfx", image="block1.png"}
					 	}
					}
				
				}
			},	
	}
}