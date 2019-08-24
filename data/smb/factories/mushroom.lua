factory.mushroom = {}

factory.mushroom.response = function (p1, p2) 
	monkey.removeFromId(p2.id)
end

factory.mushroom.create = function (args, pos) 
	print ("qui" .. tostring(pos[1]) .. args.sprite)
	glib.assert (args.sprite, "sprite")
	local position = pos or {0, 0, 0}
	print ("ppppp")
	return {
		type = "sprite",
		pos = position,
		model = args.sprite,
		components = {
			{ type="controller2d", maxclimbangle = 80, maxdescendangle = 80, horizontalrays=4, verticalrays=4 },
			{ type="dynamics2d", gravity = variables.gravity },
			{ 
				type = "smartcollider", 
				tag = variables.collision.tags.mushroom, 
				flag = variables.collision.flags.foe, 
				mask = variables.collision.flags.player
			},
			{ 
				type="extstatemachine", 
				initialstate = "idle",
				states = {
					{
						id = "idle",
						state = { type="simple", anim="walk" }
					},
					{ 
						id = "walk", 
						state = {
							type = "walkside", 
							speed = 20, 
							acceleration = 0.05, 
							fliph = false, 
							jumpspeed = 0 
						}
					},
					{
						id = "jump",
						state = {
							type = "jump",
							speed = 20,
							acceleration = 0.10,
							fliph = false,
							animup = "walk",
							animdown = "walk"
						}
					},
				}
			},
			{ type ="enemyinput", left =true, flip=false },

		}
	}

end
