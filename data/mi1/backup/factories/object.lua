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

    -- flipx is optional. If not provided, the default value is false (NOT flipped horizontally)
	local flipx = object.flipx or false 

	local anim = args.anim and args.anim or object.anim

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
		pos = pos,
		flipx = flipx,
		tag = object.tag,
		tagSpeak = args.tagSpeak,
		children = {},
		components = {}
	}
	
	-- add the gfx component only if a model is supplied
	if (object.model ~= nil) then
		local a = get(anim)	
		table.insert (obj.components, { type="gfx", model=object.model, anim = a, flip = flip})
	end

	-- add the hotspot only if size is supplied
	if (object.size ~= nil) then
		table.insert (obj.components, { type="hotspot", 
			priority = object.priority or 1,
			shape = {type="rect", width = object.size[1], height = object.size[2], offset = object.offset},
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