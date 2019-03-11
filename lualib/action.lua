action = {}

action.change_room = function (args) 	
	glib.assert (args.room, "room")
	return { type="gotoroom", room = args.room }
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