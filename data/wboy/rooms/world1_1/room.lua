local roomInfo = {
	worldWidth = 224,
	worldHeight = 32,
	screen_size = {16, 12},
	collisionSize = 80,
	g = -10,
	name = "1-1",
	next = "world1_1",
	player_factory = factory.player.create,
	player_args = { pos={2, 4}, id = "nayu", speed =150 },
}

local items_dynamic = { 
	

}

room = factory.stage.create (roomInfo)

local items_d = {
	factory.tiled.create { pos={0,0}, template = "ciao", repx=10, z = -1,collide=true},
	factory.tiled.create { pos={20,-1}, template = "inclined", repx=10, delta ={0,1},z = -1 },
	factory.platform.create_poly { pos = {20, 0}, points = {0, 0, 0, 4*16, 10*4*16, 14*16, 10*4*16, 0}},
	factory.bgcolor.create { pos = {0, 0}, z=-5, color = {0,182,255,255}, width=256, height=192 },
	factory.bgcolor.create { pos = {0, -48}, z=-4, color = {36,146,85,255}, width=3*256+128, height = 96, px=0.5, py=0.5},
	factory.pickupitem.create  { pos = {8, 5}, model="apple", width=8,height=12,callback = function(p, i) 
		i:remove() 
	end },
	factory.foe1.create { pos = {10,4},sprite="snail", speed=5, acceleration=0.01}
}

for _, v in pairs(items_dynamic) do
	for _, p in ipairs(v.pos) do
		table.insert(items_d, v.factory(p))
	end
end
room:add({
	factory.image.create { pos ={0, 4}, z=-4,img = "bg1.png", repx= 3, parallax = {0.5,0.5} },
	factory.image.create { pos ={48, 4}, z=-4,img = "bg2.png", repx= 1, parallax = {0.5,0.5} },
	factory.platform.create_poly { pos = {20, 0}, points = {0, 0, 0, 4*16, 10*4*16, 14*16, 10*4*16, 0}},

	--factory.platform.create_line { pos ={20, 4}, A={0,0}, B = {10*4*16,10*16}},

})
room:add_d(items_d)
