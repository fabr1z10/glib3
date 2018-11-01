local roomInfo = {
	worldWidth = 177,
	worldHeight = 16,
	startPos = {2.5, 2},
	collisionSize = 80,
	g = -10
}

local initscripts = {}

room = getBaseRoom(roomInfo)
local mainScene = room.scene[1].children[3].children

local basicBricks = { {39, 25}, {39, 26}, {39, 27}, {40,25}, {41,25}, {41,26}, {41,27}, {42,27}, {43,27}, {44,27}, {44,26}, {44,25}, {45,25}, {46,25}, {46,26},
	{52, 25}, {53, 25}, {54,25}, {55,25},{54,24},{55,24},{54,23},{55,23}, {52,26},{53,26},{52,27},{53,27}, {52,28},{53,28},{52,29}, {53,29}, {54,30}, {55,30}, {54,31}, {55,31},
	{58, 25}, {59, 25}, {60, 25}, {61,25}, {62,25}, {63,25}, {62,26},{63,26},{62,27},{63,27}, {62,28}, {63,28}, {62,29},{63,29},
	{58, 30}, {59, 30}, {60, 30}, {61,30}, {62,30}, {63,30}, {58, 31}, {59, 31}, {60, 31}, {61,31}, {62,31}, {63,31},
	{66, 31}, {67, 31}, {68, 31}, {69, 31}, {66,30}, {67,30}, {68,30}, {69,30}, {67,29}, {67,28}, {67,27}, {67, 26}, {67, 25}, {68,25}, {69, 25},
	{72, 25}, {73, 25}, {72, 26}, {72, 27}, {73, 27}, {72,28}, {73,28}, {72,29}, {73,29},
	{76, 25}, {77,25}, {78,25}, {79, 25}, {76, 30}, {77,30}, {78,30}, {79,30}, {76,31}, {77,31}, {78,31}, {79,31},
	{84, 26}, {85, 26}, {86, 26}, {87, 26}, {88, 26}, {89, 26}, {84, 27}, {85, 27}, {86, 27}, {87, 27}, {88, 27}, {89, 27}  }
for x = 1,83 do table.insert(basicBricks, {5+x, 32}) end
for x = 1,48 do table.insert(basicBricks, {89+x, 32}) end

local mushroomBricks = {{10,25}}
local coinBricks = { {11, 25}, {12, 25}, {13, 25}, {14, 25} }
local coins = { {40,26}, {41,29}, {42,29}, {43,29}, {44,29}, {45,26}, {58, 26}, {59, 26}, {60, 26}, {61, 26}, {68, 26}, {84, 29}, {85, 29}, {86, 29}, {87, 29}, {88, 29}, {89, 29} }
local pipe2 = { {115, 22} }
local pipe3 = { {103, 22} }
local pipe4 = { {109, 22} }

