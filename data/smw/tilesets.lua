tilesets = {
	ramp1 = function(pos, z)
		local z1 = z or 0
		return items.backgroundelement.create { pos=pos, width=9, height=6, z=z1, tiledata = {
			-1, -1, 2, 2, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 3, 1,
			-1, 2, 2, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 3, 1, -1,
			1,1,0,1,0,1,0,1,0,1,0,1,3,1,-1,-1,
			1,0,2,0,0,1,0,1,0,1,3,1,-1,-1,-1,
			-1,1,0,2,0,0,1,3,1,-1,-1,-1,-1,
			-1,-1,1,0,2,1,-1,-1,-1,-1,-1
		}}
	end,
	incline_pipe_green = function(pos, z)
		local z1 = z or 0 
		return items.backgroundelement.create { pos=pos, width=8, height=6, z=z1, tiledata = {
			7, 5, 7, 6, 8, 6, 8, 7, 9, 7, -1, -1, -1,
			-1, 7, 5, 7, 6, 8, 6, 8, 7, 9, 7, -1, -1, 
			-1, -1, 7, 5, 7, 6, 8, 6, 8, 7, 9, 7, -1, 
			-1, -1, -1, 7, 5, 7, 6, 8, 6, 9, 6, 10, 6,
			-1, -1, -1, -1, 7, 5, 8,5, 9,5, 10,5, 
			-1, -1, -1, -1, -1, 8,4, 9,4, -1
		}}
	end

}

