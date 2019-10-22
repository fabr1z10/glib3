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
			return factory.tiled.create { pos = p, width=2, height=2, collide=true, tiledata = {0,4,1,4,0,3,1,3}, img = "smb1.png"} 
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

}






room = factory.room.create (roomInfo)

room:add_d( {
	factory.rect { pos = {0, 0}, img = "block1.png", width=69, height=2 },
	factory.rect { pos = {71, 0}, img = "block1.png", width=15, height=2 },
	factory.rect { pos = {89, 0}, img = "block1.png", width=64, height=2 },
	factory.rect { pos = {155, 0}, img = "block1.png", width=69, height=2 },

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

	--factory.bonus_brick.create { pos={16*16, 5*16}, sprite="bonusbrick", factory = factory.mushroom, args = { sprite="mushroom" } },
	--factory.bonus_brick.create { pos={16*16, 5*16}, sprite="bonusbrick", factory = factory.flyingcoin, args = { sprite="flying_coin" } },
	--factory.basic_brick.create { pos={20*16, 5*16}, sprite="basicbrick" },
	--factory.basic_brick.create { pos={22*16, 5*16}, sprite="basicbrick" },
	--factory.basic_brick.create { pos={24*16, 5*16}, sprite="basicbrick" },
	
	factory.spawn.create { width=1, height=256, use_once=true, pos={3,2}, func = factory.goomba.create, args = {  pos={12*16,3*16}, sprite="goomba",flip=false }}
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