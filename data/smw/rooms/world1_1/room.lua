local roomInfo = {
	worldWidth = 224,
	worldHeight = 14,
	startPos = {1, 4},
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
	makePlatformRect {pos = Pos{0,0}, size = Pos{59,2}},
	makePlatformRect {pos = Pos{59,0}, size = Pos{14,6}},
	makePlatformLine {A =Pos{11,5}, B=Pos{14,8}},
	makePlatformLine {A =Pos{51,2}, B=Pos{57,8}},
	makePlatformLine {A =Pos{57,8}, B=Pos{59,6}},
	makePlatformLine {A =Pos{11,5}, B=Pos{14,8}},

	items.spawn.create { pos=Pos{5,0}, items = { { id="banzaibill", args = { pos=Pos{20,2.5}}  }}},
	items.rex.create { pos = Pos{12,3}, dir =-1},
	--makePlatformLine {A =Pos{7,7	}, B=Pos{8,7}},

	--makePlatformLine {A =Pos{7,7}, B=Pos{7.25,7}},
	--makePlatformLine {A =Pos{8,7}, B=Pos{13,5}},
	items.backgroundelement.create { pos=Pos{59,1}, width=1, height=5, tiledata = {0,4,0,3,0,3,0,3,0,2}},
	makeTiledRect { pos = Pos{60,5}, tile ={0,0}, width = 12 , height = 1 },
	items.backgroundelement.create { pos=Pos{72,1}, width=1, height=5, tiledata = {1,4,1,3,1,3,1,3,1,2}},
	tilesets.ramp1(Pos{11,2}, -1),
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



