scumm.factory.object = function(args)
	
	local objId = args.id
	print ("*** Creating object " .. objId)
	-- fetch the object
	local object = items[objId]
	if (object == nil) then
		print ("Error! Unknown object " .. args.id)
		return
	end
	--print ("CAZZONE")
	-- These values can be overridden in the args
	
	local pos = args.pos and args.pos or object.pos
	if (pos == nil) then pos = {0,0,0} end
    -- flipx is optional. If not provided, the default value is false (NOT flipped horizontally)
	
	local flipx = args.flipx
	if (flipx == nil) then flipx = object.flipx or false end
	
	local tag = args.tag
	if (tag == nil) then 
		tag = object.tag or objId
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
		obj.anim = glib.get(object.anim)
	end

	-- add the hotspot only if size is supplied
	if (object.hotspot ~= nil) then
		local hotspot = object.hotspot
		table.insert (obj.components, { type="hotspot", 
			priority = hotspot.priority or 1,
			shape = {type="rect", width = hotspot.size[1], height = hotspot.size[2], offset = hotspot.offset},
			onenter = glib.curry(scumm.ui.hoverOn, objId),
			onleave = scumm.ui.hoverOff,
			onclick = scumm.ui.runAction })
	end
	if (object.character ~= nil) then
		table.insert (obj.components, { type="character", speed = object.character.speed, dir = args.dir or object.character.dir, state = object.character.state })
	end
	if (args.follow == true) then
		table.insert(obj.components, { type="follow", cam ="maincam", relativepos = {0,0,5}, up={0,1,0}})
	end
	if (args.collide == true) then
		table.insert(obj.components, { type="collider", shape = {type="rect", width=10, height=2, offset={-5,-1}}, tag=1, flag=1, mask=2 })
	end
	if (object.walkarea) then
		table.insert (obj.components, { type="walkarea", 
			priority = object.walkarea.priority or 1,
			shape = object.walkarea.shape,
			onclick = function(x, y, obj) scumm.ui.runSciAction(x, y, objId) end,
			scale = object.walkarea.scale,
			depth = object.walkarea.depth
		})

	end

	-- depth component
	if (object.applydepth) then
		table.insert(obj.components, { type="depth", depth = roomDefinition.depth, scale = roomDefinition.scale })
	end
    --print ("CAZZONE2")
	return obj

end