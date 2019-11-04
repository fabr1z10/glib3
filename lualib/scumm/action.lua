print ("exec <scumm/action> script")

local items =engine.items
local dialogues =engine.dialogues
local inventory = engine.state.scumm.inventory

scumm.action = {}

scumm.action.walkto = function (args) 
	glib.assert_either (args.tag, args.id, "id or tag")
	local pos = args.pos
	if (pos == nil) then
		assert (args.obj, "pos or obj")
		local obj = items[args.obj]
		pos = obj.hotspot.walk_to
	end	
	local walk_action = engine.config.scumm.walk[engine.config.style]
	print ("WALK = " .. walk_action)
	return { type=walk_action, tag = args.tag, id = args.id, pos = pos }
end

scumm.action.walktoitem = function (args) 
	glib.assert_either (args.tag, args.id, "id or tag")
	glib.assert(args.item, "item")
	local item = monkey.getEntity(args.item)
	local offset = args.offset or {0,0}
	return { type=engine.config.walk, tag = args.tag, id = args.id, pos = {item.x + offset[1], item.y + offset[2]} }
end



scumm.action.turn = function (args) 
	glib.assert_either (args.tag, args.id, "id or tag")
	assert (args.dir, "dir")
	local turn_action = engine.config.scumm.turn[engine.config.style]

	return { type=turn_action, tag = args.tag, id = args.id, dir = args.dir }

end

scumm.action.enableplay = function(args) 
	glib.assert (args.value, "value")
	return { type="callfunc", func = function() 
		print ("PLAY = " .. tostring(args.value))
		engine.state.scumm.play = args.value
	end }

end

scumm.action.enable_wall = function (args) 
	glib.assert(args.walkarea, "walkarea")
	glib.assert(args.wall, "wall")
	glib.assert(args.active, "active")

	return { type="enable_wall", walkarea = args.walkarea, wall = args.wall, active = args.active }

end

scumm.action.pickup2 = function(args)		
	if (inventory[args.id] ~= nil and inventory[args.id] > 0) then return {} end
	return { 
		{ ref = 1, type = action.animate, args ={tag="player", anim=args.anim1, sync=true}},
		{ type = action.activate, args ={tag=args.id, active=false }},
		{ type = action.animate, after={1}, args ={tag="player", anim=args.anim2 }},
		{ type = scumm.action.add_to_inventory, args = {id=args.id}}
	}
end


scumm.action.pickup = function(id, anim1, anim2)
print ("CIAO NERRR")
	print ("HAS " .. id .. tostring(inventory[id])) 
	if (inventory[id] ~= nil and inventory[id] > 0) then return {} end
	return { 
		{ ref = 1, type = action.animate, args ={tag="player", anim=anim1, sync=true}},
		{ type = action.activate, args ={tag=id, active=false }},
		{ type = action.animate, after={1}, args ={tag="player", anim=anim2 }},
		{ type = scumm.action.add_to_inventory, args = {id=id}}
	}
end

scumm.action.walk_to_object= function(actor, id) 
	return { 
		{ type = scumm.action.walkto, args = { tag=actor, obj=id}},
		{ type = scumm.action.turn, args = { tag=actor, dir = items[id].hotspot.dir}}
	}
end

scumm.action.say = function(args) 
	--assert (args.id, "id")
	glib.assert (args.actor, "actor")
	glib.assert (args.lines, "lines")

	local item = items[args.actor]
	local tag = item.tag or args.actor

	local animstart = args.animstart
	local animend = args.animend
	local animate = true
	if (args.animate ~= nil) then animate = args.animate end

	local l = {}
	for _, li in ipairs(args.lines) do
		table.insert(l, glib.get(li))
	end

	return { 
		type="say", 
		tag = tag, 
		lines = l, 
		offset = item.text_offset, 
		color = item.text_color,
		animstart = animstart, 
		animend = animend, 
		animate = animate 
	}
end

scumm.action.disable_controls = function(args) 
	return { type="callfunc", func = function()
		local value = true
		if (args ~= nil and args.value ~= nil) then value = args.value end
		local n = not value 
		engine.state.scumm.walk_enabled = n
		local m = monkey.getEntity("mainui")
		local m1 = monkey.getEntity("main")
		if (not m.isnil) then
			m:setactive(n)
		end
		if (not m1.isnil) then
			m1:enablecontrols(n)
		end
	end }
end

