factory.cobject = {}

factory.cobject.create = function(args) 
	local objId = args.object
	-- fetch the object
	local object = items[objId]
	if (object == nil) then
		print ("Error! Unknown object " .. args.object)
	end

	-- first of all, the position.
	-- If args provides a position, we use that, otherwise we get the object pos
    local pos = args.pos and args.pos or object.pos
	
    -- flipx is optional. If not provided, the default value is false (NOT flipped horizontally)
	local flipx = object.flipx or false 
	
    -- appplydepth is false by default
	local applydepth = object.applydepth or false

	local obj = {
		pos = pos,
		flipx = flipx,
		tag = object.tag,
		tagSpeak = args.tagSpeak,
		children = {},
		components = {}
	}

	if (applydepth == true) then
		table.insert(obj.components, { type="depth", depth = room.depth, scale = room.scale })
	end

	if (object.size ~= nil) then
		table.insert(obj.components, { type="hotspot", priority = object.priority or 1, 
			shape = {type="rect", width = object.size[1], height = object.size[2], offset = object.offset },
			onenter = curry(hoverOn, objId),
			onleave = hoverOff,
			onclick = runAction })
	end

	mn = {}
	-- create nodes
	for _, v in ipairs(object.nodes) do
		local node = { name = v.name, pos={0,0,0}, tag =v.tag, children = {}, components= {
			{ type="gfx", model=v.model, anim=v.anim, framehandlers = v.fh }
		}}
		mn[v.name] = node
		if (v.parent ~= nil) then
			table.insert(mn[v.parent].children, node)
		else
			table.insert(obj.children, node)
		end
	end

	return obj
end