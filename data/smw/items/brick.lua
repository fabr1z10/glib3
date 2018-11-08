items.brick = {}

items.brick.create = function(arg)
	local pos = arg.pos
	local sprite = arg.sprite

	local s = { type = "rect", width = 16, height = 16 }
	local s1 = { type = "rect", width = 14, height = 0.5}
	local b = nextTag()
	local y = pos[2]
	return {
		tag = b,
		pos = {pos[1], pos[2], 0},
		components = {
			
			{ type="gfx", model=sprite, anim="idle", width = 16, height = 16},	
			{ type="collider", shape=s, tag=10, flag = collisionFlags.platform, mask = 0},
			{ type="info", y = y },
		},
		children = {
			{
				pos = { 1, 16-0.25, 0},
				components = {
					{ type="collider", shape = s1, tag = brickTag, flag = collisionFlags.enemy, mask = collisionFlags.player },
					{ type="gfx", shape = s1, color = {255,0,0,255}}
				}
			}
		}

	}
end

function mario_brick(e1, e2)
	
	if (e1.state =="jump" and e1.vy < 0) then
		print ("CIAOOO")
		e1.vy = -e1.vy
		local parent = e2:parent()
		local x = parent.x
		local y = parent.y
		parent:remove()
		--for i = 1,4 do
		CreateItem { id ="brickpiece", args= {pos ={x+16, y+16}, z=1, velocity = {40, 40}} }
		CreateItem { id ="brickpiece", args= {pos ={x+16, y}, z=1, velocity = {30, 20}} }
		CreateItem { id ="brickpiece", args= {pos ={x, y+16}, z=1, velocity = {-40, 40}} }
		CreateItem { id ="brickpiece", args= {pos ={x, y}, z=1, velocity = {-30, 20}} }
		--end
	end
	--print ("Brick is at " .. tostring(e2.x) .. ", " .. tostring(e2.y))
	-- local brick = e2:parent()
	-- local brickInfo = brick:getinfo()
	-- local marioinfo = e1:getinfo()
	-- if (marioinfo.supermario == false) then
	-- 	local s = script:new("_brick" .. brick.tag)
	-- 	print ("vel = " .. tostring(e1.vy))
	-- 	e1.vy = -e1.vy
	-- 	s.actions = {
	-- 		[1] = { type="movegravity", actor = e2:parent().tag, velocity  = {0, brickSpeed}, g = brickg, ystop = brickInfo.y}
	-- 	}
	-- 	monkey.play(s)
	-- else
	-- 	brick:remove()

	--end
end