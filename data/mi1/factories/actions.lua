function getTag (args) 
	local tag = args.tag
	if (tag == nil) then
    	assert (args.actor, "tag or actor")    
		local item = items2[args.actor]
		tag = item.tag or args.actor
	end
	return tag
end

action.walkto = function (args) 
	--assert (args.id, "id")
	local after = args.after
	-- you can specify a tag or an actor (in this case the tag will be the actor's tag)
	local tag = getTag(args)

	-- you can specify pos directly or through object
	local pos = args.pos

	if (pos == nil) then
		assert (args.obj, "pos or obj")
		local obj = items2[args.obj]
		pos = obj.hotspot.walk_to
	end
	
	return { type="walk", actor=tag, pos = pos }

end

action.turn = function (args) 
	--assert (args.id, "id")
	assert (args.dir, "dir")
	local after= args.after
	local tag = getTag(args)
	return { type="turn", actor=tag, dir = args.dir }

end

action.change_room = function (args) 	
	assert (args.room, "room")
	return { type="gotoroom", room = args.room }
end

action.delay = function (args) 
	--assert (args.id, "id")
	--assert (args.sec, "sec")
	local after= args.after
	return { type="delay", sec = args.sec }

end

action.animate = function(args)
	--assert (args.id, "id")
	assert (args.anim, "anim")
	--local after= args.after
	local tag = getTag(args)
	local fwd = args.fwd
	local sync = args.sync
	if (fwd == nil) then fwd = true end
	if (sync == nil) then sync = false end
	return {type="animate", actor = tag, anim = args.anim, fwd = fwd, sync = sync }
end

action.say = function(args) 
	--assert (args.id, "id")
	assert (args.lines, "lines")
	assert (args.actor, "actor")

	local after= args.after
	local item = items2[args.actor]
	local tag = item.tag or args.actor

	local animstart = args.animstart
	local animend = args.animend
	local animate = true
	if (args.animate ~= nil) then animate = args.animate end

	local l = {}
	for _, li in ipairs(args.lines) do
		table.insert(l, get(li))
	end

	local item = items2[args.actor]
	return { id = args.id, after = after,  type="say", actor= tag, lines = l, offset = item.text_offset, color = item.text_color,
		animstart = animstart, animend = animend, animate = animate }
end

action.disable_controls = function(args) 
	--assert (args.id, "id")
	--local after = args.after
	return { type="callfunc", func = function() 
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
	--assert (args.id, "id")
	assert (args.dialogue, "dialogue")

	local droot = args.root

	return { type="callfunc", func = function() 
		--print ("Starting dialogue: " .. args.dialogue)
		local dialogue = dialogues[args.dialogue]
		if (dialogue == nil) then
			error ("Can't find dialogue " .. args.dialogue)
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
		local children = get(root.children)
		--print ("Size of children = " .. tostring(#children))
		m2:cleartext()
		for k, v in ipairs(children) do
        	local node = dialogue.nodes[v]
            if (get(node.active) == true) then
				m2:addtext { text=node.text, dialogue_node = node, dialogue = args.dialogue }
			end
        end
	end }
end

action.end_dialogue = function(args)
	assert (args.dialogue, "dialogue")
	return { type="callfunc", func = function() 
		local dialogue = dialogues[args.dialogue]
		if (dialogue == nil) then
			error ("Can't find dialogue " .. args.dialogue)
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
			dialogue.close()
		end
	end
	}
end

local closeDialogue = function(dialogue) 
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
		dialogue.close()
	end
end

local showDialogue = function(dialogueId, node) 
	local m2 = monkey.getEntity("dialogueui")
	local dialogue = dialogues[dialogueId]
	m2:setactive(true)
	m2:cleartext()
	for _, v in ipairs(node.children) do
		print ("examine node " .. tostring(v))
    	local node = dialogue.nodes[v]
        if (get(node.active) == true) then
			print ("active " .. node.text)
			m2:addtext { text=node.text, dialogue_node = node, dialogue = dialogueId }
		end
    end
end


action.resume_dialogue = function(args) 
	assert (args.node, "node")
	assert (args.dialogue, "dialogue")
	local node = args.node
	local dialogue = dialogues[args.dialogue]
	return { type="callfunc", func = 
		function() 
			print ("... resuming dialogue.")
			if (node.children == nil) then
        		-- return to game
        		closeDialogue (dialogue)
        	else
				-- check if node has active children
				print ("I have children. Check at least one is active.")
        		atLeastOneActiveChild = false
        		for _, v in ipairs(node.children) do
					print (tostring(v))
            		if (get(dialogue.nodes[v].active) == true) then
                		atLeastOneActiveChild = true
                		break
        		    end
        		end
				if (atLeastOneActiveChild == true) then
					print ("At least one child is active. Resuming dialogue...")
					showDialogue (args.dialogue, node)
				else
					print ("No active children. Shutting down dialogue, returning to game.")
					closeDialogue (dialogue)
				end
			end
		end
	}
end




action.random_delay = function(args)
	local id = gr(args.id, "Required id in action.random_delay")
	local after= go(args.after, nil)
	local min = gr(args.min, "Required min in action.random_delay")
	local max = gr(args.max, "Required min in action.random_delay")
	
	return { id = id, after = after, type="delay_dynamic", func = function() return (min + math.random() * (max-min)) end }
end



action.animate_once = function(args)
	local id = gr(args.id, "Required id in action.animate")
	local after= go(args.after, nil)
	local tag = args.tag
	if (tag == nil) then
		local actor = gr(args.actor, "Required actor in action.animate")
		local item = items[actor]
		tag = item.tag
	end
	local anim = gr(args.anim, "Required id in action.animate")
	return { id = id, after = after, type="animate", actor=tag, loop=1, anim=anim }
end






action.noop = function(args) 
	return { type="noop" }	
end



action.flip = function(args) 
	local tag = args.tag
	local flip = args.flip
	if (tag == nil) then
		local actor = gr(args.actor, "Required actor in action.animate")
		local item = items[actor]
		tag = item.tag
	end
	return { type="callfunc", func = function() 
		local m = monkey.getEntity(tag)
		m.flipx = flip
	end }

end




action.create_object = function(args) 
	assert (args.name, "name")
	local flip = false
	if (args.face ~= nil and args.face == "west") then
		flip = true
	end
	return { type = "callfunc", func = 
		function()
			print ("ciao, creating " .. args.name)
			local o = factory.objc { id = args.name, pos = args.pos, flipx = args.flipx }
			local m1 = monkey.getEntity("main")
			monkey.addEntity (o, m1)
		end
	}
end

action.remove_object = function(args) 

	local tag = args.tag
	if (tag == nil) then
		local objid = gr(args.name, "Required name in action.create_object")
		tag = items[objid].tag
	end
	return { type = "callfunc", func = 
		function()
			print ("ciao " .. tag)
			local i = monkey.getEntity(tag)
			i:remove()
		end
	}
end

action.open_door = function(args) 
	assert (args.door, "door")
	return { type = "callfunc", func = 
		function()
			local d = items2[args.door]
			print ("tag is " .. d.tag)
			local e = monkey.getEntity(d.tag)
			e.anim = "open"
			variables[d.variable] = 1
		end
	}
end

action.close_door = function(args) 
	assert (args.door, "door")
	return { type = "callfunc", func = 
		function()
			local d = items2[args.door]
			local e = monkey.getEntity(d.tag)
			e.anim = "close"
			variables[d.variable] = 0
		end
	}
end

action.set_variable = function(args)
	assert (args.var, "var")
	assert (args.value, "value")
	return { type = "callfunc", func = 
		function()
			print ("Setting " .. args.var .. " to " .. tostring(args.value))
			variables[args.var] = args.value
		end
	}

end

action.show_message = function(args) 
	local msg = gr(args.message, "Required id in action.create_object")
	local time = go(args.time, nil)
	local color = args.color
	local pos = args.pos
	
	return { type="show_message", message = msg, color = color, pos= pos}
end

action.suspend_script = function(args) 
	local script = gr(args.script, "Required id in action.create_object")
	return {type="suspend_script", script = script}
end

action.resume_script = function(args) 
	local script = gr(args.script, "Required id in action.create_object")
	return {type="resume_script", script = script}
end

action.kill_script = function(args) 
	local script = gr(args.script, "Required id in action.create_object")
	return {type="kill_script", script = script}
end


action.add_to_inventory = function(args) 
	--local id = gr(args.id, "Required id in action.create_object")
	--local after= go(args.after, nil)
	local objid = args.name
	local qty = args.qty
	return { type = "callfunc", func = 
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
	local objid = gr(args.name, "Required object name in add_to_inventory")
	return { type = "callfunc", func = 
		function()
			variables.inventory[objid] = nil
			refresh_inventory()
		end
	}


end

action.change_text_item = function(args) 
	local objid = gr(args.name, "Required object name in add_to_inventory")
	local text = gr(args.text, "Required object name in add_to_inventory")
	return {type = "callfunc", func = 
		function()
			items[objid].text = text
			refresh_inventory()
		end
	}

end

action.enable_wall = function(args) 
	local wallId = gr(args.wall,"")
	local active = gr(args.active,"")
	return {type="enable_wall", wall = wallId, active = active }
end

action.scroll = function (args) 
	local speed = gr(args.speed, "Required speed in action.scroll")
	local by = args.by
	local to = args.to
	return { type="scroll", cam = "maincam", by = by, to = to, speed = speed }
end

action.activate = function (args)
	local tag = args.tag
	if (tag == nil) then
		local name = gr(args.name, "Required <name> in action.activate")
		tag = items[name].tag
	end
	local activate = gr(args.value, "Req <value> in action.activate")
	return { type="callfunc", func = function() 
		local m = monkey.getEntity(tag)
		m:setactive(activate)
	end}

end