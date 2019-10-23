factory.coin = {}


factory.coin.response = function (mario, coin, sx, sy) 
	coin:remove()
end

factory.coin.create = function(args)
	--local t = nextTag()	
	local s = {type="rect", width=16, height=16 }
	local z = args.z or 1
	return {
		type = "sprite",
		model = args.model,
		pos = { args.pos[1]*engine.tilesize, args.pos[2]*engine.tilesize, z },
		components = {
			--{ type="gfx", model = args.model},
			{ type="collider", tag=variables.collision.tags.coin, flag = variables.collision.flags.foe, mask = variables.collision.flags.player, shape = s },
		},
	}
end

