local roomInfo = {
	worldWidth = 224,
	worldHeight = 16,
	screen_size = {16, 16},
	start_pos = {2, 2},
	collisionSize = 80,
	g = -10
}

--local initscripts = {}


local items_dynamic = { 
	basic_bricks = {
		pos = {
			{20, 5}, {22, 5}, {24, 5}, {77, 5}, {79, 5}, {80, 9}, {81, 9}, {82, 9}, {83, 9}, {84, 9}, {85, 9}, {86, 9}, {87, 9}, {91, 9}, {92, 9}, {93, 9}, {100, 5},
			{118, 5}, {121, 9}, {122, 9}, {123, 9}, {128, 9}, {129, 5}, {130, 5}, {131, 9}, {168, 5}, {169, 5}, {171, 5}
		},
		factory = function(p) 
			print ("ccc")
		 	return factory.basic_brick.create { pos = p, sprite="basicbrick" } 
		 end
	},
	coin_bonus_bricks = {
		pos = { {16, 5}, {22, 9}, {23, 5}, {94, 9}, {106,5}, {109, 5}, {112, 5}, {129,9}, {130,9}, {170, 5}},
		factory = function(p) 
			print ("faccmi")
			return factory.bonus_brick.create { pos= p, sprite="bonusbrick", factory = factory.flyingcoin, args = { sprite="flying_coin" } } 
		end
	},
	coin2_bonus_bricks = {
		pos = { {94, 5} },
		factory = function(p) 
			print ("faccmi")
			return factory.bonus_brick.create { pos= p, sprite="bonusbrick2", hitsleft=5, factory = factory.flyingcoin, args = { sprite="flying_coin" } } 
		end
	},	
	mushroom_bonus_bricks = {
		pos = { {21,5}, {78, 5}, {109, 9} },
		factory = function(p) 
			print ("faccmi")
			return factory.bonus_brick.create { pos= p, sprite="bonusbrick", factory = factory.mushroom, args = { sprite="mushroom" } } 
		end
	},
	starman_bonus_bricks = {
		pos = { {101,5} },
		factory = function(p) 
			return factory.bonus_brick.create { pos= p, sprite="bonusbrick2", factory = factory.starman, args = { sprite="starman" } } 
		end
	},
	oneup_hidden_bricks = {
		pos = { {64,6} },
		factory = function(p) 
			print ("faccmi")
			return factory.bonus_brick.create { pos= p, sprite="hiddenbrick", factory = factory.mushroom, args = { sprite="mushroom1up", oneup=true } } 
		end
	},	
	pipe2 = {
		pos = { {28, 2}, {163, 2}, {179, 2} },
		factory = function(p) 
			return factory.tiled.create { pos = p, z=1, width=2, height=2, collide=true, tiledata = {0,4,1,4,0,3,1,3}, img = "smb1.png"} 
		end
	},
	pipe3 = {
		pos = { {38, 2} },
		factory = function(p) 
			return factory.tiled.create { pos = p, width=2, height=3, collide=true, tiledata = {0,4,1,4,0,4,1,4,0,3,1,3}, img = "smb1.png"} 
		end
	},
	pipe4 = {
		pos = { {46, 2}, {57, 2} },
		factory = function(p) 
			return factory.tiled.create { pos = p, width=2, height=4, collide=true, tiledata = {0,4,1,4,0,4,1,4,0,4,1,4,0,3,1,3}, img = "smb1.png"} 
		end
	},
	pickup_coins = {
		pos = { 
			{4,21}, {5,21}, {6,21}, {7,21}, {8,21}, {9,21}, {10,21},
			{4,23}, {5,23}, {6,23}, {7,23}, {8,23}, {9,23}, {10,23},
			{5,25}, {6,25}, {7,25}, {8,25}, {9,25}
		}, 
		factory = function(p) 
			return factory.coin.create { model="pickup_coin", pos = p}
		end
	},
	goombas = {
		pos = { {42, 2}, {50, 2}, {52, 2}},
		factory = function(p) return factory.goomba.create {pos = p, sprite="goomba", flip=true} end
	},
	bighills = {
		pos = {{0, 2}, {48, 2}, {96, 2}, {144, 2}, {192, 2}},
		factory = function(p) return factory.tiled.create_from { pos = p, z=-0.1,template = "big_hill"} end,
	},
	smallhills = {
		pos = {{16, 2}, {64, 2}, {112, 2}, {160, 2}, {208, 2}},
		factory = function(p) return factory.tiled.create_from { pos = p, z=-0.1,template = "small_hill"} end,
	},
	bush1 = {
		pos = {{23, 2}, {71, 2}, {119, 2}, {167, 2}, {215, 2}},
		factory = function(p) return factory.tiled.create_from { pos = p, z=-0.1,template = "bush1"} end,
	},
	bush2 = {
		pos = {{41, 2}, {89, 2}, {137, 2}, {185, 2}},
		factory = function(p) return factory.tiled.create_from { pos = p, z=-0.1,template = "bush2"} end,
	},
	bush3 = {
		pos = {{11, 2}, {59, 2}, {107, 2}, {155, 2}, {203, 2}},
		factory = function(p) return factory.tiled.create_from { pos = p, z=-0.1,template = "bush3"} end,
	},
	cloud1 = {
		pos = {{8, 10}, {19, 11}, {56, 10}, {67, 11}, {104, 10}, {115, 11}, {152, 10}, {163, 11}, {200, 10}, {211, 11}},
		factory = function(p) return factory.tiled.create_from { pos = p, z=-0.1,template = "cloud1"} end,
	},		
	cloud2 = {
		pos = { {36, 11}, {84, 11}, {132, 11}, {180, 11}},
		factory = function(p) return factory.tiled.create_from { pos = p, z=-0.1,template = "cloud2"} end,
	},		
	cloud3 = {
		pos = { {27, 10}, {75, 10}, {123, 10}, {171, 10}, {219, 10}},
		factory = function(p) return factory.tiled.create_from { pos = p, z=-0.1,template = "cloud3"} end,
	},	
}






