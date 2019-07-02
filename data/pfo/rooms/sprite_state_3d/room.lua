	local roomInfo = {
	worldWidth = 224,
	worldHeight = 16,
	startPos = {2, 4},
	collisionSize = 80,
	g = -10
}

local initscripts = {}


room = {

	engines = {
		{ type = "scheduler"},
		{ 
			type = "collision", 
			size = {roomInfo.collisionSize, roomInfo.collisionSize}, 
			response = {
				{ tag = {variables.tags.player, variables.tags.foe}, onenter = function(player, foe) 
					--print ("azzzz") 

					player_info = player:getinfo()
					if (player_info.invincible == false) then
						player_info.invincible = true
						local actions = {
							{ type = action.blink, args = { tag="player", duration = 5, blink_duration=0.1}},
							{ type = action.callfunc, args = { func = function() player_info.invincible = false end }}
						}
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
				pos = {0,0,-5}
			},
			children = {
				--factory.rect { pos = {0, 0}, img = "block1.png", width=69, height=2 },
				--factory.rect { pos = {10, 2}, flag=2|4, tag = 50, img = "block1.png", width=1, height=1 },	
				factory.path { pos={0,0}, A = {0,16}, B = {300,16} },
				factory.path { pos={0,0}, A = {300,16}, B = {400,116} },
				factory.character.create { 
					class = "player",
					model = "ryu", 
					scale =0.2,
					pos = {112, 64}, 
					speed =75, 
					acc_gnd = 0.05, 
					acc_air = 0.10, 
					jump_speed = 100, 
					gravity = -50,
					energy = 3,
					can_duck = true,
					custom_states = {
						{ id = "lowkick", state = { type="hit", anim="lowkick", acceleration = 0.05 }}
					},
					attack_tags = {
						{ anim ="lowkick", tag = variables.tags.player_attack, mask = 4|8 }
					},
					attack_moves = {
						{ type = "w", key = 81, state ="lowkick" },
						{ type = "j", key = 81, anim = "lowkick" }
					},
				},
				-- factory.character.create {
				-- 	class = "enemy_1",
				-- 	model = "goomba",
				-- 	pos = {180, 80},
				-- 	speed = 50,
				-- 	acc_gnd = 0.05,
				-- 	acc_air = 0.10,
				-- 	jump_speed = 0,
				-- 	gravity = -50,
				-- 	energy = 5
				-- },
				-- factory.character.create {
				-- 	class = "enemy_2",
				-- 	scale = 0.4,
				-- 	model = "ryu",
				-- 	pos = {32, 32},
				-- 	speed = 50,
				-- 	acc_gnd = 0.05,
				-- 	acc_air = 0.10,
				-- 	jump_speed = 0,
				-- 	gravity = -50,
				-- 	energy = 5,
				-- 	attack_prob = 0.7,
				-- 	attack_moves = {
				-- 		{ key = 81, odds = 10 }
				-- 	},
				-- 	attack = {
				-- 		{ type = "w", key = 81, state ="lowkick", anim="lowkick", tag = variables.tags.foe_attack, mask = 1 },
				-- 	},
				-- },
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
	},
}