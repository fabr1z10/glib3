action = {}

action.change_room = function (args) 	
	glib.assert (args.room, "room")
	return { type="gotoroom", room = args.room }
end

action.noop = function(args) 
	return { type="noop" }	
end

action.delay = function (args) 
	glib.assert (args.sec, "sec")
	return { type="delay", sec = args.sec }

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
	glib.assert (args.speed, "speed")
	return { type="move", tag = args.tag, id = args.id, to = args.to, by = args.by, speed = args.speed }
end

action.callfunc = function (args) 
	assert (args.func, "func") 
	return { type="callfunc", func = args.func }
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
	assert (args.actor, "actor")
	assert (args.state, "state")
	return {type="setstate", tag = args.tag, id = args.id, state = args.state}
end

action.suspend_script = function(args) 
	assert (args.script, "script")
	return { type="suspend_script", script = args.script}
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
	print ("ciao ciao2")
	glib.assert (args.var, "var")
	glib.assert (args.value, "value")
	print ("ciao")
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
	glib.assert (args.value, "value")
	return { 
		type="callfunc", 
		func = function() 
			local m = monkey.getEntity(args.tag)
			m:setactive(args.value)
		end
	}

end

-- dynamically creates a new object in the game
action.create_object = function(args) 
	assert (args.factory, "factory")
	assert (args.args, "args")
	return { type = "callfunc", func = 
		function()
			print ("creating a new object ... ")
			local o = args.factory(args.args)
			local m1 = monkey.getEntity("main")
			monkey.addEntity (o, m1)
		end
	}
end

action.remove_object = function(args) 
	assert (args.tag, "tag")
	return { type = "callfunc", func = 
		function()
			print ("ciao " .. args.tag)
			local i = monkey.getEntity(args.tag)
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