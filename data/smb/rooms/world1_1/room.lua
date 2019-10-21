local roomInfo = {
	worldWidth = 224,
	worldHeight = 16,
	screen_size = {16, 16},
	start_pos = {2, 2},
	collisionSize = 80,
	g = -10
}

--local initscripts = {}

room = factory.room.create (roomInfo)

room:add_d( {
	factory.rect { pos = {0, 0}, img = "block1.png", width=69, height=2 },
	factory.rect { pos = {71, 0}, img = "block1.png", width=15, height=2 },
	factory.rect { pos = {89, 0}, img = "block1.png", width=64, height=2 },
	factory.rect { pos = {155, 0}, img = "block1.png", width=69, height=2 },
	factory.bonus_brick.create { pos={16*16, 5*16}, sprite="bonusbrick", factory = factory.mushroom.create, args = { sprite="mushroom" } },
	factory.spawn.create { width=1, height=256, use_once=true, pos={3,2}, func = factory.goomba.create, args = {  pos={12*16,3*16}, sprite="goomba",flip=false }}
})
