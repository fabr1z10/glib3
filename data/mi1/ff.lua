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
		door = {715, 13},
		to_lookout = {11, 70},
		to_village2 = {1008, 34}
	},
	village2 = {
		to_village1 = {436, 35},
		to_village3 = {160, 59}
	},
	village3 = {
		to_village2 = {762, 16},
		to_alley = {605, 55},
		to_shop = {668, 22},
		to_church = {543, 39}
	},
	lookout = {
		to_village = {250, 0},
		to_map = {320, 50}
	},
	meleemap = {
		lookout = {75, 79},
		clearing = {136, 113},
		fork = {74, 112}
	},
	clearing = {
		to_map = {320,10}
	},
	alley = {
		to_village3 = {35, 18}
	},
	store = {
		to_village3 = {81, 15}
	},
	church = {
		to_village3_1 = {0,0},
		to_village3_2 = {0,0}
	},
	forest_1 = {
		to_map = {320, 35},
		to_forest_2_1 = {238, 69},
		to_forest_2_2 = {158, 69}
	},
	forest_2 = {
		to_forest_1 = {320, 35},
		to_forest_3 = {257, 69},
		to_forest_9 = {0, 35}
	},
	forest_3 = {
		to_forest_2 = {135, 68},
		to_forest_4 = {320, 35}
	},
	forest_4 = {
		to_forest_3 = {0, 35},
		to_forest_5 = {320, 35}
	},
	forest_5 = {
		to_forest_4 = {241, 68},
		to_forest_6 = {0, 24},
		to_forest_8 = {320, 24},
	},
	forest_6 = {
		to_forest_5 = {0,35},
		to_forest_7 = {151, 68}
	},
	forest_7 = {
		to_forest_6 = {0, 35},
		to_swordmaster = {320, 35}
	},
	forest_8 = {
		to_forest_5 = {0,0}
	},

	forest_9 = {
		to_forest_2 = {0, 0},
	},
	swordmaster = {
		to_map = {0,10}
	}

}


mi.addStorekeeper = function(args)
	-- pos: where it goes
	-- walkto: where it walks to (might be more than once)
	print ('fFOFOFOFOFOFOFOFOFOFO ' .. tostring(variables.chasing_shopkeeper))
	if variables.chasing_shopkeeper then
		if engine.state.previousRoom ~= args.from then
			variables.chasing_shopkeeper = false
			return nil
		end
		local actions = {
			{ 
				type = action.create_object, 
				args = { 
					factory = scumm.factory.object, 
					parent = args.parent, 
					args = { 
						id='storekeeper', 
						params = { pos = {args.pos[1], args.pos[2], 0}, dir = args.dir} 
					}
				}
			}
		}
		print ('ciaociao')
		for _, v in ipairs(args.walkto) do
			table.insert(actions, { type = scumm.action.walkto, args ={tag='storekeeper', pos = v }})
		end
	 	table.insert (actions, { type = action.remove_object, args = { tag = 'storekeeper'}})
		-- table.insert (actions, { type = action.activate, args = {tag='storekeeper', active=false}})
		table.insert (actions, { type = action.delay, args = {sec=10}})
		table.insert (actions, { type = action.set_variable, args = {var="chasing_shopkeeper", value=false}})
		local s = script.make(actions)
		monkey.play(s)
end
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
				--print ('ciao ' .. args.tag)
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