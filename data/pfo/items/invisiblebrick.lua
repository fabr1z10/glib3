items.invisiblebrick = {}

items.invisiblebrick.create = function(arg)
	local s = { type = "rect", width = 16, height = 16 }
	local s1 = { type = "rect", width = 14, height = 0.5, offset = {1, -0.25}}
	local b = nextTag()
	local z = arg.z or 0
	--print ("CREATE BRICK WITH TAG = " .. b)
	return {
		tag = b,
		pos = {arg.pos[1], arg.pos[2], z},
		components = {
			{ type="gfx", model=arg.sprite, anim="nottaken" },	
			--{ type="collider", shape=s, tag=10, flag = 2},
			{ type="multicollider", tag=10, flag = collisionFlags.platform, mask = 0, initialshape="default", shapes = {
				{ name ="default", type="rect", width=16, height=16 }
			}},
			{ type="info", y = arg.pos[2], item = arg.item},
			{ type="statemachine", initialstate = "nottaken",
				states = {
					{ id = "nottaken", init = { type="animcollider", anim="nottaken" } },
					{ id = "taken", init = { type="animcollider", anim="taken", collider="default" }}
				}
			}
		},
		children = {
			-- head sensors
			{
				pos = { 0, -0.25, 0},
				components = {
					{ type="collider", shape = s1, tag = invisibleBrickTag, flag = collisionFlags.enemy, mask = collisionFlags.player },
					{ type="gfx", shape = s1, color = {255,0,0,255}}
				}
			}
		}
	}
end

function mario_invisiblebrick(mario, sensor)	
	local brick = sensor:parent()
	local brickInfo = brick:getinfo()
	print (brick.state .. tostring(mario.vy))
	if (brick.state=="nottaken" and mario.vy > 0) then	
		mario.vy = -mario.vy
		brick:changestate("taken")
		local s = script:new()
		s.actions = {
			[1] = { type="movegravity", actor = brick.tag, velocity  = {0,brickSpeed}, g = brickg, ystop = brickInfo.y, after={1} },
			[2] = { type="callfunc", func = curry(generateBonus, brick), after={1} } 
		}
		monkey.play(s)
	end
end