local models = engine.assets.models

local s = {
	goomba_walk_1 = {x=112, y=0, width=16, height=16, anchor = {8, 0}},
	goomba_walk_2 = {x=128, y=0, width=16, height=16, anchor = {8, 0}},
	fx_1_1 = {x=1,y=1,width=15,height=11, anchor={7,6}},
	fx_1_2 = {x=19,y=1,width=29,height=27,anchor={14,13}},
	fx_1_3 = {x=51,y=1,width=35,height=38, anchor={19,18}},
	fx_1_4 = {x=90,y=2,width=46,height=49,anchor={24,22}},
	fx_1_5 = {x=141,y=1,width=48,height=49,anchor={25,23}},
	fx_1_6 = {x=195,y=4,width=36,height=31,anchor={15,14}},
	fx_1_7 = {x=239,y=3,width=34,height=38, anchor={18,17}},
	fx_1_8 = {x=281,y=3,width=37, height=40, anchor={19,16}},
	fx_1_9 = {x=332, y=2, width=35, height=40, anchor={19,15}},
	fx_1_10 = {x=378, y=2, width=35, height=40, anchor={19,14}},
	fx_1_11 = {x=428, y=5, width=35, height=19, anchor={19,14}}	
}

local dt=0.1

models["goomba"] = {
    sheet = "smb1.png",
    type = "boxed_sprite",
    ppu=1,
	animations = {
		{ name = "idle", box = {-8, 0, 8, 16}, frames = {
		 	{duration = dt, quads = {{ id = s.goomba_walk_1 }}, boxes = {{-8,0,8,16}}},
		 	{duration = dt, quads = {{ id = s.goomba_walk_2 }}, boxes = {{-8,0,8,16}}},
		}},
		{ name = "walk", box = {-8, 0, 8, 16}, frames = {
		 	{duration = dt, quads = {{ id = s.goomba_walk_1 }}, boxes = {{-8,0,8,16}}},
		 	{duration = dt, quads = {{ id = s.goomba_walk_2 }}, boxes = {{-8,0,8,16}}},
		}},
		{ name = "jumpup", box = {-8, 0, 8, 16}, frames = {
		 	{duration = dt, quads = {{ id = s.goomba_walk_1 }}, boxes = {{-8,0,8,16}}},
		 	{duration = dt, quads = {{ id = s.goomba_walk_2 }}, boxes = {{-8,0,8,16}}},
		}},
		{ name = "jumpdown", box = {-8, 0, 8, 16}, frames = {
		 	{duration = dt, quads = {{ id = s.goomba_walk_1 }}, boxes = {{-8,0,8,16}}},
		 	{duration = dt, quads = {{ id = s.goomba_walk_2 }}, boxes = {{-8,0,8,16}}},
		}},

		--{ name = "die", frames = { { duration = dt, quads = {{ id = s.mario_die }}}}}
	}
}

models["fx_1"] = {
    sheet = "fx.png",
    type = "sprite",
    ppu=1,
	animations = {
		{ name = "default", frames = {
		 	{duration = dt, quads = {{ id = s.fx_1_1 }}},
		 	{duration = dt, quads = {{ id = s.fx_1_2 }}},
		 	{duration = dt, quads = {{ id = s.fx_1_3 }}},
		 	{duration = dt, quads = {{ id = s.fx_1_4 }}},
		 	{duration = dt, quads = {{ id = s.fx_1_5 }}},
		 	{duration = dt, quads = {{ id = s.fx_1_6 }}},
		 	{duration = dt, quads = {{ id = s.fx_1_7 }}},
		 	{duration = dt, quads = {{ id = s.fx_1_8 }}},
		 	{duration = dt, quads = {{ id = s.fx_1_9 }}},
		 	{duration = dt, quads = {{ id = s.fx_1_10 }}},
		 	{duration = dt, quads = {{ id = s.fx_1_11 }}},
		}},
	}

}

model_factory = {}

model_factory.trapezoid = function(points, depth, y, textop, texside) 
	vertices_top = {}
	hd = depth * 0.5
	for i, p in points do
		table.insert (vertices_top, { p[0], p[1], hd })
		table.insert (vertices_top, { p[0], p[1], -hd })
	end
end

