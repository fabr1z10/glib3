scripts.cook = function() 
	local s = script:new()
	s.actions = {
		action.delay { id=1, sec = 5 },
		action.create_object { id = 2, name="scummbar.cook", pos = {100,5,0}, anim ="idle_right", face = "west", applydepth = true}
		

	}
	monkey.play(s)

end