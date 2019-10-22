factory.starman = {}

factory.starman.response = function (p1, p2) 
	monkey.removeFromId(p2.id)
end

factory.starman.script = function(id) 
	local actions = {
		{ type=action.move, args = { id = id, by = {0, engine.tilesize}, speed=10}},
		{ type=action.set_state, args = {id =id, state="jump"}},
		{ type=action.callfunc, args = { func = function() 
			local m  = monkey.getEntityFromId(id)
			m.vy = variables.jump_velocity * 0.5
		end}}
	}
	return actions
end

factory.starman.create = function (args, pos) 
	glib.assert (args.sprite, "sprite")
	local position = pos or {0, 0, 0}
	local tag = variables.collision.tags.starman
	return {
		type = "sprite",
		pos = position,
		model = args.sprite,
		components = {
			{ type="controller2d", maxclimbangle = 80, maxdescendangle = 80, horizontalrays=4, verticalrays=4 },
			{ type="dynamics2d", gravity = variables.gravity },
			{ 
				type = "smartcollider", 
				tag = tag, 
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
							speed = 100, 
							acceleration = 0.05, 
							fliph = false, 
							jumpspeed = 0 
						}
					},
					{
						id = "jump",
						state = {
							type = "jump",
							speed = 100,
							acceleration = 0.10,
							fliph = false,
							animup = "walk",
							animdown = "walk",
							bounce = true,
							bouncefactor=1.0,
						}
					},
				}
			},
			{ type ="enemyinput", left =false, flip=false },

		}
	}

end
