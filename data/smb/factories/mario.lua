factory.mario = {}

factory.mario.supermario = function(player, value) 
	player:getinfo().supermario = value
	if (value == true) then
		player.state = "walk_big"
	else
		player.state = "walk"
	end

end

factory.mario.create = function(args)
	local pos = args.pos 
	return {	
		tag="player",
		type="sprite",
		model="mario",
		anim="idle",
		pos = {pos[1], pos[2], 0},
		components = {
			{ type="controller2d", maxclimbangle = 80, maxdescendangle = 80, horizontalrays=4, verticalrays=4 },
			{ type="dynamics2d", gravity = variables.gravity },
			{ 
				type = "smartcollider", 
				tag = variables.collision.tags.player, 
				flag = variables.collision.flags.player, 
				mask = variables.collision.flags.foe | variables.collision.flags.foe_attack
			},
			{
				type="info", 
				supermario = false
			},
			{ 
				type="extstatemachine", 
				initialstate = "walk",
				states = {
					{ 
						id = "walk", 
						state = {
							type = "walkside", 
							speed = 75, 
							acceleration = 0.05, 
							fliph = true, 
							jumpspeed = variables.jump_velocity 
						}
					},
					{
						id = "jump",
						state = {
							type = "jump",
							speed = 75,
							acceleration = 0.10,
							fliph = true,
							animup = "jump",
							animdown = "jump"
						}
					},
					{ 
						id = "walk_big", 
						state = {
							type = "walkside", 
							speed = 75, 
							acceleration = 0.05, 
							fliph = true, 
							jumpspeed = variables.jump_velocity,
							jump_state = "jump_big",
							walk_anim = "walk_big",
							idle_anim = "idle_big"
						},
					},
					{
						id = "jump_big",
						state = {
							type = "jump",
							speed = 75,
							acceleration = 0.10,
							fliph = true,
							animup = "jump_big",
							animdown = "jump_big",
							walk_state = "walk_big"
						}
					},
				},
			},
			{ type ="keyinput" },
			{ type="follow", cam ="maincam", relativepos={0,0,5}, up={0,1,0} }
		},
	}
end