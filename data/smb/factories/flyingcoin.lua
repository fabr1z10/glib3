factory.flyingcoin = {}

factory.flyingcoin.create = function (args, pos) 
	glib.assert (args.sprite, "sprite")
	local position = pos or {0, 0, 0}
	return {
		type = "sprite",
		pos = position,
		model = args.sprite,
	}
end

factory.flyingcoin.script = function(id, pos) 
	local actions = {
		{ type = action.moveaccel, args = {id = id, initial_velocity = {0,100}, acceleration = {0,-100}, ystop = pos[2]+16}},
		{ type = action.remove_object, args = {id = id}},
		{ type = action.create_object, args = { factory = factory.score.create, args = { sprite = "score_100" }, pos = {pos[1],pos[2]+16,0}, script = factory.score.script }}
	}
	return actions
end