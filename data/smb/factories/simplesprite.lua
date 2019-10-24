factory.simplesprite = {}

factory.simplesprite.create = function(args)
	--local t = nextTag()	
	local z = args.z or 0
	return {
		type = "sprite",
		tag = args.tag,
		model = args.model,
		pos = { args.pos[1]*engine.tilesize, args.pos[2]*engine.tilesize, z },
	}
end

