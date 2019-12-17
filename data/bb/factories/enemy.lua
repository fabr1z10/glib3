factory.goomba = {}

factory.goomba.response = function (mario, goomba, sx, sy) 
	if (goomba.state == "dead") then
		return
	end
	if (mario:getinfo().invincible == true) then
		return
	end
	--str:sub(1, #start) == start
	if (mario.state:sub(1, 4) == "jump" and mario.vy < 0 and sy > 0 and math.abs(sx) < 0.01) then
		--monkey.removeFromId(goomba.id)
		mario.vy = 300		
		local act = {
			{ type = action.set_state, args = { id = goomba.id, state = "dead"}	},
			{ type = action.delay, args = { sec= 2}},
			{ type = action.remove_object, args = {id=goomba.id}}
		}
		local s = script.make(act)
		monkey.play(s)
		add_score (100)

	else
		factory.mario.hit_by_enemy(mario, goomba)
	end

end

factory.goomba.create = function (args, pos) 
	glib.assert (args.sprite, "sprite")
	return {
		pos = {args.pos[1]*16, args.pos[2]*16, 0},
		type = "sprite",
		model = args.sprite,
		components = {
			{ type="controller2d", maxclimbangle = 80, maxdescendangle = 80, horizontalrays=4, verticalrays=4 },
			{ type="dynamics2d", gravity = variables.gravity },
			{ type="garbage", target="maincam", max_dist = {256, 256}},
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
							type = "zenchan", 
							left=true,
							speed = {2, 2},
							acceleration = 0.05, 
							fliph = true, 
							jumpspeed = 0 
						}
					},
				}
			},
			{ type ="basicenemyinput", left =true, flip=args.flip or false },

		}
	}

end