model_factory.box = function (width, height, depth, tex, tsx, tsy, tsz) 
	local texture_size_x = tsx or width
	local texture_size_y = tsy or height
	local texture_size_z = tsz or depth
	local rx = width/texture_size_x
	local ry = height/texture_size_y
	local rz = depth/texture_size_z
	return {
		type = "model3d",
		meshes = {
			{
				texture = tex,
				vertices = {
					-- front
					{ 0, 0, 0,          0, ry,  0, 0, 1}, 
					{ width, 0, 0,      rx, ry,  0, 0, 1},
					{ width, height, 0, rx, 0,  0, 0, 1},
					{ 0, height, 0,     0, 0,  0, 0, 1},
					-- right
					{ width, 0, 0,           0, ry,  1, 0, 0}, 
					{ width, 0, -depth,      rz, ry,  1, 0, 0},
					{ width, height, -depth, rz, 0,  1, 0, 0},
					{ width, height, 0,      0, 0,  1, 0, 0},
					-- back
					{ width, 0, -depth, 0, ry, 0, 0, -1},
					{ 0, 0, -depth, rx, ry, 0, 0, -1},
					{ 0, height, -depth, rx,0, 0, 0, -1 },
					{width, height, -depth, 0, 0, 0, 0, 1},
					-- left
					{0, 0, -depth, 0, ry, -1, 0, 0},
					{0,0,0, rx,ry, -1, 0, 0},
					{0, height, 0, rx,0, -1,0,0},
					{0, height, -depth, 0, 0, -1, 0, 0},
					-- bottom 
					{0,0,0, 0, ry, 0,-1,0},
					{0,0,-depth, 0, 0, 0,-1,0},
					{width, 0, -depth, rz, 0, 0,-1, 0},
					{width, 0, 0, 1, rz, 0, -1, 0},
					--top
					{0, height, 0, 0, rz, 0, 1, 0},
					{width, height, 0, rx,rz,0,1,0},
					{width, height, -depth, rx,0,0,1,0},
					{0,height,-depth,0,0,0,1,0}
				},
				indices = {
					0, 1, 2, 2, 3, 0, 
					4, 5, 6, 6, 7, 4,
					8, 9, 10, 10, 11, 8,
					12, 13, 14, 14, 15, 12,
					16, 17, 18, 18, 19, 16,
					20, 21, 22, 22, 23, 20
				}
			}
		}
	}
end

models["cube"] = model_factory.box (100, 16, 16, "block1.png", 10,10,10)
-- models["goomba"] = {
--     sheet = "smb1.png",
--     type = "sprite",
--     ppu=1,
-- 	animations = {
-- 		{ name = "walk", frames = {
-- 			{ duration = dt, quads = {{ id = s.goomba_walk_1 } }},
-- 			{ duration = dt, quads = {{ id = s.goomba_walk_2 } }},
-- 		}},
-- 		{ name = "jump", frames = {
-- 			{ duration = dt, quads = {{ id = s.goomba_walk_1 } }},
-- 			{ duration = dt, quads = {{ id = s.goomba_walk_2 } }},
-- 		}},
-- 		{ name = "die", frames = { { duration = dt, quads = {{ id = s.goomba_die }}}}}

-- 	}

-- }

-- models["supermario"] = {

	
-- }
-- 		{
-- 			name = "large.nofire.idle",
-- 			frames = {
-- 				{ duration = dt, quads = {{ id = s.mario_idle_big }}}
-- 			}
-- 		},
-- 		{
-- 			name = "large.nofire.walk",
-- 			frames = {
-- 				{ duration = dt, quads = {{ id = s.mario_walk_big_1 } }},
-- 				{ duration = dt, quads = {{ id = s.mario_walk_big_2 } }},
-- 				{ duration = dt, quads = {{ id = s.mario_walk_big_3 } }},
-- 			}
-- 		},
-- 		{
-- 			name = "large.nofire.jump",
-- 			frames = {
-- 				{ duration = dt, quads = {{ id = s.mario_jump_big }}},
-- 			}
-- 		},
-- 		{
-- 			name = "large.nofire.duck",
-- 			frames = {
-- 				{ duration = dt, quads = {{ id = s.mario_duck_big }}},
-- 			}
-- 		},

-- 	}
-- }