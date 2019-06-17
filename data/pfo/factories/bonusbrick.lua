factory.bonus_brick = {}

factory.bonus_brick.response = function(p1, p2) 
	-- if mario is large
	
	local taken = p2:get("taken")
	print ("taken = " .. tostring(taken))
	if (not taken) then	
		p2:set ("taken", true)
		local brick = p2:parent()
		local s = ms2 {
			{ type=action.animate, args = { id=brick.id, anim="taken" }},
			{ type=action.moveaccel, args = { id = brick.id, initial_velocity = {0, 50}, acceleration = {0, 0.5*variables.gravity}, ystop = brick.y}},
			{ type=action.create_entity, args = { func = p2:get("factory"), args = { pos={p2.x/16,p2.y/16} }, script = {
				{ type = action.enable_state_machine, args = { id = -1, value = false }},
				{ type = action.move, args = { id = -1, by = {0, 16}, speed =20}},
				{ type = action.enable_state_machine, args = { id = -1, value = true }},
			} } }
		}
		monkey.play(s)
	end
end

factory.bonus_brick.create = function(args)
	assert(args.pos, "pos")	
	assert(args.sprite, "sprite")
	assert(args.factory, "factory")

	local z = args.z or 0
	return {
		type = "sprite",
		tag = "giggi",
		model = args.sprite,
		-- basic brick
		pos = { args.pos[1] * engine.tilesize, args.pos[2] * tilesize, z },
		components = {
			{ type="collider", flag=2, mask=1, tag=1, shape = {type="rect", width=engine.tilesize, height=engine.tilesize} },
		},
		children = {
			{
				pos = {8, 0, 0},
				components = {
					{ type="collider", flag=4, mask=1, tag=variables.tags.bonus_brick, shape = {type="rect", width=8, height=4, offset = {-4,-2}} },
					{ type="properties", additional_info = { factory = args.factory, taken = false } }
				}
			}
		}
	}
end

-- register
table.insert (variables.collider.response, { tag = { 1, variables.tags.bonus_brick}, onenter = factory.bonus_brick.response })
