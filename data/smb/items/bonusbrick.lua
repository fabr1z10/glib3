items.bonusbrick = {}

items.bonusbrick.create = function(arg)
	local s = { type = "rect", width = 16, height = 16 }
	local s1 = { type = "rect", width = 14, height = 0.5, offset = {1, -0.25}}
	local b = nextTag()
	local y = arg.pos[2] * 16
	--print ("CREATE BRICK WITH TAG = " .. b)
	return {
		tag = b,
		pos = {arg.pos[1] * 16, y, 0},
		components = {
			{ type="gfx", model=arg.sprite, anim="idle", width = 16, height = 16},	
			{ type="collider", shape=s, tag=10, flag = 2},
			{ type="info", y = y, hits = arg.hits, item = arg.item}
		},
		children = {
			-- head sensor
			{
				pos = { 0, -0.25, 0},
				components = {
					{ type="collider", shape = s1, tag = 21, flag = 4 },
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
		brickInfo.hits = brickInfo.hits - 1
		local a1 ={ type="noop" }
		local a2 ={ type="noop", after={2}}
		if (brickInfo.hits == 0) then
			a1 = { type="animate", actor=brick.tag, anim="taken" }
			a2 = { type="callfunc", func = curry(generateBonus, brick), after={2} } 
		end
		local s = script:new()
		s.actions = {
			[1] = a1,
			[2] = { type="movegravity", actor = brick.tag, velocity  = {0,brickSpeed}, g = brickg, ystop = brickInfo.y, after={1} },
			[3] = a2
		}
		monkey.play(s)
	end
end