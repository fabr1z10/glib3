--require("rooms/001/actions")

local dt=0.1
local d = {
	depth = { 
	    { rect = {0, 316, 0, 166}, dir = "y", bounds = {1, 0} } 
	}
}

local startPositionTable = {
	['start'] = {212, 77}
}

--local startPosition = startPositionTable[variables._previousroom]

room = {
	afterstartup = function()
		for k, v in ipairs(room.initstuff) do
			v()
		end
		--if (variables.troll_fed==false) then troll() end
	end,	
	initstuff = {},
	engines = {
		{ type = "scheduler" },

		{ 
			type = "collision", 
			size = {80, 80}, 
			response = {
				{ tag = {1, 10}, onenter = function() print ("CIAO") end }
			}
		},
			{ 
				type = "hotspotmanager",
				tag ="_hotspotmanager", 
				keys = {
					{ key = 299, func = function() monkey.endroom() end },
					{ key = 257, func = function() if (engine.config.pause == true) then exitpause() end end}
				},
				-- lmbclick is the func called when you click on no hotspot
				lmbclick = function(x, y) 
					-- if (variables.verbs[variables.currentverb].mnemonic == "walk") then
					-- 	local actions = scumm.ui.walk { pos = {x,y} }
					-- 	local s = script.make(actions)
					-- 	s.name="_walk"
					-- 	monkey.play(s)
					-- end
				end,	
				rmbclick = function() 
					local current = glib.get(engine.config.current_verb)
					local v = glib.get (engine.config.verbs[current].next)
					engine.config.current_verb = v
					--print ("current verb = " .. variables._actionInfo.verb.code)
					local cursor = monkey.getEntity("cursor")
					local a=engine.config.verbs[v].anim
					cursor.anim = a

				end
			},	
	},
	scene = {
		{
			tag = "main",
			camera = {
				tag = "maincam",
				type="ortho",
				size = {316, 166},
				bounds = {0, 0, 316, 166},
				viewport = {2, 25, 318, 25+166}
			},
			children = {
				{ pos = {0,0,-3}, components = { { type="gfx", image="bg001.png" }}},
				{ pos = {196, 39, 0.765}, components = { { type="gfx", image="bg002.png" }}},
				{ pos = {0,0,0},
				  components = {
					{ type = "collider", flag = 2, mask = 1, tag=1, 
						shape = { type="line", A = {0,19}, B = {184,19}}
					}
				  }
				},
				{ pos = {0,0,0},
				  components = {
					{ type = "collider", flag = 32, mask = 1, tag=10, 
						shape = { type="line", A = {0,6}, B = {228, 6}}
					},
					{ type = "info", func = function() 

						local actions = {
							{ type = action.move, args = {tag="player", by = {0,-5}, imm=true}},
							{ type = action.set_state, args = { tag="player",state="drown"}},
							{ type = action.delay, args = {sec = 2}},
							{ type = action.kq.showmessage, args = {msg=strings.room001[3]}}
							--{ type = action.callfunc, args = { func = function() displayBox(strings.room001[3]) end }}
							
						}		
						local s = script.make(actions)
						monkey.play(s)
						--displayBox("ciaociao") 
					end }
				  }
				},

				{
					tag="player",
					type="sprite",
					model="graham",
					pos = {20, 16, 0},
					components = {

						{ type ="keyinput" },
						{ type="depth",
							depth = { type="linear_y", values = {0, 1, 166, 0}}
						},
						{ 
							type="extstatemachine", 
							initialstate = "walk",
							states = {
								{ 
									id = "walk", 
									state = {
										type = "walk25", 
										speed = 50,
										acceleration = 0.1, 
										fliph=true
									}
								},
								{
									id = "drown",
									state = { type="simple", anim="drown"}

								}
							}
						}
					}
				},
				scumm.factory.item_sci { id="castle" },
				scumm.factory.item_sci { id="flags" },
				scumm.factory.item_sci { id="purple_flag"},
				scumm.factory.item_sci { id="yellow_flag"},
				scumm.factory.item_sci { id="cyan_flag"},
				scumm.factory.item_sci { id="alligator_1"},

			},				
		},
			{
				tag = "diag",
				camera = {
					tag = "maincam",
					type="ortho",
					size = {320, 200},
					bounds = {0, 0, 320, 200},
					viewport = {0, 0, 320, 200}
				},
				children = {
					{ 
						type = "sprite",
					 	model="cursor",
				     	tag = "cursor",
		 		    	pos={0,0,5},
					 	components = {
							{ type="cursor"}
					 	}
					}
				}
			}		

	}
}



