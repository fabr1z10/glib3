factory.basic_brick = {}

factory.basic_brick.response = function(p1, p2) 
	-- if mario is large
	local supermario = p1:get("supermario")
	print ("supermario = " .. tostring(supermario))
	p1.vy = -p1.vy
	
	if (supermario == true) then
		local piece = p2:get("piece_sprite")
		
		local x = p2.x
		local y = p2.y
		-- print (piece .. " " .. tostring(x) .. " " .. tostring(y))
		p2:parent():remove()
		local main = monkey.getEntity("main")
		local initial_velocities = { {20, 40}, {40, 20}, {-20,40}, {-40, 20}}
		for i = 1,4 do
			local id = monkey.addEntity ({
		 		tag = tag,
		 		type ="sprite",
		 		pos = {x, y, 1},
		 		model = piece
			}, main)
			print ("dynamically created entity with id: " .. tostring(id))
			local s = ms2 {
				{ type=action.moveaccel, args = { id = id, initial_velocity = initial_velocities[i], acceleration = {0, 0.5*variables.gravity}, ystop = -20}},
				{ type=action.remove_object, args = { id = id} }
			}
			monkey.play(s)
		end
	else
		-- nothing happens
		local brick = p2:parent()
		local s = ms2 {
			{ type=action.moveaccel, args = { id = brick.id, initial_velocity = {0, 50}, acceleration = {0, 0.5*variables.gravity}, ystop = brick.y }}
		}
		monkey.play(s)
	end
end

factory.basic_brick.create = function(args)
	assert(args.pos, "pos")	
	assert(args.sprite, "sprite")
	assert(args.piece_sprite, "piece_sprite")

	local z = args.z or 0
	return {
		type = "sprite",
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
					{ type="collider", flag=4, mask=1, tag=variables.tags.basic_brick, shape = {type="rect", width=8, height=4, offset = {-4,-2}} },
					{ type="properties", additional_info = { piece_sprite = args.piece_sprite} }
				}
			}
		}
	}
end

-- register
table.insert (variables.collider.response, { tag = { 1, variables.tags.basic_brick}, onenter = factory.basic_brick.response })
