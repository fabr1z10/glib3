factory.mushroom = {}

factory.mushroom.response = function(p1, p2) 
	p2:remove()
end

factory.mushroom.create_auto = function(args)
	return factory.mushroom.create { sprite="mushroom", pos ={args.x, args.y}}
end

factory.mushroom.create = function(args)
	assert(args.pos, "pos")	
	assert(args.sprite, "sprite")

	local z = args.z or 0
	return {
		type = "sprite",
		model = args.sprite,
		-- basic brick
		pos = { args.pos[1] * engine.tilesize, args.pos[2] * tilesize, z },
		components = {
				{ 
					type = "collider", 
					flag = 4, 
					mask = 1, 
    				tag=variables.tags.mushroom
				},
				{ 
					type="characterstate", 
					acceleration_ground = 0.05, 
					acceleration_air = 0.05, 
					speed = 75, 
					jump_velocity = variables.jump_velocity,
					can_duck = false,
					flip = false,
					anims = {
						idle = "idle",
						walk = "idle",
						jump_up = "idle",
						jump_down = "idle",
						turn = "idle",
						duck = "idle"
					},
					colliders = {
						{ key = "walk", value = { type="rect", width = 16, height = 16, offset={-8,0}}}
					},
					f = mario_refresh
				},
				{
					-- properties
					type="dynamics2d", 
					gravity = variables.gravity,
				},
				{ 
					type="controller2d", 
					maxclimbangle = 80, 
					maxdescendangle = 80
				},
				{
					type = "enemyinput", 
					left = true,
					flip = true
				}
			}
	}
end

-- register
table.insert (variables.collider.response, { tag = { 1, variables.tags.mushroom}, onenter = factory.mushroom.response })

