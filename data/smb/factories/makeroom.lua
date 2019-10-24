factory.room = {}

factory.room.create = function(args)
	local room = {
		engines = {
			{ type = "scheduler"},
			{ 
				type = "collision", 
				size = {args.collisionSize, args.collisionSize}, 
				response = {
					{ tag = {variables.collision.tags.player, variables.collision.tags.brick_sensor}, onenter = factory.basic_brick.response },
					{ tag = {variables.collision.tags.player, variables.collision.tags.bonus_brick_sensor}, onenter = factory.bonus_brick.response },
					{ tag = {variables.collision.tags.player, variables.collision.tags.mushroom}, onenter = factory.mushroom.response },
					{ tag = {variables.collision.tags.player, variables.collision.tags.goomba}, onenter = factory.goomba.response },
					{ tag = {variables.collision.tags.player, variables.collision.tags.koopa}, onenter = factory.koopa.response },
					{ tag = {variables.collision.tags.player, variables.collision.tags.coin}, onenter = factory.coin.response },
					{ tag = {variables.collision.tags.player, variables.collision.tags.spawn}, onenter = factory.spawn.response },
					{ tag = {variables.collision.tags.player, variables.collision.tags.warp}, onenter = factory.warp.response, onleave = factory.warp.onexit },
					{ tag = {variables.collision.tags.player, variables.collision.tags.hotspot}, onenter = factory.hotspot.response },
				}
			},
			{ 
				type = "hotspotmanager",
				tag ="_hotspotmanager", 
				keys = {
					{ key = 299, func = function() monkey.endroom() end },				-- restart room
					{ key = 81, func = function () 
						local mario = monkey.getEntity("player")
						local isSuperMario = (mario:getinfo().supermario)
						factory.mario.supermario(mario, not isSuperMario)
					end }
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
					factory.mario.create { pos={args.start_pos[1]*16,args.start_pos[2]*16}},
				}
			},			
			[2] = {
				tag = "diag",
				camera = {
					tag = "diagcam",
					type ="ortho",
					size = {args.screen_size[1]*16, args.screen_size[2]*16},
					bounds = {0,0,args.screen_size[1]*16, args.screen_size[2]*16},
					viewport = {0, 0, args.screen_size[1]*16, args.screen_size[2]*16}
				},
				children = {
			 		{
						pos = {0,256,0},
						components = {
							{ type = "text", id="SCORE", font="main", size=8, }
						}
					}
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
