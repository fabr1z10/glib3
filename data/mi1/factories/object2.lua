factory.objc = function(args)

	local objId = args.id
	-- fetch the object
	local object = items[objId]
	if (object == nil) then
		print ("Error! Unknown object " .. args.object)
	end

	-- These values can be overridden in the args
	local pos = args.pos and args.pos or object.pos

    -- flipx is optional. If not provided, the default value is false (NOT flipped horizontally)
	local flipx = object.flipx or false 

	local tag = args.tag
	if (tag == nil) then 
		tag = object.tag 
	end
	
	local owned = variables.inventory[objId] ~= nil
	local createanyway = object.createanyway
	local createObject = ((not owned) or object.createanyway)
	if (not createObject) then
		return {}
	end

	local obj = {
		tag = tag,
		name = object.name,
		pos = pos,
		flipx = flipx,
		children = {},
		components = {}
	}
	if (object.model ~= nullptr) then
		obj.type = "sprite"
		obj.model = object.model
		obj.anim = object.anim
	end

	-- add the hotspot only if size is supplied
	if (object.hotspot ~= nil) then
		local hotspot = object.hotspot
		table.insert (obj.components, { type="hotspot", 
			priority = hotspot.priority or 1,
			shape = {type="rect", width = hotspot.size[1], height = hotspot.size[2], offset = hotspot.offset},
			onenter = curry(hoverOn, objId),
			onleave = hoverOff,
			onclick = runAction })
	end

	-- depth component
	if (object.applydepth) then
		table.insert(obj.components, { type="depth", depth = room.depth, scale = room.scale })
	end

	return obj

end