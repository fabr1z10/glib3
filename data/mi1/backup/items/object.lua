items.object = {}

items.object.create = function(args) 
	-- normally, if player owns something, the object is not created
	local tag = args.object.tag
	--if (tag ~= nil) then
	--	print ("tag is " .. tag)
	--end
	
	local qty = args.object.qty or 0
	local createanyway = args.object.createanyway
	local createObject = (qty == 0 or args.object.createanyway)
	if (not createObject) then
	print ("FUCO")
		return nil
	else
		local pos = args.object.pos
		local priority = args.priority or 1
		local comp = {}
		local offset = args.object.offset
		if (args.object.model ~= nil) then
			table.insert (comp, { type="gfx", model=args.object.model, anim = args.object.anim, flip = args.object.flip})
		end
		if (args.object.size ~= nil) then
			table.insert (comp, { type="hotspot", priority = priority, 
				shape = {type="rect", width = args.object.size[1], height = args.object.size[2], offset = offset},
				onenter = curry(hoverOn, args.object),
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