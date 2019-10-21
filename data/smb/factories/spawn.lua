factory.spawn = {}

factory.spawn.create = function(args)
	local s = {type="rect", width=args.width, height=args.height }
	return {
		tag = t,
		pos = { args.pos[1]*engine.tilesize, args.pos[2]*engine.tilesize, 0},
		components = {
			{ type="collider", tag=variables.collision.tags.spawn, flag=variables.collision.flags.foe, mask =variables.collision.flags.player, shape = s },
			{ type="info", func = args.func, args = args.args, use_once = args.use_once }
		},
	}
end



factory.spawn.response = function (mario, spawn, sx, sy) 
	if (sx < 0) then
		local info = spawn:getinfo()
		if (info.use_once) then
			spawn:remove()
		end
		local a = monkey.getEntity("main")
		monkey.addEntity (info.func(info.args), a)
	end
end