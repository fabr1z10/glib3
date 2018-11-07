local roomInfo = {
	worldWidth = 224,
	worldHeight = 14,
	startPos = {49,4},
	collisionSize = 80,
	g = -10
}

local initscripts = {}

room = getBaseRoom(roomInfo)
local mainScene = room.scene[1].children[3].children

local sceneItems = {
	items.parallaxbg.create { img="gfx/bg1.png", width=512, height=224, factor = 0.5},
	makeTiledRect { pos = Pos{0,0}, tile ={0,1}, width = 60, height = 1 },
	makeTiledRect { pos = Pos{60,0}, tile ={0,1}, width = 12, height = 5 },
	makeTiledRect { pos = Pos{0,1}, tile ={0,0}, width = 59, height = 1 },
	makeTiledRect { pos = Pos{73,1}, tile ={0,0}, width = 118, height = 1 },
	makeTiledRect { pos = Pos{72,0}, tile ={0,1}, width = 119, height = 1 },
	makeTiledRect { pos = Pos{119,2}, tile ={11,6}, width = 1, height = 4, solid=true},
	makeTiledRect { pos = Pos{122,2}, tile ={11,6}, width = 1, height = 4, solid=true},
	

	makePlatformRect {pos = Pos{0,0}, size = Pos{59,2}},
	makePlatformRect {pos = Pos{59,0}, size = Pos{14,6}},
	makePlatformRect {pos = Pos{73,0}, size = Pos{118,2}},

	makePlatformLine {A =Pos{11,5}, B=Pos{14,8}},
	--makePlatformLine {A =Pos{51,2}, B=Pos{57,8}},
	--makePlatformLine {A =Pos{57,8}, B=Pos{59,6}},
	makePlatformLine {A =Pos{11,5}, B=Pos{14,8}},
	makePlatformLine {A =Pos{75,5}, B=Pos{78,8}},
	makePlatformLine {A =Pos{79,5}, B=Pos{82,8}},
	makePlatformLine {A =Pos{83,5}, B=Pos{86,8}},

	items.spawn.create { pos=Pos{5,0}, items = { { id="banzaibill", args = { pos=Pos{20,2.5}}  }}},
	items.rex.create { pos = Pos{12,3}, dir =-1},
	--makePlatformLine {A =Pos{7,7	}, B=Pos{8,7}},

	--makePlatformLine {A =Pos{7,7}, B=Pos{7.25,7}},
	--makePlatformLine {A =Pos{8,7}, B=Pos{13,5}},
	items.backgroundelement.create { pos=Pos{59,1}, width=1, height=5, tiledata = {0,4,0,3,0,3,0,3,0,2}},
	makeTiledRect { pos = Pos{60,5}, tile ={0,0}, width = 12 , height = 1 },
	items.backgroundelement.create { pos=Pos{72,1}, width=1, height=5, tiledata = {1,4,1,3,1,3,1,3,1,2}},
	tilesets.ramp1(Pos{11, 2}, -1),
	tilesets.ramp1(Pos{75, 2}, -1),
	tilesets.ramp1(Pos{79, 2}, -0.9),
	tilesets.ramp1(Pos{83, 2}, -0.8),
	tilesets.incline_pipe_green(Pos{51,2}, -1),
	tilesets.incline_pipe_green(Pos{124,2}, -1),
	tilesets.pipe_purple(Pos{113, 2}, 0.1, 3, true),
	tilesets.pipe_purple(Pos{120, 2}, 0.1, 2, true),
	tilesets.pipe_grey(Pos{139, 2}, 0.1, 4, true),
	tilesets.pipe_green_small(Pos{131, 2}, 0.1, 3, false),
	tilesets.pipe_green_small(Pos{132, 2}, 0.1, 4, true),

	--items.backgroundelement.create { pos=Pos{11,2}, width=9, height=6, z=-1, tiledata = tilesets.ramp1 },


}

for k, v in ipairs(sceneItems) do
	table.insert(mainScene, v)
end

function room.init()
end

function room.start()

end

function room.afterstartup() 
	for k, v in pairs(initscripts) do
		monkey.play(v)
	end		
end



