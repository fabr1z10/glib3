factory.bonus_brick = {}

factory.bonus_brick.response = function(p1, p2)

	local brick = p2:parent()
	local brick_info = brick:getinfo()
	if brick_info.hitsleft > 0 then
		brick_info.hitsleft = brick_info.hitsleft - 1
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
		if (brick_info.hitsleft == 0) then
			table.insert (actions, {
				type = action.animate,
				args = { id = brick.id, anim = "taken" }
			})
		end
		

		table.insert (actions, {
			type = action.callfunc,
			args = {
				func = function()
					local pos = {brick.x+0.5*engine.tilesize, brick.y, 1}
					local o = brick_info.factory(brick_info.args, pos)
					print("Mio cuggggg")
					local m1 = monkey.getEntity("main")
					local id = monkey.addEntity (o, m1)
					local actions = {
						{ type=action.move, args = { id = id, by = {0, engine.tilesize}, speed=5}},
						{ type=action.set_state, args = {id =id, state="walk"}}
					}
					local s = script.make(actions)
					monkey.play(s)
				end
				
			}
		})

		-- release the bonus
		local s = script.make(actions)
		monkey.play(s)
	end	
end

factory.bonus_brick.create = function(arg)
	glib.assert (arg.pos, "pos")
	glib.assert (arg.sprite, "sprite")
	glib.assert (arg.factory, "factory")
	glib.assert (arg.args, "args")
	local hitsleft = arg.hitsleft or 1
	local s = { type = "rect", width = engine.tilesize, height = engine.tilesize }
	local s1 = { type = "rect", width = engine.tilesize-4, height = 1.0}
	--local b = nextTag()
	local y = arg.pos[2]
	return {
		--tag = b,
		type = "sprite",
		model = arg.sprite,
		pos = {arg.pos[1], y, 0},
		components = {			
			--{ type="gfx", model=arg.sprite, anim="idle", width = engine.tilesize, height = engine.tilesize},	
			{ type="collider", shape=s, tag=10, flag = variables.collision.flags.platform, mask = 0},
			{ type="info", y = y, hitsleft = hitsleft, factory = arg.factory, args = arg.args },
		},
		children = {
			{
				pos = { 2, -0.5, 0},
				components = {
					{ 
						-- sensor for head-butt
						type="collider", 
						shape = s1, 
						tag = variables.collision.tags.bonus_brick_sensor, 
						flag = variables.collision.flags.foe, 
						mask = variables.collision.flags.player 
					},
					{ type="gfx", shape = s1, color = {255,0,0,255}}
				}
			}
		}
	}
end