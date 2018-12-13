factory.object = {}

factory.object.create = function(args) 
	local objId = args.object
	-- fetch the object
	local object = items[objId]
	if (object == nil) then
		print ("Error! Unknown object " .. args.object)
	end

	-- These values can be overridden in the args
	local pos = args.pos and args.pos or object.pos
	local anim = args.anim and args.anim or object.anim
	local flip = args.flip and args.flip or object.flip

	local tag = object.tag
	--if (tag ~= nil) then
	--	print ("tag is " .. tag)
	--end
	
	local owned = variables.inventory[objId] ~= nil
	local createanyway = object.createanyway
	local createObject = ((not owned) or object.createanyway)
	if (not createObject) then
		return {}
	else
		local pos = args.pos and args.pos or object.pos
		local priority = args.priority or 1
		local comp = {}
		local offset = object.offset
		if (object.model ~= nil) then
			local a = nil
			if (type(anim)=="function") then
				a = anim() 
			else
				a = anim
			end
			table.insert (comp, { type="gfx", model=object.model, anim = a, flip = flip})
		end
		if (object.size ~= nil) then
			table.insert (comp, { type="hotspot", priority = priority, 
				shape = {type="rect", width = object.size[1], height = object.size[2], offset = offset},
				onenter = curry(hoverOn, objId),
				onleave = hoverOff,
				onclick = runAction })
		end
		if (args.applydepth) then
			print ("COME STAI")
			print (tostring(room.depth == nil))
			print (tostring(room.scale == nil))
			table.insert(comp, { type="depth", depth = room.depth, scale = room.scale })
		end
		return {
			tag = tag,
			pos = pos,
			components = comp
		}
	end

end