-- a basic walking enemy. Won't do much, just walk and interact with player and surroundings.
-- No hits or special moves.
factory.character = {}

factory.character.classes = {
	player = {
		tag = "player",
		collision_flag = 1,
		collision_mask = 2 | 4,
		collision_tag = variables.tags.player,
		input = function(comps,args) 
			table.insert(comps, { type="keyinput"})
			table.insert(comps, { type="follow", cam ="maincam", relativepos={0,60,200}, up={0,1,0} })
			table.insert(comps, { type="info", invincible = false, energy = args.energy})
		end
	},
	enemy_1 = {
		collision_flag = 4,
		collision_mask = 1 | 2,
		collision_tag = variables.tags.foe,
		input = function(comps, args) 
			table.insert(comps, { type="enemyinput", attack = args.attack })
			table.insert(comps, {type="info", energy = args.energy})
		end
	},
	enemy_2 = {
		collision_flag = 8,
		collision_mask = 0,
		collision_tag = variables.tags.foe,
		input = function(comps, args) 
			table.insert(comps, { type="enemyinput", attack_moves = args.attack_ia.moves, attack_prob = args.attack_ia.prob})
			table.insert(comps, {type="info", energy = args.energy})
		end
	},

}

factory.character.create = function(args)
	glib.assert (args.class, " ** <character> requires class [str]")
	glib.assert (args.model, " ** <character> requires a model [str]")
	glib.assert (args.pos, " ** <character> requires pos [vec2]")
	glib.assert (args.speed, " ** <character> requires speed [float]")
	glib.assert (args.acc_gnd, " ** <character> requires acc_gnd [float]")
	glib.assert (args.acc_air, " ** <character> requires acc_air [float]")
	glib.assert (args.jump_speed, " ** <character> requires jump_speed [float]")

	local cc = factory.character.classes[args.class]
	if (cc == nil) then
		error("Unknown character class: " .. args.class, 1)
	end
	local max_climb_angle = args.max_climb_angle or 80
	local max_descend_angle = args.max_descend_angle or 80
	local gravity = args.gravity or variables.gravity
	local z = args.z or 0
	local can_duck = args.can_duck or false

	local state_component = { type ="extstatemachine", initialstate = "walk",
		states = {
			{ 
			 	id = "walk", 
			 	state = {
			 		type="walkside", 
			 		speed = args.speed, 
					acceleration = args.acc_gnd, 
					fliph = true, 
					jumpspeed = args.jump_speed,
					keys = {
						--{ id = 81, action = "changestate", state = "lowkick" },
						--{ id = 87, action = "callback", func = function() print ("W") end },
						--{ id = 264, action = "changestate", state = "duck"}
					}
				}
			},
			{ 
			 	id = "jump", 
			 	state = { 
			 		type="jump", 
			 		speed = args.speed,
					acceleration = args.acc_air,
					fliph = true, 
					animup = "jumpup",
					animdown = "jumpdown",
					keys = {
						--{ id = 81, action = "playanim", anim = "lowkick" }
					}
				}
			},
		}
	}
	if (can_duck) then
		table.insert(state_component.states, { id="duck", state={type="duck", acceleration=args.acc_gnd}})
		table.insert(state_component.states[1].state.keys, {id=264, action="changestate", state="duck"})
	end

	if (args.custom_states ~= nil) then
		for _, value in ipairs(args.custom_states) do
			table.insert(state_component.states, value)
		end
	end

	local attack_info = {}
	if (args.attack_tags ~= nil) then
		for _, value in ipairs(args.attack_tags) do
			table.insert (attack_info, { anim = value.anim, tag = value.tag,  mask = value.mask })
		end
	end

	if (args.attack_moves ~= nil) then
		for _, value in ipairs(args.attack_moves) do
			if (value.type == "w") then
				table.insert(state_component.states[1].state.keys, { id = value.key, action = "changestate", state = value.state })
				--table.insert(state_component.states, { id = value.state, state = { type="hit", anim = value.anim, acceleration = args.acc_gnd} })
			elseif (value.type == "j") then
				table.insert(state_component.states[2].state.keys, { id = value.key, action = "playanim", anim = value.anim })
			elseif (value.type == "d") then
				table.insert(state_component.states[3].state.keys, { id = value.key, action = "playanim", anim = value.anim })
			end
		end	
	end

	local components = {
		{ type = "smartcollider", tag=cc.collision_tag, flag=cc.collision_flag, mask =cc.collision_mask, attack_tags = attack_info },
		{ type ="controller2d", maxclimbangle = max_climb_angle, maxdescendangle = max_descend_angle, horizontalrays=4, verticalrays=4 },
		{ type ="dynamics2d", gravity = gravity },
		state_component
	}

	cc.input(components, args)





	local scale = args.scale or 1.0
	return
	{	
		tag=cc.tag,
		scale = scale,
		type = "sprite",
		model = args.model,
		pos = {args.pos[1], args.pos[2], z},
		components = components
	}
end
