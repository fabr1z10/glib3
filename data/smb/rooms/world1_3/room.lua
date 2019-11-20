local roomInfo = {
	worldWidth = 176,
	worldHeight = 16,
	screen_size = {16, 16},
	start_pos = {129, 2},
	collisionSize = 80,
	g = -10,
	name = "1-3",
	next = "world1_4"
}

local items_dynamic = { 
	{
		factory = factory.blocks.platform("block1.png"),
		pos = { {0, 0, 16, 2}, {129,0,47,2} }
	},
	{
		factory = factory.blocks.platform("block2.png"),
		pos = { {137, 2, 6, 4}, {139,6,4,2}, {141,8,2,2}, {151,2,1,1} }
	},
	{
		factory = factory.bg.tiled_one { img = "smb1.png", tile ={0, 15}, collide=false },
		pos = { {19, 0, 2, 2}, {24, 0, 6, 5}, {26,6,3,3}, {32,0,1,2}, {35,0,3,6}, {40,0,5,10}, {50,0,2,1}, {59,0,3,1}, {60,2,2,7}, {66,0,3,1}, {71,0,1,5}, {77,0,4,8}, {99,0,2,3},
		 {105,0,6,7}, {114,0,1,1}, {117,0,2,5}, {123,0,2,5}}
	},
	{
		factory = factory.bg.tiled_one { img = "smb1.png", tile ={15, 1}, collide=false },
		pos = { {163, 2, 13, 5}}
	},	
	{
		factory = factory.bg.tiled_one { img = "smb1.png", tile ={14, 3}, collide=false },
		pos = { {163, 7, 13, 1}}
	},		
	{
		factory = factory.blocks.platform1,
		pos = { {18, 2, 4}, {23,5,8}, {25,9,5}, {31,2,3}, {34,6,5}, {39,10,7}, {49,1,4}, {58,1,5}, {59,9,4}, {65,1,5}, {70,5,3}, {76,8,6}, {98,3,4},
			{104,7,8}, {113,1,3}, {116,5,4}, {122,5,4} },	
	},
	{
		factory = factory.npc.koopa,
		pos ={{6,3}}

	},
	{
		factory = factory.bg.tiled("castle",-0.5),
		pos = { {0, 2} },
	},	
	{
		factory = factory.bg.tiled("big_castle",-0.5),
		pos = { {154, 2} },
	},	
	{
		factory = factory.blocks.pickupcoin,
		pos = { 
			{26,10},{27,10},{28,10},{32,3},{36,12},{37,12},{49,8},{50,8},{59,10},{60,10},{61,10},{62,10}
		}
	},	
	{
		factory = factory.blocks.moving_platform_2,
		pos = { {54, 0, 0, 0, 0, 112}, {82,6,0,0,64,0}, {89,5,0,0,64,0}, {127,8,0,0,96,0} }
	},
	{
		factory = factory.blocks.end_level_pole, pos = {{151.5, 3}}
	},
	{
		factory = factory.blocks.touchdown, pos = {{159,2}},
	},	
	{
		factory = factory.bg.tiled("flag",-0.5),
		pos = { {151, 3} },
	},		
}

room = factory.room.create (roomInfo)

local items_d = {
	factory.simplesprite.create {pos ={150.5, 11}, tag="flag", model = "end_level_flag"},
}

for _, v in pairs(items_dynamic) do
	for _, p in ipairs(v.pos) do
		table.insert(items_d, v.factory(p))
	end
end

room:add_d(items_d)

