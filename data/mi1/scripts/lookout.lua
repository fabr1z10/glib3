script.lookout.init_dialogue = function(n)
	local s = script:new()
	s.actions = {
		[1] = say2 { actor = objects.guybrush, lines= {d[n] }},
		[2] = { type="turn", actor = "lookout", dir ="south", after = {1}}, 
		[3] = say2 { actor = room.items.lookout, lines = {d[5], d[6], d[7], d[8], d[9]}, after= {2} }
	}
	return s
end

script.lookout.turn = function()
	local s = script:new()
	s.actions = {
		[1] = say2 { actor = objects.guybrush, lines= {d[12] }},
		[2] = { type="turn", actor = "lookout", dir ="east", after={1}}, 
		[3] = say2 { actor = room.items.lookout, lines = {d[15], d[16] }, after={2}}
	}
	return s
end