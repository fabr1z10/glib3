items.spawn = {}

-- Spawns one or more entities when player hits it
items.spawn.create = function(args)



	local t = nextTag()	
	local s = {type="rect", width=1, height=256 }
	return {
		tag = t,
		pos = { args.pos[1], args.pos[2], 0},
		components = {
			{ type="collider", tag=spawnTag, flag=collisionFlags.enemy, mask = collisionFlags.player, shape = s },
			{ type="info", items = args.items }
		},
	}
end



function mario_spawn(mario, spawn, sx, sy)
	if (sx < 0) then
		local info = spawn:getinfo()
		local a = monkey.getEntity("restofscene")
		print ("CANE")
		for k, v in ipairs(info.items) do
			print ("CIAO")
			CreateItem(v)
		end
	end
end