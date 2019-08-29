factory.goomba = {}

factory.goomba.response = function (mario, goomba, sx, sy) 
	if (goomba.state == "dead") then
		return
	end
	if (mario.state == "jump" and mario.vy < 0 and sy > 0 and math.abs(sx) < 0.01) then
		--monkey.removeFromId(goomba.id)
		mario.vy = 300
		local act = {
			{ type = action.set_state, args = { id = goomba.id, state = "dead"}	},
			{ type = action.delay, args = { sec= 2}},
			{ type = action.remove_object, args = {id=goomba.id}}
		}
		local s = script.make(act)
		monkey.play(s)
	else

	end

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
			{ 
				type = "smartcollider", 
				tag = variables.collision.tags.goomba, 
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
					{
						id = "dead",
						state = { type="simple", anim="die" }
					},					
				}
			},
			{ type ="enemyinput", left =true, flip=args.flip or false },

		}
	}

end
