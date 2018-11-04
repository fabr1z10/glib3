items.plant = {}

items.plant.getScript = function(m)
	local s = script:new()
	s.actions = {
		[1] = {type="move", actor = m.tag, by = {0, -48}, speed = 50},
		[2] = {type="delay", actor=m.tag, sec=1, after={1}},
		[3] = {type="move", actor = m.tag, by = {0, 48}, speed = 50, after={2}},
		[4] = {type="delay", actor=m.tag, sec=1, after={3}},
	}
	s.loop = 1
	return s
end

items.plant.create = function(args)
	local t = nextTag()	
	local s = {type="rect", width=16, height=24, offset = {-8, 0} }
	local z = args.z or 1
	local item =  {
		tag = t,
		pos = { args.pos[1], args.pos[2], z },
		components = {
			{ type="gfx", model = "plant", anim="idle" },
			{ type="collider", tag=plantTag, flag=collisionFlags.enemy, mask = collisionFlags.player, shape = s },
		},
	}

	if (args.initscripts ~= nil) then 
		local s = items.plant.getScript(item)
		table.insert(args.initscripts, s)
	end
	return item
end




items.plant.script = function(m) 

end

function mario_plant(mario, coin) 
	print ("Ciao")
end