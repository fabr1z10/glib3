local roomInfo = {
	worldWidth = 16,
	worldHeight = 15,
	screen_size = {16, 15},
	collisionSize = 80,
	g = -10,
	name = "1",
	next = "2",
	player_factory = factory.player.create,
	player_args = { pos={2, 1}, id = "nayu", speed =150 },	
}

local td = {
	full = {0,0},
	shade_right = {1,0},
	shade_below = {1,1},
	shade_below_start = {0,1},
	shade_right_start = {2,0},
	shade_below_right = {3,0},
	shade_corner = {2,1}
}

local items_dynamic = { 
	

}

room = factory.stage.create (roomInfo)

local items_d = {
	factory.goomba.create {
		sprite="zenchan", pos ={8, 15},
	},
	factory.goomba.create {
		sprite="zenchan", pos ={8, 17},
	},
	factory.tiled.make_platform { pos={7, 5}, z=-1, width=18, left=0, right=0, td=td },
	factory.tiled.make_platform { pos={7, 10}, z=-1, width=18, left=0, right=0, td=td },
	factory.tiled.make_platform { pos={7, 15}, z=-1, width=18, left=0, right=0, td=td },
	factory.tiled.make_platform { pos={2, 5}, z=-1, width=2, left=1, right=0, td=td },
	factory.tiled.make_platform { pos={2, 5}, z=-1, width=2, left=1, right=0, td=td },
	factory.tiled.make_platform { pos={2, 10}, z=-1, width=2, left=1, right=0, td=td },
	factory.tiled.make_platform { pos={2, 15}, z=-1, width=2, left=1, right=0, td=td },
	factory.tiled.make_platform { pos={28, 5}, z=-1, width=2, left=0, right=1, td=td },
	factory.tiled.make_platform { pos={28, 10}, z=-1, width=2, left=0, right=1, td=td },
	factory.tiled.make_platform { pos={28, 15}, z=-1, width=2, left=0, right=1, td=td },
	factory.tiled.make_platform { pos={2,0}, z=-1, width=28, left=1, right=1, td=td},
	factory.tiled.make_platform { pos={2,25}, z=-1, width=28, left=1, right=1, td=td, collide=0},
	factory.tiled.make_wall {pos={0,0}, z=-2,data ={0,0,0,0,0,0,0,0}, right = 0, height = 26, td=td},
	factory.tiled.make_wall {pos={30,0}, z=-2,data ={0,0,0,0,0,0,0,0}, right = 1, height = 26, td=td},


	-- factory.tiled.create_from_data {
	-- 	pos={2,5},width=3,height=2,data={
	-- 		3,0,1,1,2,1,
	-- 		0,0,0,0,2,0
	-- 	},
	-- 	collide_rect={2,2,32,1}
	-- },
	-- factory.tiled.create_from_data {
	-- 	pos={2,10},width=3,height=2,data={
	-- 		3,0,1,1,2,1,
	-- 		0,0,0,0,2,0
	-- 	},
	-- 	collide_rect={2,2,32,1}
	-- },
	-- factory.tiled.create_from_data {
	-- 	pos={2,15},width=3,height=2,data={
	-- 		3,0,1,1,2,1,
	-- 		0,0,0,0,2,0
	-- 	},
	-- 	collide_rect={2,2,32,1}
	-- },

	-- factory.tiled.create_from_data {
	-- 	pos={28,5},width=2,height=2,data={
	-- 		0,1,1,1,
	-- 		0,0,0,0,
	-- 	},
	-- 	collide_rect={2,2,32,1}
	-- },
	-- factory.tiled.create_from_data {
	-- 	pos={28,10},width=2,height=2,data={
	-- 		0,1,1,1,
	-- 		0,0,0,0,
	-- 	},
	-- 	collide_rect={2,2,32,1}
	-- },
	-- factory.tiled.create_from_data {
	-- 	pos={28,15},width=2,height=2,data={
	-- 		0,1,1,1,
	-- 		0,0,0,0,
	-- 	},
	-- 	collide_rect={2,2,32,1}
	-- },

	--factory.tiled.create_from_data { pos={0,0},width=2,height=26,data={0,0}, collide_rect={2,26,2,0}},
	--factory.tiled.create_from_data { pos={1,0},width=29,height=1,data={0,0}, collide_rect={29,1,2,0}},
	--factory.tiled.create_from_data { pos={30,0},width=2,height=26,data={0,0}, collide_rect={2,26,2,0}},


}

for _, v in pairs(items_dynamic) do
	for _, p in ipairs(v.pos) do
		table.insert(items_d, v.factory(p))
	end
end

room:add_d(items_d)
