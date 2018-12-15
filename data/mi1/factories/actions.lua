action.delay = function (args) 
	local id = gr(args.id, "Required id in action.delay")
	local after= go(args.after, nil)
	local sec = gr(args.sec, "Required min in action.delay")
	return { id = id, after = after, type="delay", sec = sec }

end


action.random_delay = function(args)
	local id = gr(args.id, "Required id in action.random_delay")
	local after= go(args.after, nil)
	local min = gr(args.min, "Required min in action.random_delay")
	local max = gr(args.max, "Required min in action.random_delay")
	
	return { id = id, after = after, type="delay_dynamic", func = function() return (min + math.random() * (max-min)) end }
end

action.animate = function(args)
	local id = gr(args.id, "Required id in action.animate")
	local after= go(args.after, nil)
	local actor = gr(args.actor, "Required actor in action.animate")
	local item = items[actor]
	local anim = gr(args.anim, "Required anim in action.animate")
	local flip = 0
	if (args.flip ~= nil) then
		flip = (args.flip) and 2 or 1
	end
	return { id = id, after = after, type="animate", actor=item.tag, anim=anim, flip = flip }
end

action.animate_once = function(args)
	local id = gr(args.id, "Required id in action.animate")
	local after= go(args.after, nil)
	local actor = gr(args.actor, "Required id in action.animate")
	local item = items[actor]
	local anim = gr(args.anim, "Required id in action.animate")
	return { id = id, after = after, type="animate", actor=item.tag, loop=1, anim=anim }
end

action.walkto = function (args) 

	local id = gr(args.id, "Required id in action.walkto")
	local after= go(args.after, nil)
	local actor = gr(args.actor, "Required id in action.walkto")
	local item = items[actor]
	local pos = nil
	if (args.obj == nil) then
		pos = gr(args.pos, "Required object or position in action.walkto")
	else
		--local item2 = items[args.obj]
		--print("plllll" .. args.obj.tag)
		pos = args.obj.walk_to
		if (pos == nil) then
			print ("ERROR! Target object needs a <walk_to> field!")
		end
	end
	print ("id... = " .. tostring(id))
	return { id=id, after=after, type="walk", actor=item.tag, pos = pos }

end

action.turn = function (args) 
	local id = gr(args.id, "Required id in action.turn")
	local after= go(args.after, nil)
	local actor = gr(args.actor, "Required actor in action.turn")
	local dir = gr(args.dir, "Required dir in action.turn")
	local item = items[actor]
	return { id=id, after=after, type="turn", actor=item.tag, dir = dir }

end

action.say = function(args) 
	local id = gr(args.id, "Required id in action.say")
	local after= go(args.after, nil)
	local actor = gr(args.actor, "Required actor in action.say")
	local lines = gr(args.lines, "Required lines to say in action.say")
	local animstart = args.animstart
	local animend = args.animend
	local animate = true
	if (args.animate ~= nil) then animate = args.animate end

	local item = items[actor]
	return { id = id, after = after,  type="say", actor= item.tag, lines = lines, offset = item.text_offset, color = item.text_color,
		animstart = animstart, animend = animend, animate = animate }
end

action.change_room = function (args) 	
	local id = gr(args.id, "Required id in action.changeroom")
	local after= go(args.after, nil)
	local room = gr(args.room, "Required room in action.changeroom")
	return { id = id, after = after, type="gotoroom", room = room }
end

action.disable_controls = function(args) 
	local id = gr(args.id, "Required id in action.start_dialogue")
	local after= go(args.after, nil)
	return { id = id, after = after, type="callfunc", func = function() 
		local m = monkey.getEntity("mainui")
		local m1 = monkey.getEntity("main")
		if (not m.isnil) then
			m:setactive(false)
		end
		if (not m1.isnil) then
			m1:enablecontrols(false)
		end
	end }

end

