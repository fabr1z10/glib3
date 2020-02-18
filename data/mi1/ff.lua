mi = {}

mi.addStorekeeper = function()
end
make_door = function(args)

	assert (args.tag, "tag")
	assert (args.pos, "pos")
	assert (args.size, "size")
	assert (args.walk_to, "walk_to")
	assert (args.dir, "dir")
	assert (args.model, "model")
	assert (args.var, "var - the controlling variable")
	assert (args.room, 'room')

	local cv = variables[args.var]
	if not cv then
		error("don't know variable: " .. args.var, 1)
	end
	local item = {
		type = 'object',
		tag = args.tag,
		model = args.model,
 		pos = args.pos,
 		hotspot = {
 			text = strings.objects.door,
 			size = args.size,
 			walk_to = args.walk_to,
 			dir = args.dir
 		},
		anim = function() return variables[args.var] == 0 and 'close' or 'open' end,
		actions = {
			walk = args.walk or function() 
				if variables[args.var] == 1 then
					return { type = action.change_room, args = {room = args.room }}
				else
					return nil
				end
			end,
			open = args.open or function()
				variables[args.var] = 1
				return { type = action.animate, args = {tag=args.tag, anim="open"}}
			end,
			close = args.close or function()
				variables[args.var] = 0
				return { type = action.animate, args = {tag=args.tag, anim="close"}}
			end,
		}
	}
	return item
end