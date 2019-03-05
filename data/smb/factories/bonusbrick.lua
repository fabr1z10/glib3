factory.bonus_brick = {}

factory.bonus_brick.response = function(p1, p2) 
	-- if mario is large
	print ("ciao")
end

factory.bonus_brick.create = function(args)
	assert(args.pos, "pos")	
	assert(args.sprite, "sprite")
	assert(args.factory, "factory")

	local z = args.z or 0
	return {
		type = "sprite",
		tag = "giggi",
		model = args.sprite,
		-- basic brick
		pos = { args.pos[1] * engine.tilesize, args.pos[2] * tilesize, z },
		components = {
			{ type="collider", flag=2, mask=1, tag=1, shape = {type="rect", width=engine.tilesize, height=engine.tilesize} },
		},
		children = {
			{
				pos = {8, 0, 0},
				components = {
					{ type="collider", flag=4, mask=1, tag=variables.tags.bonus_brick, shape = {type="rect", width=8, height=4, offset = {-4,-2}} },
					{ type="properties", additional_info = { factory = args.factory} }
				}
			}
		}
	}
end

-- register
table.insert (variables.collider.response, { tag = { 1, variables.tags.bonus_brick}, onenter = factory.bonus_brick.response })
