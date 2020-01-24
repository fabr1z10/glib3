factory.mario = {}

factory.mario.models = {"mario", "supermario", "supermario_fire"}

factory.mario.change_state = function(player, value) 
	variables.state = value
	player:setmodel(factory.mario.models[value], "walk")
	-- Mario can fire only when state == 3
	variables.can_fire = (value == 3)
end

factory.mario.warp = function(player) 
	local st = player:getinfo().state
	player.state = factory.mario.warp_states[st]	
end

factory.mario.fire = function ()
	-- create a fire
	local mario = monkey.getEntity("player")
	local delta = mario.flipx and -10 or 10
	local pos = {mario.x + delta, mario.y+24, 0}
	local o = factory.fire.create({flipx = mario.flipx}, pos)

	local m1 = monkey.getEntity("main")
	local id = monkey.addEntity (o, m1)
	

end

factory.mario.hit_by_enemy = function(player, enemy)
	-- if Mario is hit by enemy, what happens depends on whether mario is supermario or not
	local marioInfo = player:getinfo()
	local supermario = marioInfo.supermario

	if (variables.state > 1) then
		marioInfo.invincible = true
		factory.mario.change_state(player, 1)
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
		model=factory.mario.models[variables.state],
		anim="idle",
		pos = {pos[1], pos[2], 0},
		components = {
			{ type="controller2d", maxclimbangle = 80, maxdescendangle = 80, horizontalrays=4, verticalrays=4 },
			{ type="dynamics2d", gravity = variables.gravity },
			{ 
				type = "smartcollider", 
				tag = variables.collision.tags.player, 
				flag = variables.collision.flags.player, 
				mask = variables.collision.flags.foe | variables.collision.flags.foe_attack,
				collision_overrides = {
					{ state = "warp", flag = 0, mask = 0, tag = 0},
					{ state = "slide", flag = 0, mask = 0, tag = 0},


				}
			},
			{
				type="info", 
				supermario = false,
				state = variables.state, -- 1 = small, 2 = supermario, 3 = supermario + fire
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
							jumpspeed = variables.jump_velocity,
							keys = {
								{ id = 341, action="callback", func= function() 
									if (variables.can_fire) then
										print ("fire!")
										factory.mario.fire()
									end 
									end 
								},
								{ id = 264, action="callback", func= function() if (variables.warpfunc ~= nil) then variables.warpfunc() end end },
							}
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
						id = "dead",
						state = { 
							type ="simple", 
							anim="die",							
						}
					},
					{
						id = "warp",
						state = {
							type = "simple",
							anim = "idle",
						}						
					},
					{
						id = "slide",
						state = {
							type = "simple",
							anim = "slide",
						}						
					},
				},
			},
			{ type ="keyinput" },
			{ type="follow", cam ="maincam", relativepos={0,0,5}, up={0,1,0} }
		},
	}
end