factory.fire = {}

factory.fire.response = function (p1, p2) 
	monkey.removeFromId(p1.id)
	monkey.removeFromId(p2.id)
end

factory.fire.create = function (args, pos) 
	local position = pos or {0, 0, 0}
	local tag = variables.collision.tags.fire
	return {
		type = "sprite",
		pos = position,
		model = "fire",
		--flipx = args.flipx,
		components = {
			{ type="controller2d", maxclimbangle = 80, maxdescendangle = 80, horizontalrays=4, verticalrays=4 },
			{ type="dynamics2d", gravity = variables.gravity },
			{ 
				type = "smartcollider", 
				tag = tag, 
				flag = variables.collision.flags.player_attack, 
				mask = variables.collision.flags.foe
			},
			{ 
				type="extstatemachine", 
				initialstate = "walk",
				states = {
					{
						id = "idle",
						state = { type="simple", anim="walk" }
					},
					{ 
						id = "walk", 
						state = {
							type = "walkside", 
							speed = 300, 
							acceleration = 0, 
							fliph = false, 
							jumpspeed = 0 
						}
					},
					{
						id = "jump",
						state = {
							type = "jump",
							speed = 300,
							acceleration = 0,
							fliph = false,
							animup = "walk",
							animdown = "walk",
							bounce = true,
							bouncefactor=200.0,
						}
					},
				}
			},
			{ type ="enemyinput", left =args.flipx, flip=false },

		}
	}

end
