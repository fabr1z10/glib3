items.finalboss = {}

items.finalboss.create = function(args)
	local xstart = args.xstart
	local width = engine.device_size[1]
	local height = engine.device_size[2]
	local hw = width / 2.0
	local y = args.y
	local t = nextTag()	
	local z = args.z or 1
	return {
		tag = t,
		pos = { xstart, y, z },
		components = {
			{ type="collider", tag=bossStartTag, flag=collisionFlags.enemy, mask = collisionFlags.player, shape = {type="rect", width=1, height = height} },
			{ type="info", xmin = xstart - hw, xmax = xstart+hw, ymin = y, ymax = y+height, xboss = args.xboss, yboss = args.yboss, sprite = args.sprite, script = args.script, script_info = args.script_info}
		},
		children = {
			--m--akeLine { A = {-hw, 0}, B = {-hw, height}, active=false },
			--makeLine { A = {xstart+hw, y}, B = {xstart+hw, y+height} },
		}
	} 
end

function boss_script1 (tag, info)
print ("SUSUSUSUSU")
	local delay_up = info.delay_up
	local delay_down = info.delay_down
	local speed_up = info.speed_up
	local speed_down = info.speed_down
	print ("BOSS SCRIPT 1 : delay_up = " .. tostring(delay_up))
	--playerrint (tag)	
	local entity = monkey.getEntity(tag)
	local s = script:new()
	s.actions = {
		-- move up to disappearance
		[1] = { type="delay", sec = delay_down },
		[2] = { type="move", actor=tag, by = {0, 256}, speed = speed_up, after={1}},
		[3] = { type="callfunc", func = function() 
			local p = monkey.getEntity("player")
			entity:setposition(p.x, entity.y, entity.z)
		end, after = {2}},
		[4] = { type="delay", sec = delay_up, after={3}},
		[5] = { type="move", actor = tag, by = {0, -256}, speed=speed_down, after={4}}
	}
	s.loop = 1
	monkey.play(s)
end

function boss_script2 (tag, info)
	--playerrint (tag)	
	local delta = info.delta
	local speed = info.speed
	local angle = info.angle
	local delay_up = info.delay_up
	local delay_down = info.delay_down

	local entity = monkey.getEntity(tag)
	local s = script:new()
	s.actions = {
		-- move up & left to disappearance

		[1] = { type="move", by = {-info.delta, 256}, speed = info.speed, actor=tag, angle = angle, angle_relative = false},
		[2] = { type="flip", actor = tag, after={1}},
		[3] = { type="callfunc", func = function() 
			local p = monkey.getEntity("player")
			entity:setposition(p.x-delta, entity.y, entity.z)
		end, after = {2}},
		[4] = {type="delay", sec = info.delay_up, after={3}},
		[5] = {type="move", by = {info.delta, -256}, speed = info.speed, actor=tag, angle=0, angle_relative=false, after={4}},
		[6] = {type="delay", sec = info.delay_down, after={5}},
		[7] = { type="move", by = {info.delta, 256}, speed = info.speed, actor=tag, angle = -info.angle, angle_relative = false, after={6}},
		[8] = { type="flip", actor = tag, after={7}},
		[9] = { type="callfunc", func = function() 
			local p = monkey.getEntity("player")
			entity:setposition(p.x+info.delta, entity.y, entity.z)
		end, after = {8}},
		[10] = {type="delay", sec = info.delay_up, after={9}},
		[11] = {type="move", by = {-info.delta, -256}, speed = info.speed, actor=tag, angle=0, angle_relative=false, after={10}},
		[12] = {type="delay", sec = info.delay_down, after={11}},
		-- [1] = {type="delay", sec = 2},
		-- [2] = { type="move", actor=tag, by = {0, 256}, speed = 20, after={1}},
		-- [3] = { type="callfunc", func = function() 
		-- 	local p = monkey.getEntity("player")
		-- 	entity:setposition(p.x, entity.y, entity.z)
		-- end, after = {2}},
		-- [4] = {type="delay", sec = 0.2, after={3}},
		-- [5] = { type="move", actor = tag, by = {0, -256}, speed=200, after={4}}
	}
	s.loop = 1
	monkey.play(s)
end

function player_startboss(player, bossEntry)
	print ("YU")
	local info = bossEntry:getinfo()
	local t = nextTag()	
	local m = monkey.getEntity("restofscene")
	print (tostring(info.xmin) .. "," .. tostring(info.xmax))
	monkey.addEntity(makeLine {A={info.xmin+1, info.ymin}, B={info.xmin+1, info.ymax}}, m)
	monkey.addEntity(makeLine {A={info.xmax-1, info.ymin}, B={info.xmax-1, info.ymax}}, m)
	monkey.addEntity(
    {
		tag = t,
		pos = {info.xboss, info.yboss, 1},
		components = {
			{ type="gfx", image="gfx/" .. info.sprite ..".png", offset = {-78, 0}}
		}
	}, m)
	bossEntry:setactive(false)
	local s = script:new()
	s.actions = {
		[1] = { type= "setcambounds", cam="maincam", xmin = info.xmin, xmax =info.xmax, ymin = info.ymin, ymax = info.ymax }
	}
	monkey.play(s)
	print ("CIAOCOMECSSS")
	info.script(t, info.script_info)
	--boss_script1(t)
end