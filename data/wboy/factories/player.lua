factory.player = {}


factory.player.player_hits_enemy = function(player, enemy) 
end

factory.player.hit_by_enemy = function(player, enemy)
end


factory.player.create = function(args)
	glib.assert (args.pos, "pos")
	glib.assert (args.id, "id")
	glib.assert (args.speed, "speed")
	local pos = args.pos 

	return {	
		tag = "player",
		type = "sprite",
		model = "wboy",
		anim = "idle",
		scale = scale,
		pos = {pos[1] * engine.tilesize, pos[2] * engine.tilesize, 0},
		components = {
			{ type="controller2d", maxclimbangle = 80, maxdescendangle = 80, horizontalrays=4, verticalrays=4 },
			{ type="dynamics2d", gravity = variables.gravity },
			{ 
				type = "smartcollider", 
				tag = variables.collision.tags.player, 
				flag = variables.collision.flags.player, 
				mask = variables.collision.flags.foe | variables.collision.flags.foe_attack,
			},
			{
				type="info", 
				invincible=true
			},
			{ 
				type="extstatemachine", 
				initialstate = "walk",
				states = {
					{ 
						id = "walk", 
						state = {
							type = "walkside", 
							speed = args.speed,
							acceleration = 0.10, 
							fliph = true, 
							jumpspeed = variables.jump_velocity,
							keys = {
								--{ id = 341, action = "changestate", state = "attack" },
								--{ id = 264, action="callback", func= function() if (variables.warpfunc ~= nil) then variables.warpfunc() end end }	,

							}
						}
					},
					{
						id = "jump",
						state = {
							type = "jump",
							speed = args.speed,
							acceleration = 0.10,
							fliph = true,
							animup = "jumpup",
							animdown = "jumpdown",
							keys = {
								{ id = 341, action = "changestate", state = "attack_jump" },
							}							
						}
					},
					{
						id = "dead",
						state = { type="simple", anim="dead" }
					},						

				},
			},
			{ type ="keyinput" },
			{ type="follow", cam ="maincam", relativepos={0,0,5}, up={0,1,0} }
		},
	}
end
