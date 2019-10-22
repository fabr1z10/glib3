factory.score = {}

factory.score.create = function (args, pos) 
	print ("FAMMMI")
	glib.assert (args.sprite, "sprite")
	local position = pos or {0, 0, 0}
	return {
		type = "sprite",
		pos = position,
		model = args.sprite,
	}
end

factory.score.script = function(id, pos) 
	local actions = {
		{ type = action.move, args = {id = id, speed = 50, by ={0,64}}},
		{ type = action.remove_object, args = {id = id}},
	}
	return actions
end