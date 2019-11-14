factory.room = {}

factory.room.create = function(args)
	variables.world_name = args.name or ""
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
					{ tag = {variables.collision.tags.player, variables.collision.tags.flower}, onenter = factory.flower.response },
					{ tag = {variables.collision.tags.player, variables.collision.tags.goomba}, onenter = factory.goomba.response },
					{ tag = {variables.collision.tags.player, variables.collision.tags.koopa}, onenter = factory.koopa.response },
					{ tag = {variables.collision.tags.player, variables.collision.tags.coin}, onenter = factory.coin.response },
					{ tag = {variables.collision.tags.player, variables.collision.tags.spawn}, onenter = factory.spawn.response },
					{ tag = {variables.collision.tags.player, variables.collision.tags.warp}, onenter = factory.warp.response, onleave = factory.warp.onexit },
					{ tag = {variables.collision.tags.player, variables.collision.tags.hotspot}, onenter = factory.hotspot.response },
					{ tag = {variables.collision.tags.fire, variables.collision.tags.goomba}, onenter = factory.fire.response },
				}
			},
			{ 
				type = "hotspotmanager",
				tag ="_hotspotmanager", 
				keys = {
					{ key = 299, func = function() monkey.endroom() end },				-- restart room
					{ key = 81, func = function () 
						local mario = monkey.getEntity("player")
						--local isSuperMario = (mario:getinfo().state)
						factory.mario.change_state(mario, 2)
					end },
					{ key = 87, func = function () 
						local mario = monkey.getEntity("player")
						--local isSuperMario = (mario:getinfo().state)
						factory.mario.change_state(mario, 3)
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
					pos = {0,0,5},
					size = {args.screen_size[1]*16, args.screen_size[2]*16},
					bounds = {0,0,args.screen_size[1]*16, args.screen_size[2]*16},
					viewport = {0, 0, args.screen_size[1]*16, args.screen_size[2]*16}
				},
				children = {
			 		{
						pos = {24,248,0},
						components = {
							{ type = "text", id="MARIO", font="main", size=8, }
						}
					},
					{
						tag = "score_label",
						pos = {24, 240, 0},
						components = {
							{ type = "text", id=string.format("%06d", variables.score), font="main", size=8, }	
						}
					},
			 		{
						pos = {144,248,0},
						components = {
							{ type = "text", id="WORLD", font="main", size=8, }
						}
					},	
			 		{
						pos = {164,236,0},
						components = {
							{ type = "text", id=variables.world_name, font="main", size=8, align="center" }
						}
					},						
					{
						pos = {232,248,0},
						components = {
							{ type = "text", id="TIME", font="main", size=8, align="topright" }
						}
					},	
					{
						tag = "time_label",
						pos = {232,240,0},
						components = {
							{ type = "text", id=tostring(variables.time), font="main", size=8, align="topright" }
						}
					},				
					{
						pos = {96, 232, 0},
						type="sprite",
						model="coin_counter"
					},
					{
						pos = {108,240,0},
						components = {
							{ type = "text", id="x", font="main", size=8 }
						}
					},	
					{
						tag = "coin_label",
						pos = {116, 240, 0},
						components = {
							{ type = "text", id=string.format("%02d", variables.coins), font="main", size=8, }	
						}
					},
				}
			}
		},
		initscripts = {}
	}

	room.next = args.next

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


	table.insert (room.initscripts, function()
		local actions = {
			{ type = action.repeat_forever, args = { interval = 1, func = function() 
				variables.time = variables.time - 1
				local l = monkey.getEntity("time_label")
				l:settext(tostring(variables.time))
			end} }
		}
		local s = script.make(actions)
		s.name = "_timer"
		monkey.play(s)	
	end)


 	return room
end
