local roomInfo = {
	worldWidth = 320,
	worldHeight = 14,
	startPos = {2,4},
	collisionSize = 80,
	g = -10
}

local initscripts = {}

areas = {
	main1 = {
		range = {0, 0, roomInfo.worldWidth*16, roomInfo.worldHeight*16},
		startPos = Pos{175, 4},
		background = { "bg_main" }
	},
	cave = {
		range = {0, 20*16, 512, 34*16},
		startPos = Pos{2, 34},
		background = { "bg_cave" }
	}
}



room = getBaseRoom(roomInfo)
local mainScene = room.scene[1].children[3].children

local sceneItems = {
	-- cave
	 items.parallaxbg.create { tag = "bg_cave", img="gfx/bg2.png", pos=Pos{0, 0}, width=384, height=224, factor = 0.5},
	makeTiledRect { pos = Pos{1,21}, tile ={3, 7}, width = 30, height = 1},
	makeTiledRect { pos = Pos{0,20}, tile ={3, 8}, width = 32, height = 1},
	makeTiledRect { pos = Pos{0,21}, tile ={2, 7}, width = 1, height = 1},
	makeTiledRect { pos = Pos{31,21}, tile ={4, 7}, width = 1, height = 1},
	makeTiledRect { pos = Pos{31,32}, tile ={2, 8}, width = 1, height = 1},
	makeTiledRect { pos = Pos{0,22}, tile ={2, 6}, width = 1, height = 12, solid = true },
	makeTiledRect { pos = Pos{31,22}, tile ={4, 6}, width = 1, height = 10, solid = true },
	makeTiledRect { pos = Pos{4,32}, tile ={1, 9}, width = 27, height = 1 },
	makeTiledRect { pos = Pos{4,33}, tile ={1, 8}, width = 28, height = 1 },
	makeTiledRect { pos = Pos{3,32}, tile ={0, 9}, width = 1, height = 1 },
	makeTiledRect { pos = Pos{3,33}, tile ={0, 8}, width = 1, height = 1 },
	makePlatformRect {pos = Pos{0,20}, size = Pos{32,2}},
	makeTiledRect { pos = Pos{20, 22}, tile ={11,6}, width = 1, height = 4, solid=true},
	makeTiledRect { pos = Pos{24, 22}, tile ={11,6}, width = 1, height = 4, solid=true},
	items.brick.create { pos = Pos{21, 25}, sprite="brick" },
	items.brick.create { pos = Pos{22, 25}, sprite="brick" },
	items.brick.create { pos = Pos{23, 25}, sprite="brick" },
	tilesets.pipe_orange_down (Pos{1, 25}, 0.1, 9, false),
	tilesets.pipe_horizontal_green (Pos{28, 22}, 0.1, 3, true),
	makePlatformLine {A =Pos{3,25}, B=Pos{3,32}},


	items.parallaxbg.create { tag="bg_main", img="gfx/bg1.png", width=512, height=224, factor = 0.5},
	makeTiledRect { pos = Pos{0,0}, tile ={0,1}, width = 60, height = 1 },
	makeTiledRect { pos = Pos{60,0}, tile ={0,1}, width = 12, height = 5 },
	makeTiledRect { pos = Pos{0,1}, tile ={0,0}, width = 59, height = 1 },
	makeTiledRect { pos = Pos{73,1}, tile ={0,0}, width = 119, height = 1 },
	makeTiledRect { pos = Pos{72,0}, tile ={0,1}, width = 120, height = 1 },
	makeTiledRect { pos = Pos{119,2}, tile ={11,6}, width = 1, height = 4, solid=true},
	makeTiledRect { pos = Pos{122,2}, tile ={11,6}, width = 1, height = 4, solid=true},
	tilesets.connect_down(Pos{192,0}, 2),
	makeTiledRect { pos = Pos{193,0}, tile ={0,0}, width = 5, height = 1 },
	tilesets.connect_up(Pos{198,0}, 2),
	makeTiledRect { pos = Pos{199,1}, tile ={0,0}, width = 13, height = 1 },
	makeTiledRect { pos = Pos{199,0}, tile ={0,1}, width = 13, height = 1 },
	tilesets.connect_down(Pos{212,0}, 2, 0),
	tilesets.connect_up(Pos{215,0}, 2, 0),
	makeTiledRect { pos = Pos{216,1}, tile ={0,0}, width = 2, height = 1 },
	makeTiledRect { pos = Pos{216,0}, tile ={0,1}, width = 2, height = 1 },
	tilesets.connect_down(Pos{218,0}, 2),
	makeTiledRect { pos = Pos{219,0}, tile ={0,0}, width = 4, height = 1 },
	tilesets.connect_up(Pos{223,0}, 2),
	makeTiledRect { pos = Pos{224,1}, tile ={0,0}, width = 3, height = 1 },
	makeTiledRect { pos = Pos{224,0}, tile ={0,1}, width = 3, height = 1 },
	tilesets.connect_down(Pos{227,0}, 2, 0),
	tilesets.connect_up(Pos{230,0}, 2, 0),
	--makeTiledRect { pos = Pos{224,1}, tile ={0,0}, width = 3, height = 1 },
	--makeTiledRect { pos = Pos{224,0}, tile ={0,1}, width = 3, height = 1 },


	makePlatformRect {pos = Pos{0,0}, size = Pos{59,2}},
	makePlatformRect {pos = Pos{59,0}, size = Pos{14,6}},
	makePlatformRect {pos = Pos{73,0}, size = Pos{120,2}},
	makePlatformRect {pos = Pos{193,0}, size = Pos{5,1}},
	makePlatformRect {pos = Pos{198,0}, size = Pos{15,2}},
	makePlatformRect {pos = Pos{215,0}, size = Pos{4,2}},
	makePlatformRect {pos = Pos{219,0}, size = Pos{4,1}},
	makePlatformRect {pos = Pos{223,0}, size = Pos{5,2}},
	makePlatformRect {pos = Pos{230,0}, size = Pos{56,2}},
	makePlatformRect {pos = Pos{286,0}, size = Pos{6,5}},
	makePlatformRect {pos = Pos{292,0}, size = Pos{28,2}},


	makePlatformLine {A =Pos{11,5}, B=Pos{14,8}},
	makePlatformLine {A =Pos{51,2}, B=Pos{57,8}},
	makePlatformLine {A =Pos{57,8}, B=Pos{59,6}},
	makePlatformLine {A =Pos{11,5}, B=Pos{14,8}},
	makePlatformLine {A =Pos{75,5}, B=Pos{78,8}},
	makePlatformLine {A =Pos{79,5}, B=Pos{82,8}},
	makePlatformLine {A =Pos{83,5}, B=Pos{86,8}},

	items.spawn.create { pos=Pos{5,0}, items = { { id="banzaibill", args = { pos=Pos{20,2.5}}  }}},
	--items.rex.create { pos = Pos{12,3}, dir =-1},
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
	items.brick.create { pos = Pos{120, 5}, sprite="brick" },
	items.brick.create { pos = Pos{121, 5}, sprite="brick" },
	items.warp.create { pos = Pos{121, 4}, width=8, height= 1, ctag = warpTag, func = curry(pipeDown, {area = "cave"}) },
	--items.backgroundelement.create { pos=Pos{11,2}, width=9, height=6, z=-1, tiledata = tilesets.ramp1 },
	items.midwaygate.create { pos = Pos{150, 2} },
	items.infobrick.create { pos = Pos{162, 5}, msg = strings[1] },
	items.infobrick.create { pos = Pos{207, 4}, msg = strings[2] },
	items.rex.create { pos = Pos{168,3}, dir =-1},
	tilesets.platform1 (Pos{174, 2}, -0.2, 5, 6),
	tilesets.platform1 (Pos{177, 2}, -0.1, 4, 3),
	tilesets.platform2 (Pos{177,2}, -0.3)
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
	
	monkey.getEntity("bg_cave"):setactive(false)
	print ("SWIUTCHING to main1")
	switchToArea("main1")
end



