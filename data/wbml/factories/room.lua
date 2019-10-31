factory.room = {}

factory.room.create = function(args)
	local room = {
		engines = {
			{ type = "scheduler"},
			{ 
				type = "collision", 
				size = {args.collisionSize, args.collisionSize}, 
				response = {
					-- place here the collision response map
					--{ tag = {variables.collision.tags.player, variables.collision.tags.brick_sensor}, onenter = factory.basic_brick.response },
				}
			},
			{ 
				type = "hotspotmanager",
				tag ="_hotspotmanager", 
				keys = {
					{ key = 299, func = function() monkey.endroom() end },				-- restart room, useful for debug
				},
			},
			{
				type ="dynamicworld",
				width = 256, 
				height = 256,
				cam ="maincam",
				items = {}
			}
		},
	    scene = {
			[1] = {
				tag = "main",
				camera = {
					tag = "maincam",
					type="ortho",
					size = {args.screen_size[1]*16, args.screen_size[2]*16},
					bounds = {0, 0, args.worldWidth*16, args.worldHeight*16},
					viewport = {0, 0, args.screen_size[1]*16, args.screen_size[2]*16}
				},
				children = {
					--factory.mario.create { pos={args.start_pos[1]*16,args.start_pos[2]*16}},
				}
			},			
			[2] = {
				tag = "diag",
				camera = {
					tag = "diagcam",
					type ="ortho",
					pos = {0,0,5},
					size = {args.screen_size[1]*16, args.screen_size[2]*16},
					bounds = {0,0,args.screen_size[1]*16, args.screen_size[2]*16},
					viewport = {0, 0, args.screen_size[1]*16, args.screen_size[2]*16}
				},
				children = {
					-- score and stats will go here
				}
			}
		},
		initscripts = {}
	}

	room.afterstartup = function()
 		for _, script in ipairs(room.initscripts) do
	 		script()
 		end		
 	end

	function room:add(items) 
		for _, v in ipairs(items) do
			table.insert(room.scene[1].children, v)
		end
	end
	function room:add_b(items) 
		for _, v in ipairs(items) do
			table.insert(room.scene[2].children, v)
		end
	end
	function room:add_d(items) 
		for _, v in ipairs(items) do
			print ("CIAO")
			table.insert(room.engines[4].items, v)
		end
	end

	return room
end
