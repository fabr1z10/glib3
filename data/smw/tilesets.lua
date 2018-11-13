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
	pipe_orange_down = function (pos, z, height,solid)
		local z1 = z or 0
		data = {5,8,6,8,5,7,6,7}
		for i = 1,height-1 do
			table.insert(data, 5)
			table.insert(data, 6)
			table.insert(data, 6)
			table.insert(data, 6)
		end

		local item = items.backgroundelement.create { pos=pos, width=2, height=height, z=z1, tiledata = data}
		if (solid == true) then
			table.insert(item.components, { type ="collider", shape={type="rect", width = 2*16, height=height*16}, tag=10, flag = collisionFlags.platform, mask = 0 })
		end
		return item

	end,
	pipe_horizontal_green = function (pos, z, width, solid)
		local z1 = z or 0
		data = {7,9,8,9}
		for i = 1,width-2 do
			table.insert(data, 8)
			table.insert(data, 9)
		end
		table.insert(data,7)
		table.insert(data,8)
		table.insert(data,8)
		table.insert(data,8)
		for i = 1,width-1 do
			table.insert(data, 8)
			table.insert(data, 8)
		end
		local item = items.backgroundelement.create { pos=pos, width=width, height=2, z=z1, tiledata = data}
		if (solid == true) then
			table.insert(item.components, { type ="collider", shape={type="rect", width = width*16, height=2*16}, tag=10, flag = collisionFlags.platform, mask = 0 })
		end
		return item

	end,
	incline_pipe_green = function(pos, z)
		local z1 = z or 0 
		local item = items.backgroundelement.create { pos=pos, width=8, height=6, z=z1, tiledata = {
			7, 5, 7, 6, 8, 6, 8, 7, 9, 7, -1, -1, -1,
			-1, 7, 5, 7, 6, 8, 6, 8, 7, 9, 7, -1, -1, 
			-1, -1, 7, 5, 7, 6, 8, 6, 8, 7, 9, 7, -1, 
			-1, -1, -1, 7, 5, 7, 6, 8, 6, 9, 6, 10, 6,
			-1, -1, -1, -1, 7, 5, 8,5, 9,5, 10,5, 
			-1, -1, -1, -1, -1, 8,4, 9,4, -1
		}}
		item.children = {
			{
				components = {
					{ type ="collider", shape={type="line", A={0,0}, B={6*16,6*16}}, tag=10, flag = 32, mask = 0 }
				}
			},
			{
				components = {
					{ type ="collider", shape={type="line", A={6*16,6*16}, B={8*16,4*16}}, tag=10, flag = 32, mask = 0 }
				}
			},
	

		}
		item.components = {}
		return item
	end,
	pipe_purple = function(pos, z, height, solid)
		local z1 = z or 0
		data = {}
		for i = 1,height-1 do
			table.insert(data, 11)
			table.insert(data, 5)
			table.insert(data, 12)
			table.insert(data, 5)
		end
		table.insert(data, 11)
		table.insert(data, 4)
		table.insert(data, 12)
		table.insert(data, 4)

		local item = items.backgroundelement.create { pos=pos, width=2, height=height, z=z1, tiledata = data}
		if (solid == true) then
			table.insert(item.components, { type ="collider", shape={type="rect", width = 2*16, height=height*16}, tag=10, flag = collisionFlags.platform, mask = 0 })
		end
		return item
	end,
	pipe_grey = function(pos, z, height, solid)
		local z1 = z or 0
		data = {}
		for i = 1,height-1 do
			table.insert(data, 13)
			table.insert(data, 5)
			table.insert(data, 14)
			table.insert(data, 5)
		end
		table.insert(data, 13)
		table.insert(data, 4)
		table.insert(data, 14)
		table.insert(data, 4)

		local item = items.backgroundelement.create { pos=pos, width=2, height=height, z=z1, tiledata = data}
		if (solid == true) then
			table.insert(item.components, { type ="collider", shape={type="rect", width = 2*16, height=height*16}, tag=10, flag = collisionFlags.platform, mask = 0 })
		end
		return item
	end,
	pipe_green = function(pos, z, height, solid)
		local z1 = z or 0
		data = {}
		for i = 1,height-1 do
			table.insert(data, 16)
			table.insert(data, 6)
			table.insert(data, 17)
			table.insert(data, 6)
		end
		table.insert(data, 16)
		table.insert(data, 5)
		table.insert(data, 17)
		table.insert(data, 5)

		local item = items.backgroundelement.create { pos=pos, width=2, height=height, z=z1, tiledata = data}
		if (solid == true) then
			table.insert(item.components, { type ="collider", shape={type="rect", width = 2*16, height=height*16}, tag=10, flag = collisionFlags.platform, mask = 0 })
		end
		return item
	end,
	pipe_green_small = function(pos, z, height, solid)
		local z1 = z or 0
		data = {15,6}
		for i = 1,height-2 do
			table.insert(data, 15)
			table.insert(data, 5)
		end
		table.insert(data, 15)
		table.insert(data, 4)

		local item = items.backgroundelement.create { pos=pos, width=1, height=height, z=z1, tiledata = data}
		if (solid == true) then
			table.insert(item.components, { type ="collider", shape={type="rect", width = 16, height=height*16}, tag=10, flag = collisionFlags.platform, mask = 0 })
		end
		return item
	end,
	platform1 = function (pos, z, width, height) 
		local z1 = z or 0	
		data = {}
		for i = 1,height-1 do
			table.insert(data,0)
			table.insert(data,6)
			for j = 1, width-2 do
				table.insert(data,0)
				table.insert(data,1)
			end
			table.insert(data, 1)
			table.insert(data, 6)
		end
		table.insert(data,0)
		table.insert(data,5)
		for j = 1,width-2 do
			table.insert(data, 0)
			table.insert(data, 0)
		end
		table.insert(data,1)
		table.insert(data,5)
		local item = items.backgroundelement.create { pos=pos, width=width, height=height, z=z1, tiledata = data}
		table.insert(item.components, { 
			type ="collider", 
			shape={type="line", A={0, height*16}, B={width*16, height*16}}, 
			tag=10, flag = 32, mask = 0 
		})
		return item
	end,
	platform2 = function (pos, z) 
		local z1 = z or 0
		data = {
			0, 6, 0, 1, 0, 1, 0, 1, 0, 1, 0,1,0,1,0,1,0,1,0,1,0,1,0,1,1,6,
			0, 6, 0, 1, 0, 1, 0, 1, 0, 1, 0,1,0,1,0,1,0,1,0,1,1,4,0,0,1,5,
			0, 6, 0, 1, 0, 1, 0, 1, 0, 1, 0,1,0,1,0,1,0,1,1,4,2,5,-1,-1,
			0, 6, 0, 1, 0, 1, 0, 1, 0, 1, 0,1,0,1,0,1,1,4,2,5,-1,-1,-1,
			0, 6, 0, 1, 0, 1, 0, 1, 0, 1, 0,1,0,1,1,4,2,5,-1,-1,-1,-1,
			0, 6, 0, 1, 0, 1, 0, 1, 0, 1, 0,1,1,4,2,5,-1,-1,-1,-1,-1,
			0, 6, 0, 1, 0, 1, 0, 1, 0,1,1,4,2,5,-1,-1,-1,-1,-1,-1,					
			0,5, 0,0,0,0,0,0,0,0,2,5,-1,-1,-1,-1,-1,-1,-1
		}
		local item = items.backgroundelement.create { pos=pos, width=13, height=8, z=z1, tiledata = data}
		item.children = {
			{
				components = {
					{ type ="collider", shape={type="line", A={0,8*16}, B={5*16,8*16}}, tag=10, flag = 32, mask = 0 }
				}
			},
			{
				components = {
					{ type ="collider", shape={type="line", A={5*16,8*16}, B={11*16,2*16}}, tag=10, flag = 32, mask = 0 }
				}
			},
			{
				components = {
					{ type ="collider", shape={type="line", A={11*16,2*16}, B={13*16,2*16}}, tag=10, flag = 32, mask = 0 }
				}
			},
	

		}
		return item
	end,
	connect_down = function(pos, height, turn) 
		local turn = turn or 1
		local data = {1, 4}
		if (turn == 0) then
			data = {1, 3}
		end
		for i =1, height-2 do
			table.insert(data, 1)
			table.insert(data, 3)
		end
		table.insert(data,1)
		table.insert(data,2)
		local item = items.backgroundelement.create { pos=pos, width=1, height=height, z=0, tiledata = data}
		return item
	end,
	connect_up = function(pos, height, turn) 
		local turn = turn or 1
		local data = {0, 4}
		if (turn == 0) then
			data ={0,3}
		end
		for i =1, height-2 do
			table.insert(data, 0)
			table.insert(data, 3)
		end
		table.insert(data,0)
		table.insert(data,2)
		local item = items.backgroundelement.create { pos=pos, width=1, height=height, z=0, tiledata = data}
		return item
	end,

}

