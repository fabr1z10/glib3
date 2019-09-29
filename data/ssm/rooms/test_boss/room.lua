local roomInfo = {
	worldWidth = 224,
	worldHeight = 16,
	startPos = {2, 4},
	collisionSize = 80,
	g = -10
}

local initscripts = {}

room = getBaseRoom(roomInfo)
local mainScene = room.scene[1].children[3].children

-- local coinBricks = { {16, 5}, {23, 5}, {22, 9}, {94,9}, {106,5}, {109,5}, {112,5}, {129,9}, {130,9}, {170,5} }
-- local basicBricks = { {20, 5}, {22, 5}, {24, 5}, {77, 5}, {79,5}, {80,9}, {81,9},{82,9},{83,9},{84,9},{85,9},{86,9},{87,9}, {91,9},{92,9},{93,9}, {100,5}, {118,5}, {121,9}, {122,9}, {123,9},
-- 	{128, 9}, {129, 5}, {130,5}, {131, 9}, {168, 5}, {169, 5}, {171,5} }
-- local mushroomBricks = {{21,5}, {78,5}, {109,9}}
-- local pipe2 = { {28,2}, {163, 2}, {179, 2} }
-- local pipe3 = { {38,2} }
-- local pipe4 = { {46,2}, {57, 2} }
-- local coins = { {4, 25}, {5,25}, {6,25}, {7,25}, {8,25}, {9,25}, {10,25}, {4, 27}, {5,27}, {6,27}, {7,27}, {8,27}, {9,27}, {10,27}, {5,29},
-- {6,29}, {7,29}, {8,29}, {9,29}}

local sceneItems = {
	makeRect { pos = Pos{0,0}, width = 69, height = 2, gfx="block1" },
	--items.finalboss.create { xstart = 16*16, y = 0, xboss = 26*16, yboss = 32, sprite="xxx1", script = boss_script1, script_info = { delay_down = 2, delay_up =0.5, speed_up = 100, speed_down = 500} }
	items.finalboss.create { xstart = 16*16, y = 0, xboss = 26*16, yboss = 32, sprite="xxx1", script = boss_script2, script_info = { delay_down = 2, delay_up =0.5, speed = 150, angle = 30, delta = 150} }
	-- {
	-- 	tag = "shoe",
	-- 	pos = Pos{10, 2, 1},
	-- 	components = {
	-- 		{ type="gfx", image="gfx/xxx1.png", offset = {-78, 0}}
	-- 	}
	-- }

}

for k, v in ipairs(sceneItems) do
	table.insert(mainScene, v)
end
-- for k, v in ipairs(basicBricks) do
-- 	table.insert(mainScene, items.brick.create{ pos=Pos(v), sprite="basicbrick" })
-- end
-- for k, v in ipairs(coinBricks) do
-- 	table.insert(mainScene, items.bonusbrick.create { pos = Pos(v), sprite="bonusbrick", hits=1, item = "brickcoin" })
-- end
-- for k, v in ipairs(mushroomBricks) do
-- 	table.insert(mainScene, items.bonusbrick.create { pos = Pos(v), sprite="bonusbrick", hits=1, item = "flower" })
-- end
-- -- pipes
-- for k, v in ipairs(pipe2) do table.insert(mainScene, makeRect { pos = Pos(v), z = 0.5, width = 2, height = 2, tiledata = {0,4,1,4,0,3,1,3}}) end	
-- for k, v in ipairs(pipe3) do table.insert(mainScene, makeRect { pos = Pos(v), z = 0.5, width = 2, height = 3, tiledata = {0,4,1,4,0,4,1,4,0,3,1,3}}) end	
-- for k, v in ipairs(pipe4) do table.insert(mainScene, makeRect { pos = Pos(v), z = 0.5, width = 2, height = 4, tiledata = {0,4,1,4,0,4,1,4,0,4,1,4,0,3,1,3}}) end	
-- for k, v in ipairs(coins) do
-- 	table.insert(mainScene, items.coin.create { pos = Pos(v) })
-- end

function room.init()
end

function room.start()

end

function room.afterstartup() 
	for k, v in pairs(initscripts) do
		monkey.play(v)
	end		
	-- local s = script:new()
	-- s.actions = {
	-- 	[1] = { type="move", to = {50, 128}, speed = 150, actor="shoe", angle = 30, angle_relative = false},
	-- 	[2] = { type="flip", horizontal=true, actor="shoe", after={1}},
	-- 	[3] = { type="move", to = {160, 32}, speed= 300, actor="shoe",after={2}, angle = 0, angle_relative=false},
	-- 	[4] = { type="collisioncheck", actor="shoe", offset={114-78,0}, shape = {type="rect", width=15, height=4}, mask=collisionFlags.player, func = function() 
	-- 		local mario = monkey.getEntity("player")
	-- 		mario_is_hit(mario)
	-- 	end, after = {3}},
	-- 	[5] = { type="delay", sec=1, after={4}},
	-- 	[6] = { type="move", to = {50, 128}, speed = 150, actor="shoe", angle = 30, angle_relative = false, after= {5}},
	-- 	[7] = { type="flip", horizontal=false, actor="shoe", after={6}},
	-- 	[8] = { type="move", to = {160, 32}, speed= 300, actor="shoe",after={7}, angle = 0, angle_relative=false},
	-- 	[9] = { type="collisioncheck", actor="shoe", offset={114-78,0}, shape = {type="rect", width=15, height=4}, mask=collisionFlags.player, func = function() 
	-- 		local mario = monkey.getEntity("player")
	-- 		mario_is_hit(mario)
	-- 	end, after = {8}},
	-- 	[10] = { type="delay", sec=1, after={9}},
	-- }
	-- s.loop =1
	-- monkey.play(s)
end



