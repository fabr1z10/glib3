factory.char2d = {}

factory.char2d.create = function(args)
	glib.assert (args.model, "model")
	glib.assert (args.pos, "pos")
	glib.assert (args.speed, "speed")
	local z = args.z or 0
	local max_climb_angle = args.maxclimbangle or 80
	local max_descend_angle = args.maxdescendangle or 80
	local h_rays = args.horizontalrays or 4
	local v_rays = args.verticalrays or 4
	local acceleration = args.acceleration or 0.05
	local can_jump = args.can_jump
	local is_player = (args.tag ~= nil and args.tag == "player")
	local collision_flag = (is_player and variables.collision.flags.player or variables.collision.flags.foe)
	local collision_tag = (is_player and variables.collision.tags.player or variables.collision.tags.foe)
	local collision_attack_tag = (is_player and variables.collision.tags.player_attack or variables.collision.tags.foe_attack) 
	local collision_mask = (is_player and variables.collision.flags.foe or variables.collision.flags.player)

	local states = {
		{ 
			id = "walk", 
			state = {
				type = "walkside", 
				speed = args.speed, 
				acceleration = acceleration, 
				fliph = true, 
				jumpspeed = variables.jump_velocity
			}
		},
		{
			id = "jump",
			state = {
				type = "jump",
				speed = args.speed,
				acceleration = acceleration*2,
				fliph = true,
				animup = "jump",
				animdown = "jump"
			}			
		}
	}


	-- add attack states 
	local attack_tags = nil
	if (args.attack ~= nil) then
		ws = states[1]
		js = states[2]
		local keys = {}
		local jkeys = {}
		attack_tags = {}
		for _, value in ipairs(args.attack) do
			print ("adding " .. value.id .. " " .. tostring(value.key))
			table.insert (states, {
				id = value.id,
				state = {
					type ="hit",
					anim = value.anim,
					acceleration = acceleration
				}
			})
			table.insert (states, {
				id = value.id .. "_j",
				state = {
					type ="hitj",
					anim = value.anim,
					speed = args.speed,
					acceleration = acceleration
				}
			})
			table.insert (keys, { id=value.key, action="changestate", state=value.id})
			table.insert (jkeys, { id=value.key, action="changestate", state=value.id .. "_j"})
			table.insert (attack_tags, { anim=value.anim, tag = collision_attack_tag, mask = collision_mask })
		end
		ws.state.keys = keys
		js.state.keys = jkeys
	end
	

	local comp = {
		{ type="controller2d", maxclimbangle = max_climb_angle, maxdescendangle = max_descend_angle, horizontalrays=h_rays, verticalrays=v_rays},
		{ type="dynamics2d", gravity = variables.gravity },
		{ 
			type="extstatemachine", 
			initialstate = "walk",
			states = states
		},
		
		
	}

	if (args.tag ~= nil and args.tag == "player") then
		table.insert(comp, { type ="keyinput" })
		table.insert(comp, { type="follow", cam ="maincam", relativepos={0,0,5}, up={0,1,0} })
		table.insert(comp, {
			type = "smartcollider", 
			tag = variables.collision.tags.player, 
			flag = variables.collision.flags.player, 
			mask = variables.collision.flags.foe | variables.collision.flags.foe_attack,
			attack_tags = attack_tags
		})
	else 
		--table.insert(comp, { type ="keyinput" })
		table.insert(comp, {
			type = "smartcollider", 
			tag = variables.collision.tags.foe, 
			flag = variables.collision.flags.foe, 
			mask = variables.collision.flags.player | variables.collision.flags.player_attack
		})
	end

	local pos = args.pos 
	return {	
		tag = args.tag,
		type="sprite",
		model=args.model,
		anim="idle",
		scale =args.scale or 1,
		pos = {pos[1], pos[2], z},
		components = comp
	}
end