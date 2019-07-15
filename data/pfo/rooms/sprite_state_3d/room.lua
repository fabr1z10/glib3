	local roomInfo = {
	worldWidth = 224,
	worldHeight = 16,
	startPos = {2, 4},
	collisionSize = 80,
	g = -10
}

local initscripts = {}


room = {
	afterstartup = function()
		for k, v in ipairs(room.initstuff) do
			v()
		end
	end,
	initstuff = {
		[1] = function() 
			variables.update_game_variable("energy", variables.game_variables.energy.value)
		end
	},
	engines = {
		{ type = "scheduler"},
		{ 
			type = "collision", 
			size = {roomInfo.collisionSize, roomInfo.collisionSize}, 
			response = {
				{ tag = {variables.tags.player, variables.tags.foe}, onenter = function(player, foe) 
					print ("azzzz") 

					player_info = player:getinfo()
					if (player_info.invincible == false) then
						player_info.invincible = true
						local actions = {
							{ type = action.blink, args = { tag="player", duration = 5, blink_duration=0.1}},
							{ type = action.callfunc, args = { func = function() player_info.invincible = false end }}
						}

						variables.update_game_variable("energy", variables.game_variables.energy.value -1)
						local s = script.make(actions)
						monkey.play(s)
				    end
				end
				},
				{ tag = {variables.tags.player_attack, variables.tags.foe}, onenter = generic_hit },
				{ tag = {variables.tags.foe_attack, variables.tags.player}, onenter = generic_hit },
				{ tag = {variables.tags.player_attack, variables.tags.foe}, onenter = player_hits },
				{ tag = {variables.tags.foe_attack, variables.tags.player}, onenter = player_is_hit },
				{ tag = {variables.tags.player_attack, variables.tags.hittable_block}, onenter = mario_removeenemy }
			}
		},
		{
			type ="dynamicworld",
			width = 256, 
			height = 256,
			cam ="maincam",
			items = {
			}
		}
	},

    scene = {
		[1] = {
			tag = "main",
			camera = {
				tag = "maincam",
				type="perspective",
				pos = {0,0,100}
			},
			children = {
				{ pos = {0, 0, 0}, components = { { type ="light", class="ambient", color ={128, 128, 128}}}},
				{ pos = {0,0,0}, components = {{type="light", class="directional", color={255, 255, 255}, dir = {-0.8, 0.3, 0.5}}}},
				{
					tag=" ciaoppo",
					pos = {0,0,-8},
					components = {
						{ 
							type="gfx", 
							-- prim3d = { 
							-- 	type="box3d", 
							-- 	width = 100, height=16, depth = 16, 
							-- 	texture = { 
							-- 		top = { name="block1.png", rep={16, 16}},
							-- 		side = { name="brick2.png", rep={16, 16}}
							-- 	} 
							-- }
							prim3d = {
								type = "trapezoid3d",
								points = {0,16,300,16,310,21,320,31,330,46,340,56,350,61,360,61,400,61},
								depth = 16,
								y = -100,
								texture = {
									top = { name="block1.png", rep={16, 16}},	
									side = {name="brick2.png", rep={16, 16}}								
								}
							}
						}
					}

				},
				{
					tag = "parallaxback",
					pos = {0, 0, 0},
					components ={
						{ type = "parallax3d", img = "bg3.png", cam = "maincam", z = 400}
					}
				},
				-- {
				-- 	pos={0,0,-100},
				-- 	components = {
				-- 		{ type="gfx", image="bg2.png", width = 1000, height=1000}
				-- 	}

				-- },
				--factory.rect { pos = {0, 0}, img = "block1.png", width=69, height=2 },
				--factory.rect { pos = {10, 2}, flag=2|4, tag = 50, img = "block1.png", width=1, height=1 },	
				factory.path { pos={0,0}, A = {0,16}, B = {300,16} },
				--factory.path { pos={0,0}, A = {300,16}, B = {400,116} },
				factory.character.create { 
					class = "player",
					--model = "ryu", 
					model = "wbml",
					scale =0.5,
					pos = {112, 64}, 
					speed =75, 
					acc_gnd = 0.05, 
					acc_air = 0.10, 
					jump_speed = 100, 
					gravity = -50,
					energy = 3,
					can_duck = false,
					custom_states = {
						{ id = "lowkick", state = { type="hit", anim="attack", acceleration = 0.05 }}
					},
					attack_tags = {
						{ anim ="attack", tag = variables.tags.player_attack, mask = 4|8 }
					},
					attack_moves = {
						{ type = "w", key = 81, state ="lowkick" },
						{ type = "j", key = 81, anim = "attack" }
					},
				},
				-- factory.character.create {
				-- 	class = "enemy_1",
				-- 	model = "goomba",
				-- 	pos = {180, 80},
				-- 	scale = 0.2,
				-- 	speed = 50,
				-- 	acc_gnd = 0.05,
				-- 	acc_air = 0.10,
				-- 	jump_speed = 0,
				-- 	gravity = -50,
				-- 	energy = 5,


				-- },
				factory.character.create {
					class = "enemy_2",
					scale = 0.4,
					model = "ryu",
					pos = {32, 32},
					speed = 30,
					scale = 0.25,
					acc_gnd = 0.05,
					acc_air = 0.10,
					jump_speed = 0,
					gravity = -50,
					energy = 5,
					attack_prob = 0.7,
					custom_states = {
						{ id = "lowkick", state = { type="hit", anim="lowkick", acceleration = 0.05 }}
					},
					attack_tags = {
						{ anim ="lowkick", tag = variables.tags.foe_attack, mask = 1 }
					},
					attack_moves = {
						{ type = "w", key = 81, state ="lowkick" },
						{ type = "j", key = 81, anim = "lowkick" }
					},				
					attack_ia = {
				 		prob = 0.0,
						moves = {
				 			{ key = 81, odds = 10 }
				 		}
				 	}
				},
				-- factory.character.create {
				-- 	class = "enemy_2",
				-- 	scale = 0.6,
				-- 	model = "ryu",
				-- 	pos = {32, 32},
				-- 	speed = 50,
				-- 	acc_gnd = 0.05,
				-- 	acc_air = 0.10,
				-- 	jump_speed = 0,
				-- 	gravity = -50,
				-- 	energy = 5,
				-- 	custom_states = {
				-- 		{ id = "jump_attack", state = { type="ch1", animup="jumpup", animdown="jumpdown_attack", speed = 300, target="player" }}
				-- 	},
				-- 	attack_tags = {
				-- 		{ anim="jumpdown_attack", tag = variables.tags.foe_attack, mask = 1 }
				-- 	},
				-- 	attack_ia = {
				-- 		prob = 0.7,
				-- 		moves = {
				-- 			{ key = 81, odds = 10 }
				-- 		}
				-- 	},
				-- 	attack_moves = {
				-- 		{ type = "w", key = 81, state ="jump_attack" },
				-- 	},
				-- },


				-- {	
				-- 	 tag="player",
				-- 	 scale = 0.4,
				-- 	 type = "sprite",
				-- 	 model ="ryu",
				-- 	 pos = {112, 64, 0},
				-- 	 components = {
				-- 	 	{ type = "smartcollider", tag=1, flag=1, mask =2 },
				-- 		{ type ="keyinput" },
				-- 		{ type ="controller2d", maxclimbangle = 80, maxdescendangle = 80, horizontalrays=4, verticalrays=4 },
				-- 		{ type ="dynamics2d", gravity = -50 },
				-- 		{ type="follow", cam ="maincam", relativepos={0,0,5}, up={0,1,0} },
				-- 		{ type ="extstatemachine", initialstate = "walk",
				-- 			states = {
				-- 				{ 
				-- 				 	id = "walk", 
				-- 				 	state = {
				-- 				 		type="walkside", 
				-- 				 		speed = 75, 
				-- 				 		acceleration = 0.05, 
				-- 				 		fliph = true, 
				-- 				 		jumpspeed = 100,
				-- 				 		keys = {
				-- 				 			{ id = 81, action = "changestate", state = "lowkick" },
				-- 				 			{ id = 87, action = "callback", func = function() print ("W") end },
				-- 				 			{ id = 264, action = "changestate", state = "duck"}
				-- 				 		}
				-- 				 	}
				-- 				},
				-- 				{ 
				-- 				 	id = "jump", 
				-- 				 	state = { 
				-- 				 		type="jump", 
				-- 				 		speed = 75, 
				-- 				 		acceleration = 0.10, 
				-- 				 		fliph = true, 
				-- 				 		animup = "jumpup",
				-- 				 		animdown = "jumpdown",
				-- 				 		keys = {
				-- 				 			{ id = 81, action = "playanim", anim = "lowkick" }
				-- 				 		}
				-- 				 	}
				-- 				},
				-- 				{
				-- 					id = "duck",
				-- 					state = { type="duck", acceleration=0.10}
				-- 				},
				-- 				{ id = "lowkick", state = { type="hit", anim="lowkick", acceleration =0.05 }}

				-- 			}
				-- 		},
				-- 	}
				-- }
			}
		},
		[2] = {
			tag = "main",
			camera = {
				tag = "maincam",
				type="ortho",
				size = {256, 256},
				bounds = {0, 0, roomInfo.worldWidth*16, roomInfo.worldHeight*16},
				viewport = {0, 0, 256, 256}
			},
			children = {
				{ tag="txt_energy", pos = {10,246,0}, components = { { type = "text", id="f", font="main", size=8 }}},

				-- { pos = {256,256,0}, components = {	{ type = "text", id="TOP RIGHT", font="main", size=8, align = "topright" }}},
				-- { pos = {0,0,0}, components = { { type = "text", id="BOTTOM LEFT", font="main", size=8, align = "bottomleft" }}},
				-- { pos = {256,0,0}, components = {	{ type = "text", id="BOTTOM RIGHT", font="main", size=8, align = "bottomright" }}},
				-- { pos = {128,256,0}, components = {	{ type = "text", id="TOP", font="main", size=8, align = "top" }}},
				-- { pos = {128,0,0}, components = {	{ type = "text", id="BOTTOM", font="main", size=8, align = "bottom" }}},
				-- { pos = {128,128,0}, components = {	{ type = "text", id="CENTER", font="main", size=8, align = "center" }}},
			}
		},
	},
}


--variables.update_game_variable("energy", variables.game_variables.energy.value)