room = factory.room.create (roomInfo)

room:add_d( {
	factory.rect { pos = {0, 0}, z=1, img = "block1.png", width=69, height=2 },
	factory.rect { pos = {71, 0}, z=1, img = "block1.png", width=15, height=2 },
	factory.rect { pos = {89, 0}, z=1, img = "block1.png", width=64, height=2 },
	factory.rect { pos = {155, 0}, z=1, img = "block1.png", width=69, height=2 },
	factory.warp.create { pos = {4,2}, width = 14, height = 2, func = function() 
		local mario = monkey.getEntity("player")
		mario.state = "warp"
		variables.warpfunc = nil
		local actions = {
			{ type = action.move, args = {tag="player", by = {0, -32}, speed = 50}},
			{ type = action.move, args = {tag="player", to = {32, 400}, imm = true}},
			{ type = action.set_state, args = {tag="player", state="jump"}},
			{ type = action.change_cam_bounds, args = {cam="maincam", x= {0, 256}, y = {256, 512}}}
		}
		local s = script.make(actions)

		monkey.play(s)	
	end },

	factory.rect { pos = {134, 2}, img = "block2.png", width=4, height=1 },
	factory.rect { pos = {135, 3}, img = "block2.png", width=3, height=1 },
	factory.rect { pos = {136, 4}, img = "block2.png", width=2, height=1 },
	factory.rect { pos = {137, 5}, img = "block2.png", width=1, height=1 },
	factory.rect { pos = {140, 5}, img = "block2.png", width=1, height=1 },
	factory.rect { pos = {140, 4}, img = "block2.png", width=2, height=1 },
	factory.rect { pos = {140, 3}, img = "block2.png", width=3, height=1 },
	factory.rect { pos = {140, 2}, img = "block2.png", width=4, height=1 },
	factory.rect { pos = {148, 2}, img = "block2.png", width=5, height=1 },
	factory.rect { pos = {149, 3}, img = "block2.png", width=4, height=1 },
	factory.rect { pos = {150, 4}, img = "block2.png", width=3, height=1 },
	factory.rect { pos = {151, 5}, img = "block2.png", width=2, height=1 },
	factory.rect { pos = {155, 5}, img = "block2.png", width=1, height=1 },
	factory.rect { pos = {155, 4}, img = "block2.png", width=2, height=1 },
	factory.rect { pos = {155, 3}, img = "block2.png", width=3, height=1 },
	factory.rect { pos = {155, 2}, img = "block2.png", width=4, height=1 },
	factory.rect { pos = {181, 2}, img = "block2.png", width=9, height=1 },
	factory.rect { pos = {182, 3}, img = "block2.png", width=8, height=1 },
	factory.rect { pos = {183, 4}, img = "block2.png", width=7, height=1 },
	factory.rect { pos = {184, 5}, img = "block2.png", width=6, height=1 },
	factory.rect { pos = {185, 6}, img = "block2.png", width=5, height=1 },
	factory.rect { pos = {186, 7}, img = "block2.png", width=4, height=1 },
	factory.rect { pos = {187, 8}, img = "block2.png", width=3, height=1 },
	factory.rect { pos = {188, 9}, img = "block2.png", width=2, height=1 },
	factory.rect { pos = {198, 2}, img = "block2.png", width=1, height=1 },

	-- bonus
	factory.rect { pos = {0, 16}, img = "block4.png", width=16, height=2 },
	factory.rect { pos = {0, 18}, img = "brick2.png", width=1, height=11 },
	factory.rect { pos = {4, 18}, img = "brick2.png", width=7, height=3 },
	factory.rect { pos = {4, 28}, img = "brick2.png", width=7, height=1 },
	factory.tiled.create { pos = {13, 18}, z=1,width=4, height=2, collide=false, tiledata = {2,5,3,5,4,5,6,7,2,4,3,4,4,4,6,7}, img = "smb1.png"},
	factory.tiled.create { pos = {15, 20}, width=2, height=9, collide=true, tiledata = {5,5,6,7,5,5,6,7,5,5,6,7,5,5,6,7,5,5,6,7,5,5,6,7,5,5,6,7,5,5,6,7,5,5,6,7}, img = "smb1.png"},
	factory.line { pos = {13, 20}, A = {0,0}, B={32, 0}},
	factory.hotspot.create { pos = {13, 18}, width = 14, height = 2, func = function() 
		local actions = {
			{ type = action.set_state, args = {tag = "player", state = "walk"}},
			{ type = action.set_demo_mode, args = { tag="player", value=true, sync = true, length = 1, events = {
				{ t=0, key = 262, event ="down"}
			}}},
			{ type = action.set_state, args = {tag="player", state="warp"}},
			{ type = action.move, args = {tag="player", to = {164*16,0}, imm = true}},
			{ type = action.change_cam_bounds, args = {cam="maincam", x= {0, roomInfo.worldWidth*engine.tilesize}, y = {0, roomInfo.worldHeight*engine.tilesize}}},
			{ type = action.move, args = {tag="player", by = {0, 64}, speed = 50}},
			{ type = action.set_state, args = {tag = "player", state = "walk"}},

		}
		local s = script.make(actions)
		monkey.play(s)		
	end },
	-- end level stuff
	factory.tiled.create { pos = {198, 3}, width=1, height=10, collide=false, 
		tiledata = {3,2,3,2,3,2,3,2,3,2,3,2,3,2,3,2,3,2,4,2}, img = "smb1.png"},
	factory.simplesprite.create {pos ={197.5, 11}, tag="flag", model = "end_level_flag"},
	factory.tiled.create_from { pos = {202, 2}, template = "castle"},
	factory.hotspot.create { pos = {198.5,3}, width = 2, height = 256, func = function(mario, hotspot)
		local mario = monkey.getEntity("player")
		hotspot:remove()
		mario.state = "slide"
		local delta = math.max(mario.y - 48, 0)
		local actions = {
			{ type = action.noop, ref = 1},
			{ type = action.move, ref = 2, after={1}, args = {tag="player", by = {0, -delta}, speed = 50}},
			{ type = action.move, after={1}, args = {tag="flag", by = {0, -128}, speed = 50}},
			{ type = action.set_state, after= {2}, args = {tag = "player", state = "walk"}},
			{ type = action.set_demo_mode, args = { tag="player", value=true, sync = true, length = 10, events = {
				{ t=0, key = 262, event ="down"}
			}}},
		}
		local s = script.make(actions)
		monkey.play(s)	
	end},
	factory.hotspot.create { pos = {205,2}, width = 2, height = 2, func = function(mario, hotspot)
		mario:setactive(false)
	end},
	
	factory.spawn.create { width=1, height=256, use_once=true, pos={3,2}, func = factory.goomba.create, args = 
		{ pos={23, 	3}, sprite="goomba",flip=false }
	}
})

local items_d = {}
local items = {}

for _, v in pairs(items_dynamic) do
	for _, p in ipairs(v.pos) do
		print ("ciao " .. tostring(p[1]) .. ", " .. tostring(p[2]))
		table.insert(items_d, v.factory(p))
	end
end

room:add_d(items_d)
-- room:add_b({
-- 	{ 
-- 		pos = {0, 0, -5}, 
-- 		components = { 
-- 			{
-- 				type="gfx", 
-- 				draw="solid", 
-- 				shape = { type="rect", width=256, height=256}, 
-- 				color= {92,148,252,255} 
-- 			}
-- 		}
-- 	}
-- })