local entry_cutscene = function() 
	print ("MIPIACE")
	local a1act= {
		{ ref=1, type = action.move, args = { tag="alli1", to = {280, 5}, speed=20, flip=true}},
		{ type = action.move, args = { tag="alli1", to = {20, 5}, speed=20, flip=true}},
	}

	local a1eat= {
		{ ref=1, type = action.delay, args = { sec = 2 }},
		{ type = action.animate, args = { tag="alli1", anim="eat", sync=true}},
		{ type = action.animate, args = { tag="alli1", anim="default"}},
	}
	local s = script.make(a1act,1)
	monkey.play(s)
	local s1 = script.make(a1eat,1)
	monkey.play(s1)

end

table.insert(room.initstuff, entry_cutscene)

-- 	        { pos = {8, 149, 1}, gfx = { model = "purple_flag", anim = "default" } },   
-- 			{ pos = {38, 150, 1}, gfx = { model = "yellow_flag", anim = "default" } }, 
-- 			{ pos = {68, 149, 1}, gfx = { model = "cyan_flag", anim = "default" } },
-- 			{ pos = {0, 0, 1}, tag="alli1", gfx = { model = "alligator", anim = "default" } }, 
-- 			{ pos = {20, 0, 1}, tag="alli2", gfx = { model = "alligator", anim = "default" } },
-- 		    makeGraham(startPosition[1], startPosition[2], d),
--  			makeShape { pos = {265, 39, 0}, angle = 0, tag=2, flag=2, shape = {type="rect", width=17, height=7, offset={0, 0}} },
--  			makeShape { pos = {0, 23, 0}, angle = 0, tag=2, flag=2, shape = {type="line", A={0,0},B={179,0}}, offset={0, 0} },
-- 			makeShape { pos = {0,0,0}, tag=11, flag = 4, shape = {type="line", A={1,10}, B={1,20}}, info = {roomto = "002"} },
--  			makeShape { pos = {0, 0, 0}, angle=0, tag = 10, flag = 4, shape = { type="compound", 
--  			shapes = {
--  				{ type="rect", width = 228, height = 6},
--  				{ type="poly", outline= {228,6,243,18,306,0}},
--  			}}},
--  			makeShape { pos ={0,0,0}, tag=10, flag=4, shape={type="poly", outline={182,25,176,44,197,39}}}
-- 		}
-- 	},
-- 	{
-- 		tag = "diag",
-- 		camera = {
-- 			tag = "maincam",
-- 			type="ortho",
-- 			size = {320, 200},
-- 			bounds = {0, 0, 320, 200},
-- 			viewport = {0, 0, 320, 200}
-- 		},
-- 		children = 
-- 		{
-- 			{
-- 				luakey = {
-- 					keys = {
-- 						{ key = 61, func = startSwimming },
--                         { key = 48, func = displayBox },
-- 						{ key = 257, func = exitpause }
-- 					}
-- 				}
-- 			}
-- 		}
-- 	}
-- }
-- }

-- for i = 1,10 do
--     table.insert(room.scene[1].children, { gfx = { shape = { type="line", A={40*i,0}, B={40*i, 200}}, color={255, 255, 255, 255} }})
--     table.insert(room.scene[1].children, { gfx = { shape = { type="line", A={0, 40*i}, B={320, 40*i}}, color={255, 255, 255, 255} }})
-- end

-- -- end room

-- function room.init()
-- end

-- function room.start()

-- end

-- function moveAlligator(name)
-- 	local s = script:new(name)
-- 	local x = math.random(0, 243)
-- 	local y = math.random(0, 5)
-- 	local a = monkey.getEntity(name)
-- 	local flip = false
-- 	if (x < a.x) then
-- 		flip = true
-- 	else
-- 		flip = false
-- 	end
-- 	--print ("Moving alligator to " .. tostring(x) .. ", " .. tostring(y))
-- 	s.actions = {
-- 		[1] = { type ="animate", actor =name, anim="default", flipx = flip },
-- 		[2] = { type = "move", actor=name, to={x, y}, speed=30.0, after={1} },
-- 		[3] = { type = "callfunc", func = curry(moveAlligator, name),after={2}}
-- 	}
-- 	monkey.play(s)
	
-- end

-- function room.afterstartup() 
-- 	moveAlligator("alli1")
-- 	moveAlligator("alli2")
-- end



