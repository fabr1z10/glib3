factory.koopa = {}

factory.koopa.response = function (mario, koopa, sx, sy) 
    --print ("CALLED!!!")
	if (koopa.state == "hide") then
		if (mario.state == "jump" and mario.vy < 0 and sy > 0 and math.abs(sx) < 0.01) then
			mario.vy = 300
		end
		
		koopa:move(-10*sx,0,0)
		monkey.set_dir(koopa, sx<0)
		koopa:changestate("walk_2")
		local act = {
			--{ type = action.set_enemy_dir, args ={ id = koopa.id, left = sx>0}},
		-- 	{ type = action.set_state, args = { id = koopa.id, state = "walk_2"} },
			{ type = action.kill_script, args = {script = "koopa_back_" .. tostring(koopa.id)}},
		-- 	{ type = action.move, args = {id=koopa.id, by = {-2*sx, -2*sy}, imm=true}},
		}
		local s = script.make(act)
		monkey.play(s)	
		return	
	end

	if (mario.state == "jump" and mario.vy < 0 and sy > 0 and math.abs(sx) < 0.01) then
		local next_state = (koopa.state == "walk" or koopa.state == "walk_2") and "hide" or (koopa.state == "hi")
		mario.vy = 300
		local act = {
			{ type = action.set_state, args = { id = koopa.id, state = "hide"}	},
			{ type = action.callfunc, args = { func = function() 
				local actions = {
					{ type = action.delay, args = { sec = 3}},
					{ type = action.animate, args = {id = koopa.id, anim = "hide_blink"}},
					{ type = action.delay, args = { sec = 3}},
					{ type = action.set_state, args = { id = koopa.id, state = "walk"}	},

				}
				local s = script.make(actions)
				s.name = "koopa_back_" .. tostring(koopa.id)
				monkey.play(s)
			end}},
		}
		local s = script.make(act)
		monkey.play(s)
	else
		factory.mario.hit_by_enemy(mario, goomba)
	end

end

factory.koopa.create = function (args, pos) 
	glib.assert (args.sprite, "sprite")
	return {
		pos = {args.pos[1]*16, args.pos[2]*16, 0},
		type = "sprite",
		model = args.sprite,
		components = {
			{ type="controller2d", maxclimbangle = 80, maxdescendangle = 80, horizontalrays=4, verticalrays=4 },
			{ type="dynamics2d", gravity = variables.gravity },
			{ 
				type = "smartcollider", 
				tag = variables.collision.tags.koopa, 
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
							fliph = true, 
							jumpspeed = 0 
						}
					},
					{
						id = "jump",
						state = {
							type = "jump",
							speed = 20,
							acceleration = 0.10,
							fliph = true,
							animup = "walk",
							animdown = "walk"
						}
					},
					{
						id = "hide",
						state = { type="simple", anim="hide" }
					},
					{ 
						id = "walk_2", 
						state = {
							type = "walkside", 
							speed = 100, 
							acceleration = 0.05, 
							fliph = false, 
							jumpspeed = 0,
							walk_anim = "hide",
							jump_state = "jump_2"
						}
					},
					{
						id = "jump_2",
						state = {
							type = "jump",
							speed = 100,
							acceleration = 0.10,
							fliph = false,
							animup = "hide",
							animdown = "hide"
						}
					},					
				}
			},
			{ type ="enemyinput", left =true, flip=args.flip or false },

		}
	}

end
