factory.tiled = {}

factory.tiled.create = function(args)
	assert(args.width, "width")
	assert(args.height, "height")
	assert(args.tiledata, "tiledata")
	assert(args.img, "img")
	assert(args.pos, "pos")	
	
	local z = args.z or 0
	local width = engine.tilesize * args.width
	local height = engine.tilesize * args.height
	
	local components = {
		{ type = "gfx", img = args.img, width = args.width, height = args.height, tiledata = args.tiledata, sheetsize={16,16}, size=engine.tilesize },
	}
	if (args.collide) then
		table.insert(components, { type = "collider", flag = variables.collision.flags.platform, mask = 1, tag=1, shape = { type="rect", width = args.width*engine.tilesize, height = 
		args.height*engine.tilesize }})
	end

	return {
		pos = { args.pos[1] * engine.tilesize, args.pos[2] * engine.tilesize, z },
		components = components
	}
end

factory.tiled.create_from = function(args) 
	assert(args.pos, "pos")	
	assert(args.template, "template")	
	local t = variables.data.templates[args.template]

	local z = args.z or 0
	local width = engine.tilesize * t.width
	local height = engine.tilesize * t.height
	
	local components = {
		{ 
			type = "gfx", 
			img = variables.data.sheets[t.sheet].img, 
			width = t.width,
			height = t.height,
			tiledata = t.data,
			sheetsize=variables.data.sheets[t.sheet].tilesize, 
			size=engine.tilesize 
		},
	}
	if (args.collide) then
		table.insert(components, { type = "collider", flag = variables.collision.flags.platform, mask = 1, tag=1, shape = { type="rect", width = args.width*engine.tilesize, height = 
		args.height*engine.tilesize }})
	end

	return {
		pos = { args.pos[1] * engine.tilesize, args.pos[2] * engine.tilesize, z },
		components = components
	}
end