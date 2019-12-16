factory.platform = {}

factory.platform.create_poly = function(args)
	assert(args.pos, "pos")	
	return {
		pos = { args.pos[1] * engine.tilesize, args.pos[2] * engine.tilesize, args.z or 0},
		components = {
			{ type = "collider", flag = variables.collision.flags.platform, 
				mask = 1, tag=1, shape = { type="poly", outline  = args.points }}
		}
	}

end

factory.platform.create_line = function(args)
	assert(args.pos, "pos")	
	return {
		pos = { args.pos[1] * engine.tilesize, args.pos[2] * engine.tilesize, 0},
		components = {
			--{ type = "gfx", image = args.img, width = width, height = height, rep = {args.width, args.height}},
			{ type = "collider", flag = variables.collision.flags.platform, mask = 1, tag=1, shape = { type="line", A = args.A, B = args.B }}
		}
	}
end

factory.platform.create_rect = function(args)
	assert(args.width, "width")
	assert(args.height, "height")
	assert(args.img, "img")
	assert(args.pos, "pos")	
	local z = args.z or 0
	local width = engine.tilesize * args.width
	local height = engine.tilesize * args.height
	return {
		pos = { args.pos[1] * engine.tilesize, args.pos[2] * engine.tilesize, z },
		components = {
			{ type = "gfx", image = args.img, width = engine.tilesize, height = engine.tilesize, rep = {args.width, args.height}},
			{ type = "collider", flag = variables.collision.flags.platform, mask = 1, tag=1, shape = { type="rect", width = width, height = height }}
		}
	}
end

factory.platform.make_rect = function(gfx)
	return 
		function(p)
			return factory.platform.create_rect { pos = {p[1], p[2]}, z=1, img = gfx, width=p[3], height=p[4] }
		end	
end