action.start_dialogue = function (args) 
	local id = gr(args.id, "Required id in action.start_dialogue")
	local after= go(args.after, nil)
	local dialogueId = gr(args.dialogue, "Required dialogue in action.start_dialogue")
	local droot = args.root
	return { id = id, after = after, type="callfunc", func = function() 
		local dialogue = dialogues[dialogueId]
		if (dialogue == nil) then
			print ("Can't find dialogue " .. dialogueId)
		end
		local root = droot or dialogue.nodes[1]
		local m = monkey.getEntity("mainui")
		local m1 = monkey.getEntity("main")
		local m2 = monkey.getEntity("dialogueui")
		if (not m.isnil) then
			m:setactive(false)
		end
		if (not m1.isnil) then
			m1:enablecontrols(false)
		end
		m2:setactive(true)
		print ("Size of children = " .. tostring(#root.children))
		m2:cleartext()
		for k, v in ipairs(root.children) do
        	local node = dialogue.nodes[v]
            if (get(node.active) == true) then
				m2:addtext { text=node.text, dialogue_node = node, dialogue = args.dialogue }
			end
        end
	end }
end

action.end_dialogue = function(args)
	local id = gr(args.id, "Required id in action.start_dialogue")
	local after= go(args.after, nil)
	local dialogueId = gr(args.dialogue, "Required dialogue in action.start_dialogue")
	return { id = id, after = after, type="callfunc", func = function() 
		local dialogue = dialogues[dialogueId]
		if (dialogue == nil) then
			print ("Can't find dialogue " .. dialogueId)
		end
		local m = monkey.getEntity("mainui")
		local m1 = monkey.getEntity("main")
		local m2 = monkey.getEntity("dialogueui")
		m2:cleartext()
		m2:setactive(false)
		if (not m.isnil) then
			m:setactive(true)	
		end
		if (not m1.isnil) then
			m1:enablecontrols(true)			
		end
		if (dialogue.close ~= nil) then
			print ("closing seq")
			dialogue.close()
		end
	end
	}
end

action.create_object = function(args) 
	local id = gr(args.id, "Required id in action.create_object")
	local after= go(args.after, nil)
	local objid = gr(args.name, "Required name in action.create_object")
	local flip = false
	if (args.face ~= nil and args.face == "west") then
		flip = true
	end
	return { id = id, after = after, type = "callfunc", func = 
		function()
			print ("CIAO")
			local o = factory.object.create { object = objid, pos = args.pos, anim = args.anim, flip = flip, applydepth = args.applydepth }
			print ("CIAO2")
			local m1 = monkey.getEntity("main")
			print ("CIAO3")
			monkey.addEntity (o, m1)
		end
	}
end

action.remove_object = function(args) 

	local id = gr(args.id, "Required id in action.create_object")
	local after= go(args.after, nil)
	local tag = args.tag
	if (tag == nil) then
		local objid = gr(args.name, "Required name in action.create_object")
		tag = items[objid].tag
	end
	return { id = id, after = after, type = "callfunc", func = 
		function()
			local i = monkey.getEntity(tag)
			i:remove()
		end
	}
end

action.open_door = function(args) 
	local id = gr(args.id, "Required id in action.create_object")
	local after= go(args.after, nil)
	local door = gr(args.door, "ciao")

	return { id = id, after = after, type = "callfunc", func = 
		function()
			local d = items[door]
			print ("CICICICICICICILOPPOPO")
			local e = monkey.getEntity(d.tag)
			e.anim = "open"
			variables[d.door_ref] = 1
		end
	}
end

action.close_door = function(args) 
	local id = gr(args.id, "Required id in action.create_object")
	local after= go(args.after, nil)
	local door = gr(args.door, "ciao")

	return { id = id, after = after, type = "callfunc", func = 
		function()
			local d = items[door]
			local e = monkey.getEntity(d.tag)
			e.anim = "close"
			variables[d.door_ref] = 0
		end
	}
end

action.set_variable = function(args)
	local id = gr(args.id, "Required id in action.create_object")
	local after= go(args.after, nil)
	local var = gr(args.var, "ciao")
	local value = gr(args.value, "value")

	return { id = id, after = after, type = "callfunc", func = 
		function()
			variables[var] = value
		end
	}

end

action.show_message = function(args) 
	local id = gr(args.id, "Required id in action.create_object")
	local after= go(args.after, nil)
	print ("SHOW : " .. args.message)
	local msg = gr(args.message, "Required id in action.create_object")
	local time = go(args.time, nil)
	local color = args.color
	local pos = args.pos
	
	return { id = id, after = after, type="show_message", message = msg, color = color, pos= pos}
end

action.suspend_script = function(args) 
	local id = gr(args.id, "Required id in action.create_object")
	local after= go(args.after, nil)
	local script = gr(args.script, "Required id in action.create_object")
	return { id = id, after = after, type="suspend_script", script = script}
end

action.resume_script = function(args) 
	local id = gr(args.id, "Required id in action.create_object")
	local after= go(args.after, nil)
	local script = gr(args.script, "Required id in action.create_object")
	return { id = id, after = after, type="resume_script", script = script}
end

action.kill_script = function(args) 
	local id = gr(args.id, "Required id in action.create_object")
	local after= go(args.after, nil)
	local script = gr(args.script, "Required id in action.create_object")
	return { id = id, after = after, type="kill_script", script = script}
end


action.add_to_inventory = function(args) 
	local id = gr(args.id, "Required id in action.create_object")
	local after= go(args.after, nil)
	local objid = gr(args.name, "Required object name in add_to_inventory")
	local qty = gr(args.qty, "Required qty")
	return { id = id, after = after, type = "callfunc", func = 
		function()
			-- the object might already be in inventory
			if (variables.inventory[objid] == nil) then
				variables.inventory[objid] = qty
			else 
				variables.inventory[objid] = variables.inventory[objid] + qty
			end
			refresh_inventory()
	
		end
	}
end

action.remove_from_inventory = function(args) 
	local id = gr(args.id, "Required id in action.create_object")
	local after= go(args.after, nil)
	local objid = gr(args.name, "Required object name in add_to_inventory")
	return { id = id, after = after, type = "callfunc", func = 
		function()
			variables.inventory[objid] = nil
			refresh_inventory()
		end
	}


end

action.change_text_item = function(args) 
	local id = gr(args.id, "Required id in action.create_object")
	local after= go(args.after, nil)
	local objid = gr(args.name, "Required object name in add_to_inventory")
	local text = gr(args.text, "Required object name in add_to_inventory")
	return { id = id, after = after, type = "callfunc", func = 
		function()
			items[objid].text = text
			refresh_inventory()
		end
	}

end

action.enable_wall = function(args) 
	local id = gr(args.id, "Required id in action.create_object")
	local after= go(args.after, nil)
	local wallId = gr(args.wall,"")
	local active = gr(args.active,"")
	return { id = id, after = after, type="enable_wall", wall = wallId, active = active }
end