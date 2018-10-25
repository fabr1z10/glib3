local collisionSize = 80
local startPos = {2, 4}
local g = -10

local initscripts = {}

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
	sprites.koopa
},
scene = {
	{
		tag = "main",
		camera = {
			tag = "maincam",
			type="ortho",
			size = {256, 256},
			bounds = {0, 0, 1024, 256},
			viewport = {0, 0, 256, 256}
		},
		children = {
			{
				components = {
					{ type="luakey", keys = { { key = 299, func = restartRoom }}}
				}
		    },
			-- player
			items.mario.create { pos = Pos{startPos[1], startPos[2]} },
			{
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
					makeRect { pos ={0,0,0}, width = 69, height = 2, gfx="block1" },
					items.spawn.create { pos = Pos{5,0}, func = items.goomba.create, args = { pos ={10,4}, dir = -1} },
					items.bonusbrick.create { pos = Pos{16, 5}, sprite="bonusbrick", hits=1, item = "brickcoin" },					
					--items.brick.create { pos = {16, 5}, sprite="basicbrick" },
				}		
			}
		}
	}
},
}


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



