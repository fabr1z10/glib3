print ("exec <scumm/action> script")

scumm.action = {}

scumm.action.walkto = function (args) 
	glib.assert_either (args.tag, args.id, "id or tag")
	local pos = args.pos
	if (pos == nil) then
		assert (args.obj, "pos or obj")
		local obj = items[args.obj]
		pos = obj.hotspot.walk_to
	end	
	return { type="walk", tag = args.tag, id = args.id, pos = pos }
end

scumm.action.turn = function (args) 
	glib.assert_either (args.tag, args.id, "id or tag")
	assert (args.dir, "dir")
	return { type="turn", tag = args.tag, id = args.id, dir = args.dir }

end

scumm.action.pickup = function(id, anim1, anim2) 
	return { 
		{ ref = 1, type = action.animate, args ={actor="guybrush", anim=anim1, sync=true}},
		{ type = action.remove_object, args ={name=id }},
		{ type = action.animate, after={1}, args ={actor="guybrush", anim=anim2 }},
		{ type = action.add_to_inventory, args = {id=id}}
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

scumm.action.start_dialogue = function (args) 
	assert (args.dialogue, "dialogue")
	local droot = args.root
	return { type="callfunc", func = function() 
		--print ("Starting dialogue: " .. args.dialogue)
		print ("VIVA!")
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
		local children = glib.get(root.children)
		print ("Size of children = " .. tostring(#children))
		m2:cleartext()
		for k, v in ipairs(children) do
        	local node = dialogue.nodes[v]
            if (glib.get(node.active) == true) then
				m2:addtext { text=node.text, dialogue_node = node, dialogue = args.dialogue }
			end
        end
	end }
end

scumm.action.end_dialogue = function(args)
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

