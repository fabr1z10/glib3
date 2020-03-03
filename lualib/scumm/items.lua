--- item factories
-- These functions generate the entity based on:
-- @param item the template, always Require
-- @param pos the optional position. if not provided, the item pos is used, or {0, 0} if item has no pos 

local Entity = {}

function Entity:new (a)
	o = {}
	local item = a.item
	local pos = a.args.pos or (item.pos or {0, 0, 0})
	if #pos == 2 then pos = { pos[1], pos[2], 0 } end
	o.pos = pos
	o.active = a.args.active
	o.components = {}
	o.tag = a.args.tag
	return o
end

scumm.ifac.item = function(args) 

-- @param item the item to create
-- @param args the modifiers (position, tag)
	glib.assert(args.item, 'item!')

	local item = args.item

	local entity = Entity:new(args)

	if item.model then
		entity.type = 'sprite'
		entity.model = item.model
		entity.anim = glib.get(item.anim)
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
			onenter = glib.curry (scumm.func.hoverOn, args.args._id),
			onleave = scumm.func.hoverOff,
			onclick = scumm.func.run_action,
		})
	end


	
	return entity
	
end

scumm.ifac.hotspot = function(args) 
	glib.assert(args.item, 'item!')

	local item = args.item

	local entity = Entity:new(args)
	local priority = item.priority or 1

	table.insert (entity.components, {
		type = 'hotspot',
		priority = priority,
		shape = item.shape,
		onenter = item.onenter,
		onleave = item.onleave,
		onclick = item.onclick

	})
	return entity
end



-- create a character
scumm.ifac.char = function(args) 
	glib.assert(args.item, 'item!')

	local item = args.item

	glib.assert(item.model, 'character requires a model!')
	glib.assert(item.speed, 'character requires a speed!')

	local entity = Entity:new(args)

	entity.type = 'sprite'
	print ('ciao ' .. item.model)
	entity.model = item.model

	-- direction character is facing
	local dir = args.args.dir and (args.args.dir) or (item.dir)
	local state = args.args.state and (args.args.state) or (item.state or 'idle')

	table.insert (entity.components, { type="character", speed = item.speed, dir = dir, state = state })
	table.insert (entity.components, { type="info", info = { id = args.args._id }})

	if args.args.follow then
		table.insert(entity.components, { type='follow', cam='maincam', relativepos = {0, 0, 5}, up = {0, 1, 0} })
	end	

	if item.collide and roomDefinition.collide then
		table.insert(entity.components, { 
			type='collider', 
			shape = { type='rect', width = item.collide.size[1], height=item.collide.size[2], offset = item.collide.offset },
			tag = item.collide.tag,
			flag = item.collide.flag,
			mask=item.collide.mask
		})
	end
	return entity
end

scumm.ifac.mockchar = function(args)
	glib.assert(args.item, 'item!')

	local item = args.item

	local entity = Entity:new(args)

	entity.type = item.model and 'sprite' or 'default'
	entity.model = item.model

	-- direction character is facing
	local dir = args.args.dir and (args.args.dir) or (item.dir)
	local state = args.args.state and (args.args.state) or (item.state or 'idle')

	table.insert (entity.components, { type="info", info = { id = args.args._id }})

	return entity
end

scumm.ifac.walkarea =  function(args)

	glib.assert(args.item, 'item!')
	local item = args.item
	local entity = Entity:new(args)

	glib.assert(item.shape, '<walkarea> requires shape!')

	local priority = item.priority or 0

	table.insert(entity.components, { 
		type = 'walkarea', 
		priority = priority, 
		shape = item.shape, 
		depth = item.depth, 
		scale = item.scale, 
		onclick = function(x, y, obj) 
			scumm.func.walk(x, y) 
		end,
		blockedlines = item.blockedlines 
	})	

	return entity
end

scumm.ifac.door = function(args)

	glib.assert(args.item, 'item!')

	local item = args.item

	glib.assert(item.model, 'character requires a model!')

	local entity = Entity:new(args)
	local priority = args.priority or 1

	entity.type = 'sprite'
	entity.model = item.model

	table.insert(entity.components, {
		type = "hotspot",
		priority = priority,
		shape = { type = 'rect', width = item.size[1], height= item.size[2]},
		onenter = glib.curry (scumm.func.hoverOn, args.args._id),
		onleave = scumm.func.hoverOff,
		onclick = scumm.func.run_action,
	})

	return entity
end


scumm.ifac.trap = function(args) 
	glib.assert(args.item, 'item!')

	local item = args.item

	glib.assert(item.shape, 'trap requires a shape!')
	glib.assert(item.onenter, 'trap requires a onenter!')

	local entity = Entity:new(args)

	entity.type = 'default'

	table.insert (entity.components, { type="collider", shape = item.shape, tag = 2, flag = 2, mask = 1 })
	table.insert (entity.components, { type="info", info = { onenter = item.onenter }})


	return entity
end

scumm.ifac.fmap = {
	object = scumm.ifac.item,
	walkarea = scumm.ifac.walkarea,
	char = scumm.ifac.char,
	mockchar = scumm.ifac.mockchar,
	door = scumm.ifac.door,
	trap = scumm.ifac.trap,
	hotspot = scumm.ifac.hotspot
}
