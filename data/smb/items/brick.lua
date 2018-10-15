items.brick = {}

items.brick.create = function(arg)
	local s = { type = "rect", width = 16, height = 16 }
	local s1 = { type = "rect", width = 14, height = 0.5}
	local b = nextTag()
	local y = arg.pos[2] * 16
	return {
		tag = b,
		pos = {arg.pos[1] * 16, y, 0},
		components = {
			
			{ type="gfx", model=arg.sprite, anim="idle", width = 16, height = 16},	
			{ type="collider", shape=s, tag=10, flag = 2},
			{ type="info", y = y },
		},
		children = {
			{
				pos = { 1, -0.25, 0},
				components = {
					{ type="collider", shape = s1, tag = 20, flag = 4 },
					{ type="gfx", shape = s1, color = {255,0,0,255}}
				}
			}
		}

	}
end

function basicBrickResponse(e1, e2)
	--print ("Brick is at " .. tostring(e2.x) .. ", " .. tostring(e2.y))
	local brick = e2:parent()
	local brickInfo = brick:getinfo()
	local marioinfo = e1:getinfo()
	if (marioinfo.supermario == false) then
		local s = script:new("_brick" .. brick.tag)
		print ("vel = " .. tostring(e1.vy))
		e1.vy = -e1.vy
		s.actions = {
			[1] = { type="movegravity", actor = e2:parent().tag, velocity  = {0, brickSpeed}, g = brickg, ystop = brickInfo.y}
		}
		monkey.play(s)
	else
		brick:remove()

	end
end