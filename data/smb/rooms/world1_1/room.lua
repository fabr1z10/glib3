local roomInfo = {
	worldWidth = 224,
	worldHeight = 16,
	screen_size = {16, 16},
	start_pos = {2, 2},
	collisionSize = 80,
	g = -10,
	name = "1-1",
	next = "world1_1"
}

--local initscripts = {}


local items_dynamic = { 
	{
		factory = factory.blocks.platform("block1.png"),
		pos = { {0, 0, 69, 2}, {71, 0, 15, 2}, {89, 0, 64, 2}, {155, 0, 69, 2}}
	},
	{
		factory = factory.blocks.platform("block2.png"),
		pos = { {134, 2, 4, 1}, {135, 3, 3, 1}, {136, 4, 2, 1}, {137, 5, 1, 1} , {140,5,1,1}, {140,4,2,1},
				{140,3,3,1}, {140,2,4,1},{148,2,5,1},{149,3,4,1},{150,4,3,1},{151,5,2,1},{155,5,1,1},{155,4,2,1},
				{155,3,3,1},{155,2,4,1},{181,2,9,1},{182,3,8,1},{183,4,7,1},{184,5,6,1},{185,6,5,1},{186,7,4,1},
				{187,8,3,1},{188,9,2,1},{198,2,1,1}}
	},
	{
		factory = factory.blocks.warp_down { to = {2, 25}, x_bounds = {0,256}, y_bounds={256,512} },
		pos = { {4,2} }
	},
	{
		factory = factory.blocks.warp_up { to = {164, 0}, x_bounds= {0, roomInfo.worldWidth*engine.tilesize}, y_bounds = {0, roomInfo.worldHeight*engine.tilesize}},
		pos = { {13,18} }
	},
	{
		factory = factory.blocks.end_level_pole, pos = {{198.5, 3}}
	},
	{
		factory = factory.blocks.touchdown, pos = {{205,2}},
	},
	{
		factory = factory.blocks.basicbrick,
		pos = {
			{20, 5}, {22, 5}, {24, 5}, {77, 5}, {79, 5}, {80, 9}, {81, 9}, {82, 9}, {83, 9}, {84, 9}, {85, 9}, {86, 9}, {87, 9}, {91, 9}, {92, 9}, {93, 9}, {100, 5},
			{118, 5}, {121, 9}, {122, 9}, {123, 9}, {128, 9}, {129, 5}, {130, 5}, {131, 9}, {168, 5}, {169, 5}, {171, 5}
		},
	},
	{
		factory = factory.blocks.brickcoin,
		pos = { {16, 5}, {22, 9}, {23, 5}, {94, 9}, {106,5}, {109, 5}, {112, 5}, {129,9}, {130,9}, {170, 5}},	
	},
	{
		factory = factory.blocks.brickcoinmulti,
		pos = { {94, 5} },
	},
	{
		factory = factory.blocks.brickmushroom,
		pos = { {21,5}, {78, 5}, {109, 9} },
	},	
	{
		factory = factory.blocks.brickstarman,
		pos = { {101,5} },
	},
	{
		factory = factory.blocks.brickoneuphidden,
		pos = { {64,6} },
	},
	{
		factory = factory.blocks.brickoneuphidden,
		pos = { {64,6} },
	},	
	{
		factory = factory.blocks.pipe_2_green,
		pos = { {28, 2}, {163, 2}, {179, 2} },
	},
	{
		factory = factory.blocks.pipe_3_green,
		pos = { {38, 2} },
	},
	{
		factory = factory.blocks.pipe_4_green,
		pos = { {46, 2}, {57, 2} },
	},
	{
		factory = factory.blocks.pickupcoin,
		pos = { 
			{4,21}, {5,21}, {6,21}, {7,21}, {8,21}, {9,21}, {10,21},
			{4,23}, {5,23}, {6,23}, {7,23}, {8,23}, {9,23}, {10,23},
			{5,25}, {6,25}, {7,25}, {8,25}, {9,25}
		}
	},
	{
		factory = factory.npc.goomba,
		pos = { {42, 2}, {50, 2}, {52, 2}},
	},
	{
		factory = factory.bg.tiled("big_hill"), 
		pos = {{0, 2}, {48, 2}, {96, 2}, {144, 2}, {192, 2}},
	},
	{
		factory = factory.bg.tiled("small_hill"), 
		pos = {{16, 2}, {64, 2}, {112, 2}, {160, 2}, {208, 2}},
	},
	{
		factory = factory.bg.tiled("bush1"),
		pos = {{23, 2}, {71, 2}, {119, 2}, {167, 2}, {215, 2}},
	},
	{
		factory = factory.bg.tiled("bush2"),
		pos = {{41, 2}, {89, 2}, {137, 2}, {185, 2}},
	},
	{
		factory = factory.bg.tiled("bush3"),
		pos = {{11, 2}, {59, 2}, {107, 2}, {155, 2}, {203, 2}},
	},
	{
		factory = factory.bg.tiled("cloud1"),
		pos = {{8, 10}, {19, 11}, {56, 10}, {67, 11}, {104, 10}, {115, 11}, {152, 10}, {163, 11}, {200, 10}, {211, 11}},
	},		
	{
		factory = factory.bg.tiled("cloud2"),
		pos = { {36, 11}, {84, 11}, {132, 11}, {180, 11}},
	},		
	{
		factory = factory.bg.tiled("cloud3"),
		pos = { {27, 10}, {75, 10}, {123, 10}, {171, 10}, {219, 10}},
	},
	{
		factory = factory.bg.tiled("castle",-0.5),
		pos = { {202, 2}},
	},		
}






room = factory.room.create (roomInfo)

room:add_d( {
	--bonus
	factory.rect { pos = {0, 16}, img = "block4.png", width=16, height=2 },
	factory.rect { pos = {0, 18}, img = "brick2.png", width=1, height=11 },
	factory.rect { pos = {4, 18}, img = "brick2.png", width=7, height=3 },
	factory.rect { pos = {4, 28}, img = "brick2.png", width=7, height=1 },
	factory.tiled.create { pos = {13, 18}, z=1,width=4, height=2, collide=false, tiledata = {2,5,3,5,4,5,6,7,2,4,3,4,4,4,6,7}, img = "smb1.png"},
	factory.tiled.create { pos = {15, 20}, width=2, height=9, collide=true, tiledata = {5,5,6,7,5,5,6,7,5,5,6,7,5,5,6,7,5,5,6,7,5,5,6,7,5,5,6,7,5,5,6,7,5,5,6,7}, img = "smb1.png"},
	factory.line { pos = {13, 20}, A = {0,0}, B={32, 0}},

	-- end level stuff
	factory.tiled.create { pos = {198, 3}, width=1, height=10, collide=false, 
		tiledata = {3,2,3,2,3,2,3,2,3,2,3,2,3,2,3,2,3,2,4,2}, img = "smb1.png"},
	factory.simplesprite.create {pos ={197.5, 11}, tag="flag", model = "end_level_flag"},
	--factory.tiled.create_from { pos = {202, 2}, template = "castle"},

	
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
room:add_b({
	{ 
 		tag = "bg",
		pos = {0, 0, -5}, 
		components = { 
			{
				type="gfx", 
				draw="solid", 
				shape = { type="rect", width=256, height=256}, 
				--color= {92,148,252,255} 
				color = {0,0,64,255}
			}
		}
	}
})