factory.tiled = {}

-- create a tiled rectangle from a template
-- a template is a table with the following data:
-- 		width			: the rectangle width
--		height			: the rectangle height
-- 		sheet 			: a link to the spritesheet
--      data			: an array with the tile data, this should contain a x, y coordinate for each tile, -1 for no tile
factory.tiled.create = function(args) 
	assert(args.pos, "pos")	
	assert(args.template, "template")	
	local t = variables.data.templates[args.template]

	local z = args.z or 0
	local width = engine.tilesize * t.width
	local height = engine.tilesize * t.height

	-- optional params
	local repx = args.repx or 1
	local repy = args.repy or 1

	local components = {
		{ 
			type = "gfx", 
			img = variables.data.sheets[t.sheet].img, 
			width = t.width,
			height = t.height,
			tiledata = t.data,
			sheetsize=variables.data.sheets[t.sheet].tilesize, 
			size=engine.tilesize,
			delta=args.delta,
			repx = repx,
			repy = repy
		},
	}
	if (args.collide) then
		table.insert(components, { type = "collider", flag = variables.collision.flags.platform, mask = 1, tag=1, shape = { type="rect", width = width*repx, height = height*repy }})
	end

	return {
		pos = { args.pos[1] * engine.tilesize, args.pos[2] * engine.tilesize, z },
		components = components
	}
end

factory.tiled.make = function(temp) 
	return function(p) return factory.tiled.create { pos = p, z=-0.1,template = temp } end 
end


factory.tiled.create_from_data = function(args) 
	assert(args.pos, "pos")
	assert(args.width,"width")	
	assert(args.height,"height")	
	assert(args.data,"data")	

	local z = args.z or 0
	local width = 8 * args.width
	local height = 8 * args.height
	local sheet = variables.data.sheets[args.sheet]
	-- optional params
	local repx = args.repx or 1
	local repy = args.repy or 1

	local components = {
		{ 
			type = "gfx", 
			img = "tiles.png",
			width = args.width,
			height = args.height,
			tiledata = args.data,
			sheetsize= {64, 64},
			size=8,
			delta=args.delta,
			repx = repx,
			repy = repy
		},
	}
	if (args.collide) then
		table.insert(components, { type = "collider", flag = args.collide[3], mask = 1, 
			tag=1, shape = { type="line", A = {0,height}, B={args.collide[1]*8, height}}})
	elseif (args.collide_rect) then 
		table.insert(components, { type = "collider", flag = args.collide_rect[3], mask = 1, 
			tag=1, shape = { type="rect", width = args.collide_rect[1]*8, height=args.collide_rect[2]*8, offset = {0, args.collide_rect[4]*8}}})
	end

	return {
		pos = { args.pos[1] * 8, args.pos[2] * 8, z },
		components = components
	}
end

factory.tiled.make_wall = function(args)
	assert (args.height, "height")
	assert(args.pos, "pos")
	assert(args.td, "td")
	assert(args.right, "right")

	local data = {}
	local i = 0
	local w = (args.right == 0) and 3 or 2
	while (i< args.height) do
		
		table.insert(data, args.data[1])		
		table.insert(data, args.data[2])		
		table.insert(data, args.data[3])		
		table.insert(data, args.data[4])		
		if (args.right == 0) then
			table.insert(data, args.td.shade_right[1])
			table.insert(data, args.td.shade_right[2])
		end
		table.insert(data, args.data[5])		
		table.insert(data, args.data[6])		
		table.insert(data, args.data[7])		
		table.insert(data, args.data[8])		
		if (args.right == 0) then
			table.insert(data, args.td.shade_right[1])
			table.insert(data, args.td.shade_right[2])
		end
		i = i+ 2
	end
	--print ("LEN = " .. tostring(#data))
	return factory.tiled.create_from_data {
		pos={args.pos[1], args.pos[2]}, z = args.z or 0, width = w, height=args.height, data = data,
		collide_rect={2, args.height*2, 2, 0}
	}
end	



factory.tiled.make_platform = function(args)
	assert(args.width, "width")
	assert(args.left, "left")
	assert(args.right, "right")
	assert(args.td, "td")
	assert(args.pos, "pos")

	local collide = args.collide or 1

		local data = {}
		local w = (args.right == 0) and args.width+1 or args.width
		-- LINE BELOW

		for i = 1,args.width do
			print (i)
			print (args.width)
			if (i == 1) then 
				if (args.left == 1) then
					table.insert(data, args.td.shade_below_right[1])
					table.insert(data, args.td.shade_below_right[2])
				else
					table.insert(data, args.td.shade_below_start[1])
					table.insert(data, args.td.shade_below_start[2])
				end
			else
				table.insert(data, args.td.shade_below[1])
				table.insert(data, args.td.shade_below[2])
			end
		end
		if (args.right == 0) then
			table.insert (data, args.td.shade_corner[1])
			table.insert (data, args.td.shade_corner[2])
		end
		-- LINE ABOVE
		for i = 1,args.width do
			table.insert(data, args.td.full[1])
			table.insert(data, args.td.full[2])
		end
		if (args.right == 0) then
			table.insert (data, args.td.shade_right_start[1])
			table.insert (data, args.td.shade_right_start[2])
		end

		for _,c in ipairs(data) do
			print (tostring(c) .. ",")
		end

		

		local c = (collide == 1) and {args.width, 1, 32, 1} or nil
		return factory.tiled.create_from_data {
			pos={args.pos[1], args.pos[2]-1}, z = args.z or 0, width = w, height=2, data = data,
			collide_rect=c
		}
end