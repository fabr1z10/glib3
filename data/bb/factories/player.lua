factory.player = {}


factory.player.player_hits_enemy = function(player, enemy) 
end

factory.player.hit_by_enemy = function(player, enemy)
end

factory.player.makebubble = function(x, y, z) 
	local m = monkey.getEntity("main")
	local p = monkey.getEntity("player")
	monkey.addEntity({
		type="sprite",
		model="bubble", 
		pos = {x+8,y+8,z},
		components = { 
		 	{ type="controller2d", maxclimbangle = 80, maxdescendangle = 80, horizontalrays=4, verticalrays=4, maskup = 64 },
			{ 
				type = "smartcollider", 
				tag = variables.collision.tags.bubble, 
				flag = variables.collision.flags.bubble, 
				mask = variables.collision.flags.player | variables.collision.flags.foe | variables.collision.flags.bubble
			},		
			{ type ="luahook" },
		 	{
		 	 	type="extstatemachine", 
		 	 	initialstate = "walk",
		 	 	states = {
		 	 		{ 
		 	 			id = "walk", 
		 	 			state = {
		 	 				type = "bubble",
		 	 				left = p.flipx,
		 	 				speed = 100,
		 	 				speedup = 50,
		 	 			},
		 	 		},
 				}
 	 		}
		 }
	}, m)
end


factory.player.create = function(args)
	glib.assert (args.pos, "pos")
	glib.assert (args.id, "id")
	glib.assert (args.speed, "speed")
	local pos = args.pos 

	return {	
		tag = "player",
		type = "sprite",
		model = "bub",
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
							type = "bubwalk", 
							speed = args.speed,
							acceleration = 0.10, 
							fliph = true, 
							jumpspeed = variables.jump_velocity,
							firefunc = factory.player.makebubble,
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
								--{ id = 341, action = "changestate", state = "attack_jump" },
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
