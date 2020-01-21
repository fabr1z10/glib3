action = {}

action.log = function(args) 
	glib.assert (args.message, "message")
	return { type="callfunc", func = function() print (args.message) end }
end

action.change_room = function (args) 	
	glib.assert (args.room, "room")
	return { type="gotoroom", room = args.room }
end

action.restart_room = function (args) 
	return { type="gotoroom", room = engine.state.room }
end

action.restart_game = function (args) 
	return { type="gotoroom", room = engine.start_room }
end

action.noop = function(args) 
	return { type="noop" }	
end

action.delay = function (args) 
	glib.assert (args.sec, "sec")
	return { type="delay", sec = args.sec }
end

action.random_delay = function (args) 
	glib.assert (args.min, "min")
	glib.assert (args.max, "max")

	return { type="delay_dynamic", func = function() return args.min + math.random()*(args.max - args.min) end }
end



action.runscript = function(args) 
	glib.assert (args.func, "func")
	return { 
		type="callfunc", 
		func = function() 
			local actions = args.func()
			if (actions ~= nil) then
				local s = script.make(actions)
				monkey.play(s)		
			end
		end
	}
end

-- move the given object, identified wither with tag or id, 
-- you can provide an initial velocity, and a coordinate at which motion will stop
action.moveaccel = function(args)
	glib.assert_either (args.tag, args.id, "id or tag")
	glib.assert (args.initial_velocity, "initial_velocity")
	glib.assert (args.acceleration, "acceleration")
	glib.assert (args.ystop, "ystop")
	return { type="moveaccelerated", tag = args.tag, id = args.id, velocity = args.initial_velocity, acceleration = args.acceleration, ystop = args.ystop, actor = args.actor }
end

-- move item by a given displacement or until a given osition, at a given speed
action.move = function(args) 
	glib.assert_either (args.tag, args.id, "id or tag")
	glib.assert_either (args.to, args.by, "to or by")
	--glib.assert (args.speed, "speed")
	return { type="move", tag = args.tag, id = args.id, to = args.to, by = args.by, speed = args.speed, immediate = args.imm or false, flip =  args.flip or false }
end

action.callfunc = function (args) 
	assert (args.func, "func") 
	return { type="callfunc", func = args.func }
end

action.repeat_forever = function (args) 
	assert (args.func, "func") 
	assert (args.interval, "interval")
	return { type="repeat", func = args.func, interval = args.interval }
end

action.animate = function(args)
	glib.assert_either (args.tag, args.id, "id or tag")
	assert (args.anim, "anim")
	local fwd = args.fwd
	local sync = args.sync
	if (fwd == nil) then fwd = true end
	if (sync == nil) then sync = false end
	return {type="animate", tag = args.tag, id = args.id, anim = args.anim, fwd = fwd, sync = sync }
end

action.set_state = function(args)
	glib.assert_either (args.tag, args.id, "id or tag")
	--sglib.assert (args.actor, "actor")
	glib.assert (args.state, "state")
	return {type="setstate", tag = args.tag, id = args.id, state = args.state}
end

action.set_follow = function(args)
	glib.assert_either (args.tag, args.id, "id or tag")
	glib.assert (args.value, "value")
	return { 
		type="callfunc", 
		func = function() 
			local m1 = nil
			if (args.tag) then
				m1 = monkey.getEntity(args.tag)
			else
				m1 = monkey.getEntityFromId(args.id)
			end
			m1:setfollow(args.value)
		end
	}

end

action.suspend_script = function(args) 
	assert (args.script, "script")
	return { type="suspend_script", script = args.script}
end

action.suspend_all_scripts = function(args) 
	glib.assert (args.value, "value")
	return { type="suspend_all", value = args.value} 
end

action.resume_script = function(args) 
	assert (args.script, "script")
	return {type="resume_script", script = args.script}
end

action.kill_script = function(args) 
	assert (args.script, "script")
	return {type="kill_script", script = args.script}
end

action.set_variable = function(args)
	glib.assert (args.var, "var")
	glib.assert (args.value, "value")
	return { type = "callfunc", func = 
		function()
			print ("Setting " .. args.var .. " to " .. tostring(args.value))
			variables[args.var] = args.value
		end
	}
end


action.scroll = function (args) 
	glib.assert_either(args.by, args.to, "by or to")
	assert (args.speed, "speed")
	local by = args.by
	local to = args.to
	return { type="scroll", cam = "maincam", by = by, to = to, speed = args.speed }
end

action.activate = function (args)
	glib.assert (args.tag, "tag")
	glib.assert (args.active, "active")
	return { type ="setactive", tag = args.tag, active = args.active }

end

-- dynamically creates a new object in the game
action.create_object = function(args) 
	local parent = args.parent or "main"
	glib.assert (args.factory, "factory")
	glib.assert (args.args, "args")
	return { type = "callfunc", func = 
		function()
			print ("creating a new object ... ")
			local o = args.factory(args.args, args.pos)
			local m1 = monkey.getEntity(parent)
			local id = monkey.addEntity (o, m1)

			-- check if a script is provided in the factory
			if (args.script ~= nil) then
				print ("FATTTTONE")
				local actions = args.script(id, args.pos)
				local s = script.make(actions)
				monkey.play(s)
			end			
			-- if (args.script ~= nil) then
			-- 	local actions = args.script

			-- end
		end
	}
end




action.remove_object = function(args) 
	glib.assert_either (args.tag, args.id, "id or tag")
	return { type = "callfunc", func = 
		function()
			local i = nil
			if (args.id == nil) then
				print ("qui    22")
				i = monkey.getEntity(args.tag)
			else
				print ("qui " .. tostring(args.id))
				i = monkey.getEntityFromId(args.id)
			end
			i:remove()
		end
	}
end

action.show_message = function(args) 
	glib.assert (args.message, "message")
	glib.assert (args.color, "color")
	glib.assert (args.pos, "pos")
	return { type="show_message", message = args.message, color = args.color, pos = args.pos}
end

action.wait_click = function(args) 
	return { type="waitclick"}
end

action.treemove = function(args) 
	return { type = "treemove", tag = args.tag, to=args.parent}
end

action.blink = function(args)
	glib.assert_either (args.tag, args.id, "id or tag")
	glib.assert (args.duration, "duration")
	glib.assert (args.blink_duration, "blink_duration")
	return {type="blink", tag = args.tag, id = args.id, duration = args.duration, blink_duration=args.blink_duration }
end


action.change_cam_bounds = function (args)
	glib.assert (args.cam, "cam")	
	glib.assert (args.x, "x")
	glib.assert (args.y, "y")	
	return { type = "setcambounds", cam = args.cam, xmin = args.x[1], xmax = args.x[2], ymin = args.y[1], ymax = args.y[2] }
end

action.set_demo_mode = function(args) 
print ("CIAO MERDADURA!")
	glib.assert_either (args.tag, args.id, "id or tag")
	glib.assert (args.value, "value")
	return { type = "setdemo", value = args.value,  tag = args.tag, id = args.id, keys = args.keys, length = args.length or 0, sync = args.sync, events = args.events}	
end

