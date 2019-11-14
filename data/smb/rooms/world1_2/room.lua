local roomInfo = {
	worldWidth = 192,
	worldHeight = 16,
	screen_size = {16, 16},
	start_pos = {2, 2},
	collisionSize = 80,
	g = -10,
	name = "1-2",
	next = "world1_1"
}

--local initscripts = {}

local brick_pos = {}
for i=1,132 do table.insert(brick_pos, {5+i,28}) end

local items_dynamic = { 
	{
		factory = factory.blocks.platform("block1.png"),
		pos = { {0, 0, 24, 2} }
	},	
	{
		factory = factory.blocks.platform("block5.png"),
		pos = { 
			{17, 18, 1, 1}, {19, 18, 1, 2}, {21, 18, 1, 3}, {23, 18, 1, 4}, {25, 18, 1, 4}, {27, 18, 1, 3}, {31, 18, 1, 3}, {33, 18, 1, 1},
			{133, 18, 5, 1}, {134, 19, 4, 1}, {135, 20, 3, 1}, {136, 21, 2, 1}

		}
	},
	{
		factory = factory.blocks.platform("block4.png"),
		pos = { {0, 16, 80, 2}, {83, 16, 37, 2}, {122, 16, 2, 2}, {126, 16, 12, 2}  }
	},	
	{
		factory = factory.blocks.platform("brick2.png"),
		pos = { {0, 18, 1, 11}, {122, 18, 2, 3}}
	},		
	{
		factory = factory.bg.tiled("castle",-0.5),
		pos = { {0, 2}},
	},		
	{
		factory = factory.bg.tiled("pipe_x", 1),
		pos = { {10, 2}},
	},	
	{
		factory = factory.blocks.basicbrick_dark,
		pos = brick_pos
	},
	{
		factory = factory.blocks.basicbrick_dark,
		pos = { 
			{39, 21}, {39, 22}, {39, 23}, {40, 21}, {41, 21}, {41, 22}, {41, 23}, {42, 23}, {43,23},{44,23}, {44,22}, {44,21}, {45,21}, {46,21}, {46, 22},
			{52, 21}, {52, 22}, {52, 23}, {52, 24}, {52, 25}, {53, 21}, {53, 22}, {53, 23}, {53, 24}, {53, 25}, {54, 19}, {54, 20}, {54, 21}, {54,26}, {54,27},
			{55, 19}, {55, 20}, {55, 21}, {55,26}, {55,27}, {58, 21}, {59, 21}, {60, 21}, {61, 21}, {62, 21}, {63, 21}, {62, 22}, {63, 22}, {62, 23}, {63, 23},
			{62, 24}, {63, 24}, {62, 25}, {63, 25}, {58, 26}, {59, 26}, {60, 26}, {61, 26}, {62, 26}, {63, 26}, {58, 27}, {59, 27}, {60, 27}, {61, 27}, {62, 27}, {63, 27},
			{66, 27}, {67, 27}, {68, 27}, {69, 27}, {66, 26}, {67, 26}, {68, 26}, {69, 26}, {67, 25}, {67, 24}, {67, 23}, {67, 22}, {67, 21}, {68, 21}, {69, 21}, {69, 22},
			{72, 21}, {73, 21}, {72, 22}, {72, 23}, {73, 23}, {72, 24}, {73, 24}, {72, 25}, {73, 25},
			{76, 21}, {77, 21}, {78, 21}, {79, 21},{76, 26}, {77, 26}, {78, 26}, {79, 26},{76, 27}, {77, 27}, {78, 27}, {79, 27},
			{84, 22}, {85, 22}, {86, 22}, {87, 22}, {88, 22}, {89, 22},{84, 23}, {85, 23}, {86, 23}, {87, 23}, {88, 23}, {89, 23}
		

		}
	},
	{
		factory = factory.blocks.pipe_3_green,
		pos = { {103, 18} },
	},
	{
		factory = factory.blocks.pipe_4_green,
		pos = { {109, 18} },
	},
	{
		factory = factory.blocks.pipe_2_green,
		pos = { {115, 18} },
	},
	{
		factory = factory.blocks.brickcoin,
		pos = { {11,21}, {12, 21}, {13, 21}, {14, 21}},	
	},
	{
		factory = factory.blocks.brickcoinmulti_dark,
		pos = { {29, 22} },
	},
	{
		factory = factory.blocks.brickmushroom,
		pos = { {10, 21} },
	},	
	{
		factory = factory.blocks.brickstarman_dark,
		pos = { {46, 23} },
	},
	{
		factory = factory.blocks.pickupcoin,
		pos = { 
			{40, 22}, {41,25}, {42,25}, {43,25}, {44,25}, {45,22}, {58, 22}, {59, 22}, {60, 22}, {61, 22}, {68, 22}
		}
	},
}

room = factory.room.create (roomInfo)

local items_d = {
	factory.hotspot.create { 
		pos = {12, 2},
		width = 2, 
		height = 2, 
		func = function(mario, hotspot)
			local actions = {
				{ type = action.set_demo_mode, args = { tag="player", value=false, sync = true }},
				{ type = action.move, args = {tag="player", to = {2*engine.tilesize, 25*engine.tilesize}, imm = true}},
				{ type = action.change_cam_bounds, args = {cam="maincam", x={0, 192*16}, y = {16*16,32*16}}},
			}
			local s = script.make(actions)
			monkey.play(s)	
		end
	}
}

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

-- cutscene
table.insert (room.initscripts, function()
	local actions = {
		{ type = action.change_cam_bounds, args = {cam="maincam", x= {0,256}, y = {0,256}}},
		{ type = action.set_state, args = {tag = "player", state = "walk"}},
		{ type = action.set_demo_mode, args = { tag="player", value=true, sync = true, length = 10, events = {
			{ t=0, key = 262, event ="down"}
		}}},
	}
	local s = script.make(actions)
	monkey.play(s)	
end)