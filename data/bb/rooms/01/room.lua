local roomInfo = {
	worldWidth = 16,
	worldHeight = 15,
	screen_size = {16, 15},
	collisionSize = 80,
	g = -10,
	name = "1",
	next = "2",
	player_factory = factory.player.create,
	player_args = { pos={6, 10}, id = "nayu", speed =150 },
}

local items_dynamic = { 
	

}

room = factory.stage.create (roomInfo)

local items_d = {
	factory.goomba.create {
		sprite="zenchan", pos ={3, 13},
	},
	factory.tiled.create_from_data { 
		pos={7,5},width=19,height=2,data={
			0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,
			0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,
		},
		collide={18,2,32}
	},
	factory.tiled.create_from_data {
		pos={7,10},width=19,height=2,data={
			0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,
			0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,
		},
		collide={18,2,32}
	},
	factory.tiled.create_from_data {
		pos={7,15},width=19,height=2,data={
			0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,
			0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,
		},
		collide={18,2,32}
	},
	factory.tiled.create_from_data {
		pos={2,5},width=3,height=2,data={
			3,0,1,1,2,1,
			0,0,0,0,2,0
		},
		collide={2,2,32}
	},
	factory.tiled.create_from_data {
		pos={2,10},width=3,height=2,data={
			3,0,1,1,2,1,
			0,0,0,0,2,0
		},
		collide={2,2,32}
	},
	factory.tiled.create_from_data {
		pos={2,15},width=3,height=2,data={
			3,0,1,1,2,1,
			0,0,0,0,2,0
		},
		collide={2,2,32}
	},

	factory.tiled.create_from_data {
		pos={28,5},width=2,height=2,data={
			0,1,1,1,
			0,0,0,0,
		},
		collide={2,2,32}
	},
	factory.tiled.create_from_data {
		pos={28,10},width=2,height=2,data={
			0,1,1,1,
			0,0,0,0,
		},
		collide={2,2,32}
	},
	factory.tiled.create_from_data {
		pos={28,15},width=2,height=2,data={
			0,1,1,1,
			0,0,0,0,
		},
		collide={2,2,32}
	},

	factory.tiled.create_from_data { pos={0,0},width=2,height=26,data={0,0}, collide={2,26,2}},
	factory.tiled.create_from_data { pos={1,0},width=28,height=1,data={0,0}, collide={28,1,2}},
	factory.tiled.create_from_data { pos={30,0},width=2,height=26,data={0,0}, collide={2,26,2}},


}

for _, v in pairs(items_dynamic) do
	for _, p in ipairs(v.pos) do
		table.insert(items_d, v.factory(p))
	end
end

room:add_d(items_d)
