factory.object = {}

factory.object.create = function(args) 

	-- fetch the object
	local object = items[args.object]
	if (object == nil) then
		print ("Error! Unknown object " .. args.object)
	end

	local tag = object.tag
	--if (tag ~= nil) then
	--	print ("tag is " .. tag)
	--end
	
	local qty = object.qty or 0
	local createanyway = object.createanyway
	local createObject = (qty == 0 or object.createanyway)
	if (not createObject) then
		return nil
	else
		local pos = args.pos and args.pos or object.pos
		local priority = args.priority or 1
		local comp = {}
		local offset = object.offset
		if (object.model ~= nil) then
			local anim = nil
			if (type(object.anim)=="function") then
				anim = object.anim() 
			else
				anim = object.anim
			end
			table.insert (comp, { type="gfx", model=object.model, anim = anim, flip = object.flip})
		end
		if (object.size ~= nil) then
			table.insert (comp, { type="hotspot", priority = priority, 
				shape = {type="rect", width = object.size[1], height = object.size[2], offset = offset},
				onenter = curry(hoverOn, object),
				onleave = hoverOff,
				onclick = runAction })
		end
		return {
			tag = tag,
			pos = pos,
			components = comp
		}
	end

end