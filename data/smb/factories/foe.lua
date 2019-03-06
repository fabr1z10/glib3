-- generic foe
factory.foe = {}


factory.mushroom = {}
factory.mushroom1up = {}

-- the only difference from goomba and koopa is that
-- 1. when goomba enters dead state, a script is run and after n seconds is is removed
-- 2. when koopa enters dead state, if nothing happens then after n seconds it starts blinking and after m seconds goes back to walk state
-- 2b. if mario touches koopa when in dead state, it goes in run state. 
--
-- : Goomba state machine :
-- ******** mario jump on  ********  time
---* WALK *--------------->* DEAD *---------------> removed
-- ********                ********
-- 
-- : Koopa state machine :
-- ******** mario jump on  ********  mario jump on *******
---* WALK *--------------->* DEAD *--------------->* RUN *
-- ********<---------------********<---------------*******
--              time                     time
	
factory.goomba = {}
factory.koopa = {}

factory.mushroom.response = function(p1, p2) 
	p2:remove()
	p1:set("supermario", true)
end

factory.mushroom1up.response = function(p1, p2) 
	print ("weroigfriofhj")
	p2:remove()
end

factory.goomba.response = function(mario, p2, sx, sy) 
	if (mario.state == "jump" and mario.vy < 0 and sy > 0 and math.abs(sx) < 0.01) then
		print ("goomba killed!")
		mario.vy = -mario.vy
		-- goomba:changestate("dead")
		-- local s = script:new()
		-- s.actions = {
		-- 	[1] = {type="delay", sec=2},
		-- 	[2] = {type="callfunc", func = function() goomba:remove() end, after={1}}
		-- }
		-- monkey.play(s)
	else
		--mario_is_hit(mario)
		print ("dead")
	end
end


factory.koopa.response = function(p1, p2) 
	pritn ("koopa")
end

factory.mushroom.create = function(args)
	return factory.foe.create { 
		sprite="mushroom", 
		tag = variables.tags.mushroom,
		fliph = false,
		flipWhenPlatformEnds = false,
		pos = args.pos
	}
		
end

factory.mushroom1up.create = function(args)
	return factory.foe.create { 
		sprite="mushroom1up", 
		tag = variables.tags.mushroom1up,
		fliph = false,
		flipWhenPlatformEnds = false,
		pos = args.pos
	}
end

factory.goomba.create = function(args)
	return factory.foe.create { 
		sprite="goomba", 
		tag = variables.tags.goomba,
		fliph = false,
		flipWhenPlatformEnds = false,
		pos = args.pos
	}
end


factory.foe.create = function(args)
	assert(args.pos, "pos")	
	assert(args.sprite, "sprite")
	assert(args.tag, "tag")
	
	local flipHorizontal = args.fliph or false
	local flipWhenPlatformEnds = args.flipWhenPlatformEnds or false

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
    				tag=args.tag
				},
				{ 
					type="characterstate", 
					acceleration_ground = 0.05, 
					acceleration_air = 0.05, 
					speed = 75, 
					jump_velocity = variables.jump_velocity,
					can_duck = false,
					flip = flipHorizontal,
					anims = {
						idle = "walk",
						walk = "walk",
						jump_up = "walk",
						jump_down = "walk",
						turn = "walk",
						duck = "walk"
					},
					colliders = {
						{ key = "walk", value = { type="rect", width = 16, height = 16, offset={-8,0}}}
					},
					f = function() return {"", ""} end
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
					flip = flipWhenPlatformEnds
				}
			}
	}
end

-- register
table.insert (variables.collider.response, { tag = { 1, variables.tags.mushroom}, onenter = factory.mushroom.response })
table.insert (variables.collider.response, { tag = { 1, variables.tags.mushroom1up}, onenter = factory.mushroom1up.response })
table.insert (variables.collider.response, { tag = { 1, variables.tags.goomba}, onenter = factory.goomba.response })
table.insert (variables.collider.response, { tag = { 1, variables.tags.koopa}, onenter = factory.koopa.response })
