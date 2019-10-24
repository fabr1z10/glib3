factory.hotspot = {}

factory.hotspot.create = function(args)
	assert(args.width, "width")
	assert(args.height, "height")
	assert(args.pos, "pos")
	assert(args.func, "pos")

	local s = {type="rect", width=args.width, height=args.height, offset = {-args.width/2, 0} }
	return {
		pos = { args.pos[1]*engine.tilesize, args.pos[2]*engine.tilesize, 0},
		components = {
			{ type="collider", shape=s, flag=variables.collision.flags.foe, mask = variables.collision.flags.player, tag = variables.collision.tags.hotspot },
			{ type="info", func = args.func }
		}
	}
end

factory.hotspot.response = function (mario, hotspot, sx, sy) 
	print ("entering")
	local hotspot_info = hotspot:getinfo()
	hotspot_info.func(mario,hotspot)
end

