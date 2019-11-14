factory.basic_brick = {}

factory.basic_brick.create_piece = function (pos, vx, vy, main) 

	local id1 = monkey.addEntity ({ type="sprite", model="brickpiece", pos = pos }, main)
	local act = {
		{ 
			type = action.moveaccel, 
			args = { 
				id = id1, 
				initial_velocity = {vx, vy}, 
				acceleration = {0, 0.5*variables.gravity}, 
				ystop = 0
			}
		},
		{
			type = action.remove_object, args = { id = id1}
		}
	}
	local s = script.make(act)
	monkey.play(s)

end

factory.basic_brick.response = function(p1, p2)
	local sm = p1:getinfo().state
	brick = p2:parent()

	if (sm > 1) then
		monkey.removeFromId(brick.id)
		local main = monkey.getEntity("main")
		factory.basic_brick.create_piece ( {brick.x, brick.y, 0}, 20, 120, main)
		factory.basic_brick.create_piece ( {brick.x, brick.y, 0}, -20, 120, main)
		factory.basic_brick.create_piece ( {brick.x, brick.y, 0}, 80, 90, main)
		factory.basic_brick.create_piece ( {brick.x, brick.y, 0}, -80, 90, main)
		-- generate pieces

	else	
		brick_info = brick:getinfo()

		local actions = {
			{ 
				type = action.moveaccel, 
				args = { 
					id = brick.id, 
					initial_velocity = {0, 50}, 
					acceleration = {0, 0.5*variables.gravity}, 
					ystop = brick_info.y
				}
			}
		}
		local s = script.make(actions)
		monkey.play(s)
	end	
end

factory.basic_brick.create = function(arg)
	glib.assert (arg.pos, "pos")
	glib.assert (arg.sprite, "sprite")

	local s = { type = "rect", width = engine.tilesize, height = engine.tilesize }
	local s1 = { type = "rect", width = engine.tilesize-4, height = 1.0}
	--local b = nextTag()
	local y = arg.pos[2]*engine.tilesize
	return {
		--tag = b,
		type = "sprite",
		model = arg.sprite,
		pos = {arg.pos[1]*engine.tilesize, y, 0},
		components = {			
			--{ type="gfx", model=arg.sprite, anim="idle", width = engine.tilesize, height = engine.tilesize},	
			{ type="collider", shape=s, tag=10, flag = variables.collision.flags.platform, mask = 0},
			{ type="info", y = y },
		},
		children = {
			{
				pos = { 2, -0.5, 0},
				components = {
					{ 
						-- sensor for head-butt
						type="collider", 
						shape = s1, 
						tag = variables.collision.tags.brick_sensor, 
						flag = variables.collision.flags.foe, 
						mask = variables.collision.flags.player 
					},
					{ type="gfx", shape = s1, color = {255,0,0,255}}
				}
			}
		}
	}
end