factory.goomba = {}

factory.goomba.response = function (p1, p2) 
	monkey.removeFromId(p2.id)
end

factory.goomba.create = function (args, pos) 
	glib.assert (args.sprite, "sprite")
	return {
		pos = {args.pos[1], args.pos[2], 0},
		type = "sprite",
		model = args.sprite,
		components = {
			{ type="controller2d", maxclimbangle = 80, maxdescendangle = 80, horizontalrays=4, verticalrays=4 },
			{ type="dynamics2d", gravity = variables.gravity },
			--{ 
			-- 	type = "smartcollider", 
			-- 	tag = variables.collision.tags.mushroom, 
			-- 	flag = variables.collision.flags.foe, 
			-- 	mask = variables.collision.flags.player
			-- },
			-- { 
			-- 	type="extstatemachine", 
			-- 	initialstate = "walk",
			-- 	states = {
			-- 		{ 
			-- 			id = "walk", 
			-- 			state = {
			-- 				type = "walkside", 
			-- 				speed = 20, 
			-- 				acceleration = 0.05, 
			-- 				fliph = false, 
			-- 				jumpspeed = 0 
			-- 			}
			-- 		},
			-- 		{
			-- 			id = "jump",
			-- 			state = {
			-- 				type = "jump",
			-- 				speed = 20,
			-- 				acceleration = 0.10,
			-- 				fliph = false,
			-- 				animup = "walk",
			-- 				animdown = "walk"
			-- 			}
			-- 		},
			-- 	}
			-- },
			-- { type ="enemyinput", left =true, flip=args.flip or false },

		}
	}

end
