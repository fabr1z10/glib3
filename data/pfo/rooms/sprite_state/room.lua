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
				type="ortho",
				size = {256, 256},
				bounds = {0, 0, roomInfo.worldWidth*16, roomInfo.worldHeight*16},
				viewport = {0, 0, 256, 256}
			},
			children = {
				factory.rect { pos = {0, 0}, img = "block1.png", width=69, height=2 },
				{	
					 tag="player",
					 scale = 0.4,
					 type = "sprite",
					 model ="ryu",
					 pos = {112, 64, 0},
					 components = {
					 	{ type = "smartcollider", tag=1, flag=1, mask =2 },
						{ type ="keyinput" },
						{ type ="controller2d", maxclimbangle = 80, maxdescendangle = 80, horizontalrays=4, verticalrays=4 },
						{ type ="dynamics2d", gravity = -50 },
						{ type="follow", cam ="maincam", relativepos={0,0,5}, up={0,1,0} },
						{ type ="extstatemachine", initialstate = "walk",
							states = {
								{ 
								 	id = "walk", 
								 	state = {
								 		type="walkside", 
								 		speed = 75, 
								 		acceleration = 0.05, 
								 		fliph = true, 
								 		jumpspeed = 100,
								 		keys = {
								 			{ id = 81, action = "changestate", state = "lowkick" },
								 			{ id = 87, action = "callback", func = function() print ("W") end }
								 		}
								 	}
								},
								{ 
								 	id = "jump", 
								 	state = { 
								 		type="jump", 
								 		speed = 75, 
								 		acceleration = 0.10, 
								 		fliph = true, 
								 		animup = "jumpup",
								 		animdown = "jumpdown",
								 		keys = {
								 			{ id = 81, action = "playanim", anim = "lowkick" }
								 		}
								 	}
								},
								{ id = "lowkick", state = { type="hit", anim="lowkick", acceleration =0.05 }}
							}
						},
					}
				}
			}
		},
	},
}
