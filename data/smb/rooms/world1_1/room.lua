local collisionSize = 80
local startPos = {2, 4}
local g = -10

local initscripts = {}

local coinBricks = { {16, 5}, {23, 5}, {22, 9}}
local basicBricks = { {20, 5}, {22, 5}, {24, 5}}
local mushroomBricks = {{21,5}}
local pipe2 = { {28,2} }
local pipe3 = { {28,2} }
local pipe4 = { {28,2} }


room = {

engines = {
	{ type = "scheduler"},
	{ 
		type = "collision", 
		size = {collisionSize, collisionSize}, 
		response = {
			{ tag = {1, 20}, onenter = basicBrickResponse },
			{ tag = {1, 21}, onenter = bonusBrickResponse },
			{ tag = {1, mushroomTag}, onenter = mario_mushroom},
			{ tag = {1, mushroom1upTag}, onenter = mario_mushroom1up},
			{ tag = {1, goombaTag}, onenter = mario_goomba},
			{ tag = {1, koopaTag}, onenter = mario_koopa},
			{ tag = {1, flowerTag}, onenter = mario_flower},
			{ tag = {1, starTag}, onenter = mario_star},
			{ tag = {1, invisibleBrickTag}, onenter = mario_invisiblebrick},
			{ tag = {1, movingPlatformTag}, onenter = character_movingplatform},
			{ tag = {1, spawnTag}, onenter = mario_spawn},
				
		}
	}
},
assets = {
	sprites.mario,
	sprites.basicbrick,
	sprites.bonusbrick,
	sprites.invbrick,
	sprites.brickcoin,
	sprites.mushroom,
	sprites.mushroom1up,
	sprites.flower,
	sprites.star,
	sprites.goomba,
	sprites.koopa,
	sprites.score100
},
scene = {
	[1] = {
		tag = "main",
		camera = {
			tag = "maincam",
			type="ortho",
			size = {256, 256},
			bounds = {0, 0, 1024, 256},
			viewport = {0, 0, 256, 256}
		},
		children = {
			[1] = {
				components = {
					{ type="luakey", keys = { { key = 299, func = restartRoom }}}
				}
		    },
			-- player
			[2] = items.mario.create { pos = Pos{startPos[1], startPos[2]} },
			[3] = {
				tag = "restofscene",
				children = {
					-- the background (parallax)
					-- {
					-- 	pos = {0,0,-2},
					-- 	components = {
					-- 		--{ type="gfx", image="gfx/bg1.png", width=512, height=256, rep = {2,1} },
					-- 		{ type="gfx", shape = { type="rect", width = 256, height = 256 }, color = {92, 148, 252, 255}, draw="solid" },
					-- 		{ type="parallax", cam="maincam", factor = 1, width = 512, height = 256}
					-- 	}
					-- },
					
					makeLine { A = {1,0}, B = {1,256} },
					makeRect { pos = Pos{0,0}, width = 69, height = 2, gfx="block1" },
					
					items.spawn.create { pos = Pos{5,0}, func = items.goomba.create, args = { pos ={10,4}, dir = -1} },
										
					--items.brick.create { pos = {20, 5}, sprite="basicbrick" },

				}		
			}
		}
	}
},
}


local mainScene = room.scene[1].children[3].children

for k, v in ipairs(basicBricks) do
	table.insert(mainScene, items.brick.create{ pos=Pos(v), sprite="basicbrick" })
end
for k, v in ipairs(coinBricks) do
	table.insert(mainScene, items.bonusbrick.create { pos = Pos(v), sprite="bonusbrick", hits=1, item = "brickcoin" })
end
for k, v in ipairs(mushroomBricks) do
	table.insert(mainScene, items.bonusbrick.create { pos = Pos(v), sprite="bonusbrick", hits=1, item = "flower" })
end
-- pipes
for k, v in ipairs(pipe2) do table.insert(mainScene, makeRect { pos = Pos(v), width = 2, height = 2, tiledata = {0,4,1,4,0,3,1,3}}) end	
for k, v in ipairs(pipe3) do table.insert(mainScene, makeRect { pos = Pos(v), width = 2, height = 3, tiledata = {0,4,1,4,0,3,1,3,0,3,1,3}}) end	
for k, v in ipairs(pipe4) do table.insert(mainScene, makeRect { pos = Pos(v), width = 2, height = 4, tiledata = {0,4,1,4,0,3,1,3,0,3,1,3,0,3,1,3}}) end	

-- for i = 1,10 do
-- 	print ("pollo")
--      table.insert(room.scene[1].children, { components = 
--      	{
--      		{ type="gfx", shape = { type="line", A={collisionSize*i,0}, B={collisionSize*i, 256}}, color={255, 255, 255, 255}}
--      	}})
--      table.insert(room.scene[1].children, { components =
--      	{
--      		{ type="gfx", shape = { type="line", A={0, collisionSize*i}, B={320, collisionSize*i}}, color={255, 255, 255, 255}}
--      	}})
-- end

-- end room

function room.init()
end

function room.start()

end

function room.afterstartup() 

	for k, v in pairs(initscripts) do
		monkey.play(v)
	end		
end



