scripts.cook = function() 
	local s = script:new("cook")
	local pos = items["scummbar.door_kitchen"].walk_to
	
	if (variables._previousroom == "kitchen") then
		local mancombPos = items["scummbar.mancomb"].walk_to
		variables["cook_in_kitchen"] = false
		s.actions = {
			action.create_object { id = 1, name="scummbar.cook", pos = {mancombPos[1], mancombPos[2], 0}, anim ="idle_back", face = "north", applydepth = true},
			action.delay { id=2, sec = 5 },
			action.walkto { id=3, actor ="scummbar.cook", obj = items["scummbar.door_kitchen"]},
			action.remove_object { id = 4, name = "scummbar.cook" },
			action.close_door { id = 5, door = "scummbar.door_kitchen"},
			action.set_variable { id = 6, var = "cook_in_kitchen", value = true },
		}
	end
	local s1 = script:new()
	s1.actions = {
		action.delay { id=1, sec = 10 },
		action.open_door { id = 2, door = "scummbar.door_kitchen"},
		action.set_variable { id = 3, var = "cook_in_kitchen", value = false },
		action.create_object { id = 4, name="scummbar.cook", pos = {pos[1], pos[2], 0}, anim ="idle_right", face = "west", applydepth = true},
		action.walkto { id=5, actor ="scummbar.cook", obj = items["scummbar.mancomb"]},
		action.turn { id = 6, actor="scummbar.cook", dir="north"},
		action.delay { id=7, sec = 5 },
		action.walkto { id=8, actor ="scummbar.cook", obj = items["scummbar.door_kitchen"]},
		action.remove_object { id = 9, name = "scummbar.cook" },
		action.close_door { id = 10, door = "scummbar.door_kitchen"},
		action.set_variable { id = 11, var = "cook_in_kitchen", value = true },
	}
	s1.loop = 1
	s:push{script=s1}
	monkey.play(s)

end