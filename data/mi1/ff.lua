mi = {}
mi.script = {}
mi.data = {
	cook_text_color = {85, 255, 255, 255}

}

mi.rooms = {
	scummbar = {
		door_out = {65, 15},
		door_kitchen = {588, 14},
	},
	kitchen = {
		door = {36, 16}
	},
	village1 = {
		door = {715, 13}
	},
	lookout = {
		to_village = {250, 0},
		to_map = {320, 50}
	}

}


mi.addStorekeeper = function()
end

mi.script.open_door = function(args)
    glib.assert(args.door, 'door')
    glib.assert(args.value, 'value')
    local d = engine.items[args.door]
    if not d then Error('unknown item ' .. args.door, 1) end
    return {
        { type = action.animate, args = { tag = args.door, anim = args.value and 'open' or 'close' }},
        { type = action.callfunc, args = { func = function()
            variables[d.var] = args.value and 1 or 0
        end }}
    }    
end



make_door = function(args)

	assert (args.tag, "tag")
	assert (args.pos, "pos")
	assert (args.size, "size")
	assert (args.walk_to, "walk_to")
	assert (args.dir, "dir")
	assert (args.model, "model")
	assert (args.var, "var - the controlling variable")
	
	assert (args.go_to, 'go_to')
	assert (args.go_to.room, 'go_to.room')
	assert (args.go_to.pos, 'go_to.pos')
	assert (args.go_to.dir, 'go_to.dir')

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
 		var = args.var,
		anim = function() return variables[args.var] == 0 and 'close' or 'open' end,
		actions = {
			walk = args.walk or function() 
				if variables[args.var] == 1 then
					return scumm.script.changeroom { 
						room = args.go_to.room,
						pos = args.go_to.pos,
						dir = args.go_to.dir
					}
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