items.spawn = {}

items.spawn.create = function(args)
	local t = nextTag()	
	local s = {type="rect", width=1, height=256 }
	return {
		tag = t,
		pos = { args.pos[1], args.pos[2], 0},
		components = {
			{ type="collider", tag=spawnTag, flag=1, shape = s },
			{ type="info", func = args.func, args = args.args }
		},
	}
end



function mario_spawn(mario, spawn, sx, sy)
	if (sx < 0) then
		local info = spawn:getinfo()
		print ("CANE")
		local a = monkey.getEntity("restofscene")
		monkey.addEntity (info.func(info.args), a)
	end
end