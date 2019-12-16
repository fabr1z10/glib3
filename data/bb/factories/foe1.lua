factory.foe1 = {}

factory.foe1.response = function (p, f, sx, sy) 

end

factory.foe1.create = function (args, pos) 
	glib.assert (args.pos, "pos")
	glib.assert (args.sprite, "sprite")
	glib.assert (args.speed, "speed")
	glib.assert (args.acceleration, "acceleration")
	return {
		pos = {args.pos[1]*16, args.pos[2]*16, 0},
		type = "sprite",
		model = args.sprite,
		components = {
			{ type="controller2d", maxclimbangle = 80, maxdescendangle = 80, horizontalrays=4, verticalrays=4 },
			{ type="dynamics2d", gravity = variables.gravity },
			--{ type="garbage", target="maincam", max_dist = {256, 256}},
			{ 
			 	type = "smartcollider", 
			 	tag = variables.collision.tags.basicfoe, 
			 	flag = variables.collision.flags.foe, 
			 	mask = variables.collision.flags.player
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
							acceleration = args.acceleration,
							fliph = true, 
							jumpspeed = 0 
						}
					},
					{
						id = "jump",
						state = {
							type = "jump",
							speed = args.speed,
							acceleration = args.acceleration,
							fliph = true,
							animup = "walk",
							animdown = "walk"
						}
					},
					-- {
					-- 	id = "dead",
					-- 	state = { type="simple", anim="die" }
					-- },					
				}
			},
			{ type ="enemyinputbase", left =true, flip=args.flip or false },

		}
	}

end
