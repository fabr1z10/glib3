scumm.factory.door = function(args)
	assert (args.id, "id")
	assert (args.pos, "pos")
	assert (args.size, "size")
	assert (args.walk_to, "walk_to")
	assert (args.dir, "dir")
	assert (args.model, "model")
	--assert (args.nextroom, "nextroom")
	assert (args.variable, "variable")
	--local tag = args.name
	local offset = args.offset

	items[args.id] = {
		tag = args.id,
		pos = args.pos,
		hotspot = {
			size = args.size,
			offset = offset,
			walk_to = args.walk_to,
			dir = args.dir,
			text = strings.objects.door
		},
		model = args.model,
		variable = args.variable,
		anim = function() 
			if (variables[args.variable] == 0) then
				return "close"
			else
				return "open"
			end
		end,
		actions = {
			walk = args.walk or function() 
				if (variables[args.variable] == 1) then
					return { type = action.change_room, args = {room =args.nextroom }}
				else
					return nil
				end
			end,
			open = args.open or function()
				variables[args.variable] = 1
				local s = { type = action.animate, args = {actor=args.id, anim="open"}}
				return s
			end,
			close = args.close or function()
				variables[args.variable] = 0
				local s = { type = action.animate, args = {actor=args.id, anim="close"}}
				return s
			end,
		}
	}
end
