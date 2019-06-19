-- a basic walking enemy. Won't do much, just walk and interact with player and surroundings.
-- No hits or special moves.
factory.enemy = {}
factory.enemy.create = function(args)
	glib.assert (args.model, " ** <enemy> requires a model")
	glib.assert (args.pos, " ** <enemy> requires a position")
	glib.assert (args.width, " ** <enemy> requires a width")
	glib.assert (args.height, " ** <enemy> requires a height")
	--glib.assert (args.anim, " ** <enemy> requires a anim")

	local tag = args.tag
	local scale = args.scale or 1
	return 				
	{	
		tag=tag,
		type="sprite",
		scale = scale,
		model=args.model,
		anim=args.anim,
		pos = args.pos,
		components = {
			{ type="controller2d", maxclimbangle = 80, maxdescendangle = 80, horizontalrays=4, verticalrays=4 },
			{ type="dynamics2d", gravity = -50 },
			{ type="collider", tag=variables.tags.enemy, flag=1, mask =2, shape = {type="rect", width=args.width, height=args.height, offset={-8,0}}},
			{ type="extstatemachine", initialstate = "walk",
			 	states = {
			 		{ 
			 			id = "walk", 
			 			state = {
			 				type="walkside", 
			 				speed = 75, 
			 				acceleration = 0.05, 
			 				fliph = true, 
			 				jumpspeed = 100,
			 				keys = {
			 				 	{ id = 81, action = "changestate", state = "ch1" },
			 				-- 	{ id = 87, action = "callback", func = function() print ("W") end }
			 				 }
		 				}
		 			},
		 			{ 
						id = "jump", 
						state = { 
							type="jump", 
							speed = 75, 
							acceleration = 0.10, 
							fliph = true, 
							animup = "jumpup",
							animdown = "jumpdown"
						}
		 			},
		 			{
		 				id = "ch1",
		 				state = {
		 					type = "ch1",
		 					target="player",
		 					animup="jumpup",
		 					animdown="jumpdown",
		 					speed = 500
		 				}
		 			}
		 		}
		 	},
			{ type ="enemyinput" },
		 },
	}

end
