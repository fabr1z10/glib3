--print ("exec <scumm/action> script")

local items =engine.items
local dialogues =engine.dialogues
--local inventory = variables.inventory

-- scumm.action holds functions that return single actions
-- i.e. every function here will return a table like
-- { type = 'typeid', ... } where typeid is a class recognized by glib3
-- and ... are params depending on the specific functions.
-- If you want complex actions, look for scumm.script

scumm.action = {}

scumm.action.walkto = function (args) 
	glib.assert_either (args.tag, args.id, "id or tag")
	local pos = args.pos
	if (pos == nil) then
		assert (args.obj, "pos or obj")
		local obj = items[args.obj]
		if not obj then error('Don\'t know item: ' .. args.obj) end
		pos = obj.hotspot.walk_to
	end	
	return { type='walk', tag = args.tag, id = args.id, pos = pos }
end

scumm.action.turn = function (args) 
	glib.assert_either (args.tag, args.id, "id or tag")
	assert (args.dir, "dir")
	return { type = 'turn', tag = args.tag, id = args.id, dir = args.dir }

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

-- scumm.action.pickup2 = function(args)		
-- 	if (inventory[args.id] ~= nil and inventory[args.id] > 0) then return {} end
-- 	return { 
-- 		{ ref = 1, type = action.animate, args ={tag="player", anim=args.anim1, sync=true}},
-- 		{ type = action.activate, args ={tag=args.id, active=false }},
-- 		{ type = action.animate, after={1}, args ={tag="player", anim=args.anim2 }},
-- 		{ type = scumm.action.add_to_inventory, args = {id=args.id}}
-- 	}
-- end

-- scumm.action.pickup = function(args)
-- 	-- picks up something.
-- 	-- deact = 0 --> don't remove item from scene
-- 	glib.assert(args.id, "id")		
-- 	local id_inv = args.id_inv or args.id
-- 	local deact = args.deact or 1

-- 	return function()
-- 		local act = {}
-- 		local alreadyHaveIt = (inventory[id_inv] ~= nil and inventory[id_inv] > 0)
-- 		-- if I already have and the alreadyhave msg is set, I say it
-- 		if (alreadyHaveIt and args.alreadyhave ~= nil) then
-- 			act = {
-- 				{ type = scumm.action.say, args = { actor="guybrush", lines = args.alreadyhave }}
-- 			}
-- 			return act
-- 		end
-- 		if (args.anim1 ~= nil and args.anim2 ~= nil) then
-- 			table.insert (act, { type = action.animate, args = {tag="player", anim=args.anim1, sync=true}})
-- 		end
-- 		if (args.deact == 1) then
-- 			table.insert (act, { type = action.activate, args ={tag=id, active=false }})
-- 		end
-- 		if (args.anim1 ~= nil and args.anim2 ~= nil) then
-- 			table.insert (act, { type = action.animate, args = {tag="player", anim=args.anim2 }})
-- 		end
-- 		table.insert(act, { type = scumm.action.add_to_inventory, args = {id=id_inv}})
-- 		return act
-- 	end
-- end

scumm.action.walk_to_object= function(actor, id) 
	return { 
		{ type = scumm.action.walkto, args = { tag=actor, obj=id}},
		{ type = scumm.action.turn, args = { tag=actor, dir = items[id].hotspot.dir}}
	}
end


scumm.action.say = function(args) 
	--assert (args.id, "id")
	glib.assert_either (args.tag, args.id, "id or tag")
	glib.assert (args.lines, "lines")

	local entity = nil
	if args.tag then
		entity = monkey.getEntity(args.tag)
		if not entity then Error('don\'t know item ' + args.tag, 1) end
	else
		entity = monkey.getEntityFromId(args.id)
		if not entity then Error('don\'t know item!' + args.id, 1) end
	end
	print ('found')
	local info = entity:getinfo()

	local item = items[info.id]

	local animstart = args.animstart
	local animend = args.animend
	local animate = true
	if (args.animate ~= nil) then animate = args.animate end

	local l = {}
	for _, li in ipairs(args.lines) do
		table.insert(l, glib.get(li))
	end

	return {
		type = 'say',
		tag = args.tag,
		font = engine.config.dialogue_font,
		id = args.id,
		lines = l,
		offset = item.text_offset,
		color = item.text_color,
		animstart = animstart,
		animend = animend,
		animate = animate
	}
end

-- switch controls on/off. 
-- active REQ (bool) -> tells whether you want to switch controls on or off
-- ui REQ (bool) -> tells whether you want to include the ui 
--              (if true, the verbs will disappear/appear if active is off/on)
scumm.action.toggle_controls = function(args)
	return {
		type = 'callfunc',
		func = function()
			scumm.state.walk_enabled = args.active
			if args.ui then
				local m = monkey.getEntity("mainui")
				if not m.isnil then m:setactive(args.active) end
			end
			local m1 = monkey.getEntity("main")
			if not m1.isnil then
				m1:enablecontrols(args.active)
			end
		end
	}
end

-- Starts a dialogue.
-- dialogue REQ (string) --> the dialogue to start (required)
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
		m2:cleartext()
		for k, v in ipairs(children) do
        	local node = dialogue.nodes[v]
            if (glib.get(node.active) == true) then
				m2:addtext { text=node.text, dialogue_node = node, dialogue = args.dialogue }
			end
        end
		scumm.state.walk_enabled = false
	end }
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
        		scumm.func.closeDialogue (dialogue)
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
	local inv = variables.inventory[variables.current_player]
	assert (args.id, "id")
	local qty = args.qty or 1
	return { type = "callfunc", func = 
		function()
			print (args.id .. " adding")			
			if (inv[args.id] == nil) then
				inv[args.id] = qty
			else 
				inv[args.id] = inv[args.id] + qty
			end
			scumm.func.refresh_inventory()
		end
	}
end

scumm.action.remove_from_inventory = function(args) 
	assert (args.id, "id")
	return { type = "callfunc", func = 
		function()
			local inv = variables.inventory[variables.current_player]
			inv[args.id] = nil
			scumm.func.refresh_inventory()
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
		scumm.func.refresh_inventory()
	end}
end
