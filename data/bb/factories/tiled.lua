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
			tag=1, shape = { type="rect", width = args.collide[1]*8, height = args.collide[2]*8 }})
	end

	return {
		pos = { args.pos[1] * 8, args.pos[2] * 8, z },
		components = components
	}
end