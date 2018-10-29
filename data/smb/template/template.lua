-- room base
function getBaseRoom(roomInfo) 
	return  {

		engines = {
			{ type = "scheduler"},
			{ 
				type = "collision", 
				size = {roomInfo.collisionSize, roomInfo.collisionSize}, 
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
					{ tag = {1, warpTag}, onenter = mario_warp_in, onleave = mario_warp_out },
					{ tag = {1, warpTouch}, onenter = mario_warptouch},
					{ tag = {1, coinTag}, onenter = mario_coin },
		
						
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
			sprites.score100,
			sprites.pickupcoin
		},
		scene = {
			[1] = {
				tag = "main",
				camera = {
					tag = "maincam",
					type="ortho",
					size = {256, 256},
					bounds = {0, 0, roomInfo.worldWidth*16, roomInfo.worldHeight*16},
					viewport = {0, 0, 256, 256}
				},
				children = {
					[1] = {
						components = {
							{ type="luakey", keys = { 
								{ key = 299, func = restartRoom }}
							},
							
						}
				    },
					-- player
					[2] = items.mario.create { pos = Pos{roomInfo.startPos[1], roomInfo.startPos[2]} },
					[3] = {
						tag = "restofscene",
						children = {
							makeLine { A = {1,0}, B = {1, roomInfo.worldHeight} },
						}		
					}
				}
			}
		},
	}
end

