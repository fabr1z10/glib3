items.infobrick = {}

items.infobrick.create = function(arg)
    local pos = arg.pos
	local s = { type = "rect", width = 16, height = 16 }
	local s1 = { type = "rect", width = 14, height = 0.5}
	local b = nextTag()
	
	return {
		tag = b,
		pos = {pos[1], pos[2], 0},
		components = {
			
			{ type="gfx", model="infobrick", anim="idle", width = 16, height = 16},	
			{ type="collider", shape=s, tag=10, flag = collisionFlags.platform, mask = 0},
			{ type="info", y = pos[2] },
		},
		children = {
			{
				pos = { 1, -0.25, 0},
				components = {
					{ type="collider", shape = s1, tag = infobrickTag, flag = collisionFlags.enemy, mask = collisionFlags.player },
					{ type="gfx", shape = s1, color = {255,0,0,255}}
				}
			}
		}

	}
end

function mario_infobrick(e1, e2)
	--print ("Brick is at " .. tostring(e2.x) .. ", " .. tostring(e2.y))
	local brick = e2:parent()
	local brickInfo = brick:getinfo()
	-- local marioinfo = e1:getinfo()
	-- if (marioinfo.supermario == false) then
	local s = script:new("_brick" .. brick.tag)
	-- 	print ("vel = " .. tostring(e1.vy))
	e1.vy = -e1.vy
	s.actions = {
		[1] = { type="movegravity", actor = brick.tag, velocity  = {0, brickSpeed}, g = brickg, ystop = brickInfo.y},
		[2] = { type ="callfunc", after={1}, func = function()
			local ros = monkey.getEntity("restofscene")
			ros:enableupdate(false)
			e1:enableupdate(false)
			local diag = monkey.getEntity("diag")
			monkey.addEntity ( { tag ="poa", active=false, pos = {128, 176, 1}, components = { {type="text", align="top", maxwidth = 160, id="ciao bello lameo donte ciao sono bello e tu come ti chiami pazzerello con ombrello sono sempre cont e", font="diag"} }}, diag)
			local poa = monkey.getEntity("poa")
			local ti = poa:gettextinfo()
			local center = { 128, 176-ti.height*0.5}
			ti.width = ti.width * 1.1
			ti.height = ti.height * 1.1
			
			monkey.addEntity ( { 
				tag = "advice_bg",
				pos = {center[1], center[2], 0.9}, 
				scale = 0.5,
				components = { 
					{type="gfx", shape={type="rect", width = ti.width, height = ti.height, offset = {-ti.width*0.5, -ti.height*0.5}}, color = {0,0,0,255}, draw ="solid"}
				}
			}, diag)
			local s1 = script:new()
			s1.actions = {
				[1] = { type="scale", duration = 0.5, scale = 1.0, actor = "advice_bg" },
				[2] = { type="callfunc", after={1}, func = function() poa:setactive(true) end }
			}
			monkey.play(s1)
			print ("FOLLE === " .. tostring(ti.width) .. ", ".. tostring(ti.height))
		end }
	}
	monkey.play(s)
	-- else
	-- 	brick:remove()

	-- end
end