scumm.action.start_dialogue = function (args) 
	assert (args.dialogue, "dialogue")
	local droot = args.root or 1
	return { type="callfunc", func = function() 
		local dialogue = engine.dialogues[args.dialogue]
		if (dialogue == nil) then
			error ("Can't find dialogue " .. args.dialogue)
		end
		local root = dialogue.nodes[droot] --droot or dialogue.nodes[1]
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
		local children = glib.get(root.children)
		print ("Size of children = " .. tostring(#children))
		m2:cleartext()
		for k, v in ipairs(children) do
        	local node = dialogue.nodes[v]
    		print (node.text)
            if (glib.get(node.active) == true) then
				m2:addtext { text=node.text, dialogue_node = node, dialogue = args.dialogue }
			end
			print ("cazzo")
        end
		engine.state.scumm.walk_enabled = false 
	end }
end

local closeDialogue = function(dialogue) 
	local m = monkey.getEntity("mainui")
	local m1 = monkey.getEntity("main")
	local m2 = monkey.getEntity("dialogueui")
	engine.state.scumm.walk_enabled = true
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
	local ch = glib.get(node.children)
	for _, v in ipairs(ch) do
		print ("examine node " .. tostring(v))
    	local node = dialogue.nodes[v]
        if (glib.get(node.active) == true) then
			print ("active " .. node.text)
			m2:addtext { text=node.text, dialogue_node = node, dialogue = dialogueId }
		end
    end
end


scumm.action.resume_dialogue = function(args) 
	assert (args.node, "node")
	assert (args.dialogue, "dialogue")
	local node = args.node
	local dialogue = dialogues[args.dialogue]
	return { type="callfunc", func = 
		function() 
			print ("... resuming dialogue.")
			if (node.children == nil) then
        		-- return to game
        		print ("return to game.")
        		closeDialogue (dialogue)
        	else
				-- check if node has active children
				print ("I have children. Check at least one is active.")
        		atLeastOneActiveChild = false
        		local ch = glib.get(node.children)
        		for _, v in ipairs(ch) do
					print (tostring(v))
            		if (glib.get(dialogue.nodes[v].active) == true) then
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

scumm.action.add_to_inventory = function(args) 
	assert (args.id, "id")
	local qty = args.qty or 1
	return { type = "callfunc", func = 
		function()
			print (args.id .. " adding")			
			if (inventory[args.id] == nil) then
				inventory[args.id] = qty
			else 
				inventory[args.id] = inventory[args.id] + qty
			end
			print ("ref inv")
			scumm.ui.refresh_inventory()	
			print ("done")
		end
	}
end

scumm.action.add_to_inventory_sci = function(args) 
	assert (args.id, "id")
	local qty = args.qty or 1
	return { type = "callfunc", func = 
		function()
			print (args.id .. " adding")			
			if (inventory[args.id] == nil) then
				inventory[args.id] = {}
				print ("FATTO " .. args.id)
			else 
				inventory[args.id] = inventory[args.id] + qty
			end
		end
	}
end

scumm.action.remove_from_inventory = function(args) 
	assert (args.id, "id")
	return { type = "callfunc", func = 
		function()
			print ("removing " .. args.id)
			inventory[args.id] = nil
			scumm.ui.refresh_inventory()
		end
	}
end

scumm.action.open_door = function(args) 
	assert (args.door, "door")
	return { type = "callfunc", func = 
		function()
			local d = items[args.door]
			print ("tag is " .. d.tag)
			local e = monkey.getEntity(d.tag)
			e.anim = "open"
			variables[d.variable] = 1
		end
	}
end

scumm.action.close_door = function(args) 
	assert (args.door, "door")
	return { type = "callfunc", func = 
		function()
			local d = items[args.door]
			local e = monkey.getEntity(d.tag)
			e.anim = "close"
			variables[d.variable] = 0
		end
	}
end

scumm.say = function(who, lines) 
	local l = {}
	for _, n in ipairs(lines) do
		table.insert(l, d[n])
	end
	return { type = scumm.action.say, args = {actor = actor_map[who], lines = l }}
end

scumm.action.change_text_item = function (args) 
	assert (args.id, "id")
	assert (args.text, "text")
	return { type="callfunc", func= function()
		engine.items[args.id].hotspot.text = args.text
		scumm.ui.refresh_inventory()
	end}
end

-- scumm.action.end_dialogue = function(args)
-- 	assert (args.dialogue, "dialogue")
-- 	return { type="callfunc", func = function() 
-- 		local dialogue = dialogues[args.dialogue]
-- 		if (dialogue == nil) then
-- 			error ("Can't find dialogue " .. args.dialogue)
-- 		end
-- 		local m = monkey.getEntity("mainui")
-- 		local m1 = monkey.getEntity("main")
-- 		local m2 = monkey.getEntity("dialogueui")
-- 		m2:cleartext()
-- 		m2:setactive(false)
-- 		if (not m.isnil) then
-- 			m:setactive(true)	
-- 		end
-- 		if (not m1.isnil) then
-- 			m1:enablecontrols(true)			
-- 		end
-- 		if (dialogue.close ~= nil) then
-- 			dialogue.close()
-- 		end
-- 	end
-- 	}
-- end