local sceneItems = {
	makeRect { pos = Pos{0,0}, width = 24, height = 2, gfx="block1" },
	items.backgroundelement.castle { pos = Pos{0, 2}},
	items.backgroundelement.pipe2ways { pos = Pos{10, 2}},
	makeRect { pos = Pos{0, 20}, width = 80, height = 2, gfx="block4" },
	makeRect { pos = Pos{83, 20}, width = 37, height = 2, gfx="block4" },
	makeRect { pos = Pos{122, 20}, width = 2, height = 2, gfx="block4" },
	makeRect { pos = Pos{126, 20}, width = 12, height = 2, gfx="block4" },
	makeRect { pos = Pos{145, 20}, width = 8, height = 2, gfx="block4" },
	makeRect { pos = Pos{160, 20}, width = 17, height = 2, gfx="block4" },
	makeRect { pos = Pos{0, 22}, width = 1, height = 11, gfx="brick2" },
	makeRect { pos = Pos{17, 22}, width = 1, height = 1, gfx="block5" },
	makeRect { pos = Pos{19, 22}, width = 1, height = 2, gfx="block5" },
	makeRect { pos = Pos{21, 22}, width = 1, height = 3, gfx="block5" },
	makeRect { pos = Pos{23, 22}, width = 1, height = 4, gfx="block5" },
	makeRect { pos = Pos{25, 22}, width = 1, height = 4, gfx="block5" },
	makeRect { pos = Pos{27, 22}, width = 1, height = 3, gfx="block5" },
	items.bonusbrick.create { pos = Pos{29, 26}, sprite="basicbrickdark", hits=5, item = "brickcoin" },
	items.bonusbrick.create { pos = Pos{73, 26}, sprite="basicbrickdark", hits=5, item = "brickcoin" },
	makeRect { pos = Pos{31, 22}, width = 1, height = 3, gfx="block5" },
	makeRect { pos = Pos{33, 22}, width = 1, height = 2, gfx="block5" },
	items.bonusbrick.create { pos = Pos{46, 27}, sprite="basicbrickdark", hits=1, item = "star" },			
	items.bonusbrick.create { pos = Pos{69, 26}, sprite="basicbrickdark", hits=1, item = "star" },	
	makeRect { pos = Pos{122, 22}, width = 2, height = 3, gfx="brick2" },
	makeRect { pos = Pos{132, 22}, width = 5, height = 1, gfx="block5" },
	makeRect { pos = Pos{133, 23}, width = 4, height = 1, gfx="block5" },
	makeRect { pos = Pos{134, 24}, width = 3, height = 1, gfx="block5" },
	makeRect { pos = Pos{135, 25}, width = 2, height = 1, gfx="block5" },
	items.plant.create { pos = Pos{104, 25}, z = -0.5, initscripts = initscripts },
	items.plant.create { pos = Pos{110, 26}, z = -0.5, initscripts = initscripts },
	items.plant.create { pos = Pos{116, 24}, z = -0.5, initscripts = initscripts }
}

for k, v in ipairs(sceneItems) do
	table.insert(mainScene, v)
end

for k, v in ipairs(basicBricks) do
	table.insert(mainScene, items.brick.create{ pos=Pos(v), sprite="basicbrickdark" })
end
for k, v in ipairs(mushroomBricks) do
	table.insert(mainScene, items.bonusbrick.create { pos = Pos(v), sprite="bonusbrick", hits=1, item = "flower" })
end
for k, v in ipairs(coinBricks) do
	table.insert(mainScene, items.bonusbrick.create { pos = Pos(v), sprite="bonusbrick", hits=1, item = "brickcoin" })
end
for k, v in ipairs(coins) do
	table.insert(mainScene, items.coin.create { pos = Pos(v) })
end
for k, v in ipairs(pipe2) do table.insert(mainScene, makeRect { pos = Pos(v), z = 0.5, width = 2, height = 2, tiledata = {0,4,1,4,0,3,1,3}}) end	
for k, v in ipairs(pipe3) do table.insert(mainScene, makeRect { pos = Pos(v), z = 0.5, width = 2, height = 3, tiledata = {0,4,1,4,0,4,1,4,0,3,1,3}}) end	
for k, v in ipairs(pipe4) do table.insert(mainScene, makeRect { pos = Pos(v), z = 0.5, width = 2, height = 4, tiledata = {0,4,1,4,0,4,1,4,0,4,1,4,0,3,1,3}}) end	

function room.init()
end

function room.start()

end

function room.afterstartup() 
	for k, v in pairs(initscripts) do
		monkey.play(v)
	end		

	local s = script:new()
	s.actions = {
		[1] = { type="setcambounds", cam ="maincam", xmin=0, xmax = 256, ymin = 0, ymax = 256},
		[2] = { type="changestate", actor="player", state="nophys", after={1}},
		[3] = { type="animate", actor ="player", anim="walk", flipx = false, after={2}},
		[4] = { type="move", by={128, 0}, speed = 250, actor = "player", after={3}},		
		[5] = { type="setcambounds", cam ="maincam", xmin=0, xmax = 16 * roomInfo.worldWidth, ymin = 320, ymax = 320 + 16 * roomInfo.worldHeight, after={4}},
		[6] = { type="move", to=Pos{100, 30}, immediate=true, actor="player", after={5}},
		[7] = { type="changestate", actor="player", state="idle", after={6}},		
	}
	monkey.play(s)
end






