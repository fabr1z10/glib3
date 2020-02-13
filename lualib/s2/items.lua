--- item factories
-- These functions generate the entity based on:
-- @param item the template, always Require
-- @param pos the optional position. if not provided, the item pos is used, or {0, 0} if item has no pos 

local Entity = {}
function Entity:new (args)
	o = {}
	local item = args.item
	local pos = args.pos or (item.pos or {0, 0, 0})
	o.pos = pos
	o.components = {}
	o.tag = args.tag
	return o
end

scumm.ifac.item = function(args) 

	-- Required:
	-- nothing
	-- Optional:
	--     pos				; the default position
	--     model            ; the model to use - nothing if item is not visible
	--     hotspot          ; the hotspot details if user is allowed to interact with it.
	-- If hotspot is provided, you need to provide:
	--     shape or size    ; if shape is not provided, the shape will be a rect with width and height as provided by size
	--     priority (opt)   ; the hot-spot priority, 1 is the default value
	--     text             ; the text displayed by the ui when hovering over the hotspot

	glib.assert(args.item, 'item!')

	local item = args.item

	local entity = Entity:new(args)

	if item.model then
		entity.type = 'sprite'
		entity.model = item.model
	end

	if item.hotspot then
		glib.assert(item.hotspot.text, 'entity with hotspot requires text!')
		glib.assert_either(item.hotspot.size, item.hotspot.shape, 'entity with hotspot requires size!')
		glib.assert(item.hotspot.walk_to, 'entity with hotspot requires walkto!')
		glib.assert(item.hotspot.dir, 'entity with hotspot requires dir!')

		local priority = item.hotspot.priority or 1
		local shape = item.hotspot.shape or { type="rect", width = item.hotspot.size[1], height = item.hotspot.size[2], offset = item.hotspot.offset }

		table.insert(entity.components, { 
			type = "hotspot", priority = priority,
			shape = shape,
			onenter = function() print ("entering ...") end,
			onleave = function() print ("leaving ...") end,
			onclick = function() print ("run act") end
		})
	end
	print ('pappo ' .. entity.type)
	return entity
	
end

-- create a character
scumm.ifac.char = function(args) 

end


scumm.ifac.walkarea =  function(args)

	glib.assert(args.item, 'item!')
	local item = args.item

	glib.assert(item.shape, '<walkarea> requires shape!')

	local pos = args.pos or (item.pos or {0, 0, 0})
	local priority = item.priority or 0

	entity = {
		pos = pos,
		components = {
			{ type = 'walkarea', priority = priority, shape = item.shape, depth = item.depth, scale = item.scale, blockedlines = item.blockedlines  }
		}
	}

	return entity
end


scumm.ifac.fmap = {
	object = scumm.ifac.item,
	walkarea = scumm.ifac.walkarea
}
