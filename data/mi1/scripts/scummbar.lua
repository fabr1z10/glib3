scripts.cook = function() 
	local s = script:new()
	s.actions = {
		action.delay { id=1, sec = 10 },
		action.open_door { id = 2, door = "scummbar.door_kitchen"}
		--action.create_object { id = 3, name="scummbar.cook", pos = {100,5,0}, anim ="idle_right", face = "west", applydepth = true}
		

	}
	monkey.play(s)

end