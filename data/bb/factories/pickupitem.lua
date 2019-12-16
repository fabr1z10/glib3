factory.pickupitem = {}

factory.pickupitem.response = function (player, item, sx, sy) 
	local info = item:getinfo()
	info.callback(player,item)
end

factory.pickupitem.create = function(args)
	--local t = nextTag()	
	local s = { type="rect", width=args.width, height=args.height }
	local z = args.z or 1
	return {
		type = "sprite",
		model = args.model,
		pos = { args.pos[1]*engine.tilesize, args.pos[2]*engine.tilesize, z },
		components = {
			{ type="info", callback = args.callback },
			{ type="collider", tag=variables.collision.tags.pickupitem, flag = variables.collision.flags.foe, mask = variables.collision.flags.player, shape = s },
		},
	}
end

