-- room for multiplayer with dynamic objects

function scumm.factory.dynamic_room (args) 

	local p = scumm.factory.room_base(args)

	-- load dynamic stuff
	local di = variables.dynamic_items[args.id]
	if di then
		print ("shflidsfslk")
		local it = {}
		for id, item in pairs(di) do
			local tag = (id == variables.current_player) and 'player' or nil
			local follow = (id == variables.current_player) and true or nil
			local obj = scumm.factory.object { id = id, params = { pos = item.pos, dir = item.dir, tag = tag, follow=follow }}
			table.insert(it, obj)
			local parent = item.wa 
			if not parent then
				parent = (args.walkareas and args.walkareas[1] or 'main')
			end
			p:add(parent, { obj })
		end
		--p:add('main', it)
	

	end
	return p

end
