factory.mushroom = {}

factory.mushroom.response = function (p1, p2) 
	local mario = monkey.getEntity("player")
		
	--local isSuperMario = (mario:getinfo().supermario)
	factory.mario.change_state(mario, 2)

	monkey.removeFromId(p2.id)
end

factory.mushroom.script = function(id) 
	local actions = {
		{ type=action.move, args = { id = id, by = {0, engine.tilesize}, speed=5}},
		{ type=action.set_state, args = {id =id, state="walk"}}
	}
	return actions
end

factory.mushroom.create = function (args, pos) 
	print ("qui" .. tostring(pos[1]) .. args.sprite)
	glib.assert (args.sprite, "sprite")
	local position = pos or {0, 0, 0}
	local tag = variables.collision.tags.mushroom
	if (args.oneup) then tag = variables.collision.tags.mushroom1up end

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
