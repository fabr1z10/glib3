items.bonusbrick = {}

items.bonusbrick.create = function(arg)
	local s = { type = "rect", width = 16, height = 16 }
	local s1 = { type = "rect", width = 14, height = 0.5, offset = {1, -0.25}}
	local b = nextTag()
	local y = arg.pos[2]
	--print ("CREATE BRICK WITH TAG = " .. b)
	return {
		tag = b,
		pos = {arg.pos[1], arg.pos[2], 0},
		components = {
			{ type="gfx", model=arg.sprite, anim="idle", width = 16, height = 16},	
			{ type="collider", shape=s, tag=10, flag = collisionFlags.platform, mask = 0},
			{ type="info", y = y, hits = arg.hits, item = arg.item}
		},
		children = {
			-- head sensor
			{
				pos = { 0, -0.25, 0},
				components = {
					{ type="collider", shape = s1, tag = 21, flag = collisionFlags.enemy, mask = collisionFlags.player },
					{ type="gfx", shape = s1, color = {255,0,0,255}}
				}
			}
		}
	}
end

function bonusBrickResponse(e1, e2)
	print ("Brick is at " .. tostring(e2.x) .. ", " .. tostring(e2.y))
	local brick = e2:parent()
	local brickInfo = brick:getinfo()
	print ("vel = " .. tostring(e1.vy))
	e1.vy = -e1.vy
	if (brickInfo.hits > 0) then
		--print ("brick speed = " .. tostring(brickInfo.y) .. ", " .. tostring(brickg))
		brickInfo.hits = brickInfo.hits - 1
		local a1 ={ type="noop" }
		local a2 ={ type="noop", after={2}}
		if (brickInfo.hits == 0) then
			a1 = { type="animate", actor=brick.tag, anim="taken" }
		end
		a2 = { type="callfunc", func = curry(generateBonus, brick), after={2} } 


		


		local s = script:new()
		s.actions = {
			[1] = a1,
		 	[2] = { type="movegravity", actor = brick.tag, velocity  = {0, brickSpeed}, g = brickg, ystop = brickInfo.y, after={1} },
			--[2] = {type="noop", after={1}},
		 	[3] = a2
		}
		monkey.play(s)
	end
end