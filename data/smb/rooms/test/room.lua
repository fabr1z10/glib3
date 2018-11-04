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

				
		}
	}
},
assets = {
	sprites.mario,
	sprites.basicbrick,
	sprites.bonusbrick,
	sprites.invbrick,
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
			items.mario.create { pos={startPos[1], startPos[2]}},
			{
				tag = "restofscene",
				children = {
					-- the background (parallax)
					{
						pos = {0,0,-2},
						components = {
							--{ type="gfx", image="gfx/bg1.png", width=512, height=256, rep = {2,1} },
							{ type="gfx", shape = { type="rect", width = 256, height = 256 }, color = {92, 148, 252, 255}, draw="solid" },
							{ type="parallax", cam="maincam", factor = 1, width = 512, height = 256}
						}
					},
					
					makeLine { A = {1,0}, B = {1,256} },
					makeRect { pos ={0,0,0}, width = 69, height = 2, gfx="block1" },
					makeRect { pos ={8,2,0}, width = 1, height = 1, gfx="block2" },
					makeRect { pos ={12,2,0}, width = 1, height = 1, gfx="block2" },
					makeRect { pos ={20,2,0}, width = 1, height = 1, gfx="block2" },
					items.brick.create { pos = {6,5}, sprite="basicbrick" },
					-- -- makeBrick { pos ={ 4, 5}, sprite="basicbrick"},
					items.bonusbrick.create { pos = {7,5}, sprite="bonusbrick", hits=1, item = "mushroom" },					
					items.bonusbrick.create { pos = {4,5}, sprite="bonusbrick", hits=1, item = "flower" },					
					items.bonusbrick.create { pos = {3,5}, sprite="bonusbrick", hits=1, item = "mushroom1up" },					
					items.bonusbrick.create { pos = {4,8}, sprite="bonusbrick", hits=1, item = "star" },					
					items.invisiblebrick.create { pos = {5, 8}, sprite="invbrick", hits=1, item="mushroom1up" },
					items.goomba.create { x = 16*10, y = 16*3, z = 0, dir = -1},
					items.koopa.create { x = 16*14, y = 16*3, z = 0, dir = -1},
					{
						pos = {2*16,10*16, -1},
						components = {
							{ type="gfx", img="gfx/smb1.png", width=3, height=2, size=16, tiledata={5,4,6,4,7,4,5,3,6,3,7,3}, sheetsize={16, 16}}
						}
					},
					items.movingplatform.create { pos={10, 5}, width=3, tx=15, ty=5, speed=20, pos2={18, 5}, initscripts = initscripts },
					items.movingplatform.create { pos={10, 6}, width=3, tx=15, ty=5, speed=20, pos2={10, 11}, initscripts = initscripts },

				}		
			}
		}
	}
},
}


for i = 1,10 do
	print ("pollo")
     table.insert(room.scene[1].children, { components = 
     	{
     		{ type="gfx", shape = { type="line", A={collisionSize*i,0}, B={collisionSize*i, 256}}, color={255, 255, 255, 255}}
     	}})
     table.insert(room.scene[1].children, { components =
     	{
     		{ type="gfx", shape = { type="line", A={0, collisionSize*i}, B={320, collisionSize*i}}, color={255, 255, 255, 255}}
     	}})
end

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



