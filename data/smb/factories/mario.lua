factory.mario = {}

factory.mario.supermario = function(player, value) 
	player:getinfo().supermario = value
	if (value == true) then
		player.state = "walk_big"
	else
		player.state = "walk"
	end
end

factory.mario.hit_by_enemy = function(player, enemy)
	-- if Mario is hit by enemy, what happens depends on whether mario is supermario or not
	local marioInfo = player:getinfo()
	local supermario = marioInfo.supermario

	if (supermario == true) then
		marioInfo.invincible = true
		player.state = "walk"
		local act = {
			{ type = action.blink, args = { id = player.id, duration=5, blink_duration= 0.2}},
			{ type = action.callfunc, args = { func = function() marioInfo.invincible=false end }}
		}
		local s = script.make(act)
		monkey.play(s)
	else
		local act = {
			{ type = action.set_state, args = { id = player.id, state = "dead"}	},
			{ type = action.delay, args = { sec= 1}},
			{ type = action.moveaccel, args = {id =player.id, initial_velocity = {0, 200}, acceleration = {0, variables.gravity}, ystop= 0}},
			{ type = action.remove_object, args = {id=player.id}},
			{ type = action.restart_room}
		}
		local s = script.make(act)
		monkey.play(s)
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
				supermario = false,
				invincible = false
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
					{
						id = "dead",
						state = { type="simple", anim="die" }
					},	
				},
			},
			{ type ="keyinput" },
			{ type="follow", cam ="maincam", relativepos={0,0,5}, up={0,1,0} }
		},
	}
end