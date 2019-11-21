local roomInfo = {
	worldWidth = 160,
	worldHeight = 16,
	screen_size = {16, 16},
	start_pos = {1, 9},
	collisionSize = 80,
	g = -10,
	name = "1-4",
	next = "world1_1"
}

local items_dynamic = { 
	{
		factory = factory.bg.tiled_one { img = "smb1.png", tile ={0, 13}, collide=true },
		pos = { {0, 0, 3, 8 }, {3, 0, 1, 7}, {4, 0, 1, 6}, {5, 0, 8, 5}, {0,10,24,2}, {0,12,160,1}, {15,0,11,5}, {23,9,1,1}, {29,0,3,5},{35,0,37,6},  {37,9,35,3},
			{72,0,32,5}, {80,11,1,1}, {88,11,1,1}, {97,10,7,2},{104,0,24,2}, {116,2,4,3}, {123,2,5,3}, {123,10,5,2}, {141,0,3,6}, {142,9,2,3}, {144,0,16,2} }
	},
	{
		factory = factory.bg.tiled_one { img = "smb1.png", tile ={2, 13}, collide=false},
		pos = { {13, 0, 2, 2 }, {26,0,3,1},{32,0,3,1},{128,0,13,1}}
	},
	{
		factory = factory.bg.tiled_one { img = "smb1.png", tile ={2, 12}, collide=false },
		pos = { {13, 2, 2, 1 }, {26,1,3,1},{32,1,3,1},{128,1,13,1}}
	},
	{
		factory = factory.bg.tiled_one { img = "smb1.png", tile ={0, 11}, collide=true,z=-0.9},
		pos = { {23,8,1,1}, {30,4,1,1}, {37,8,1,1},{49,8,1,1},{60,8,1,1}, {67,8,1,1}, {76,5,1,1}, {80,10,1,1}, {84,5,1,1}, {88,10,1,1}, {92,5,1,1} }
	},	
	{
		factory = factory.bg.tiled_one { img = "smb1.png", tile ={4, 13}, collide=true},
		pos = { {128,4,13,1}}
	},
	{
		factory = factory.blocks.brickmushroom,
		pos = { {30,8} },
	},	
	{
		factory = factory.npc.rotatingfire,
		pos = { {30.5,4.5,6}, {49.5,8.5,6}, {60.5,8.5,6}, {67.5,8.5,6}, {76.5,5.5,6}, {84.5,5.5,6}, {88.5, 10.5, 6} }
	}

}

room = factory.room.create (roomInfo)

local items_d = {
	--factory.rotatingfire.create { pos = {5,5}, n=6, model="enemy_fire"}
}

for _, v in pairs(items_dynamic) do
	for _, p in ipairs(v.pos) do
		table.insert(items_d, v.factory(p))
	end
end

room:add_d(items_d)

