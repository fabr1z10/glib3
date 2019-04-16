scumm.factory.hilly = function(args)
	--assert (args.scale_back, "scale_back")
	assert (args.depth_back, "depth_back")
	--assert (args.scale_front, "scale_front")
	assert (args.depth_front, "depth_front")
	--assert (args.scale_transition, "scale_transition")
	assert (args.depth_transition, "depth_transition")
	assert (args.connection_point_front, "connection_point_front")
	assert (args.connection_point_back, "connection_point_back")
	assert (args.shape_front, "shape_front")
	assert (args.shape_back, "shape_back")

	return {
		children = {
			scumm.factory.walkarea {
				tag = "walkarea_back",
				priority = 1, 
				scale = args.scale_back,
				depth = args.depth_back,
				-- trying to go front -> back
				handler = function(walkarea_from, x, y) 
					local actions = {
					 	{ type = scumm.action.walkto, args = {tag="player", pos = args.connection_point_front }},
					 	{ type = scumm.action.turn, args={tag="player", dir="north"}},
					 	{ type = action.treemove, args = {tag="player", parent="walkarea_front_back"}},
					 	{ type = action.animate, args ={tag="player", anim="walk_n"}},
					 	{ type = action.move, args = {tag="player", to = args.connection_point_back, speed = items["graham"].character.speed}},
					 	{ type = action.treemove, args = {tag="player", parent="walkarea_back"}},
					 	{ type = scumm.action.walkto, args = {tag="player", pos ={x,y}}},			 	
					}
					local s = script.make(actions)
					s.name="_walk"
					monkey.play(s)
				end,
				children = args.children_back,
				shape = args.shape_back
			},
			scumm.factory.walkarea {
				tag = "walkarea_front",
				priority = 2, 
				shape = args.shape_front,
				-- trying to go back -> front
				handler = function(walkarea_from, x, y) 
					local actions = {
					 	{ type = scumm.action.walkto, args = {tag="player", pos =args.connection_point_back}},
			 			{ type = action.treemove, args = {tag="player", parent="walkarea_front_back"}},
					 	{ type = action.animate, args ={tag="player", anim="walk_s"}},
					 	{ type = action.move, args = {tag="player", to =args.connection_point_front, speed = items["graham"].character.speed}},
					 	{ type = action.treemove, args = {tag="player", parent="walkarea_front"}},
			 			{ type = scumm.action.walkto, args = {tag="player", pos ={x,y}}},			 	
					}
					local s = script.make(actions)
					s.name="_walk"
					monkey.play(s)
				end,	
				depth = args.depth_front,
				scale = args.scale_front,
				children = args.children_front,
			},
			scumm.factory.walkarea {
				tag = "walkarea_front_back",
				priority = 0, 
				shape = args.shape_front,
				--handler = 10,
				scale = args.scale_transition,
				depth = args.depth_transition
			}
		}
	}
end
