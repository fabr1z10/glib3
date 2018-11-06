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
	end
}

