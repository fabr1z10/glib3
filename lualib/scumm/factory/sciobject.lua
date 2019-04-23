scumm.factory.sciobject = function(args)
	
	local objId = args.id
	print ("*** Creating object " .. objId)
	-- fetch the object
	local object = items[objId]
	if (object == nil) then
		print ("Error! Unknown object " .. args.id)
		return
	end
	local pos = args.pos and args.pos or object.pos
	local flipx = args.flipx
	if (flipx == nil) then flipx = object.flipx or false end
	
	local tag = args.tag
	if (tag == nil) then 
		tag = object.tag or objId
	end
	
	local obj = {
		tag = tag,
		pos = pos,
		flipx = flipx,
		children = args.children,
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
			shape = hotspot.shape,
			onclick = function(x, y, obj) scumm.ui.runSciAction(x, y, objId) end
		})
	end

	if (object.character ~= nil) then
		table.insert (obj.components, { type="character", dir = args.dir or object.character.dir, state = object.character.state })
	end
	if (args.follow == true) then
		table.insert(obj.components, { type="follow", cam ="maincam", relativepos = {0,0,5}, up={0,1,0}})
	end
	if (args.collide == true) then
		table.insert(obj.components, { type="collider", shape = {type="rect", width=10, height=2, offset={-5,-1}}, tag=1, flag=1, mask=2 })
	end

	-- depth component
	if (object.applydepth) then
		table.insert(obj.components, { type="depth", depth = roomDefinition.depth, scale = roomDefinition.scale })
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
    --print ("CAZZONE2")
	return obj

end