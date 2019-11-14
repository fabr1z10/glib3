factory.flower = {}

factory.flower.response = function (p1, p2) 
	local mario = monkey.getEntity("player")
	--local isSuperMario = (mario:getinfo().supermario)
	factory.mario.change_state(mario, 3)
	monkey.removeFromId(p2.id)
end

factory.flower.script = function(id) 
	local actions = {
		{ type=action.move, args = { id = id, by = {0, engine.tilesize}, speed=5}},
	}
	return actions
end

factory.flower.create = function (args, pos) 
	glib.assert (args.sprite, "sprite")
	local position = pos or {0, 0, 0}
	local tag = variables.collision.tags.flower

	return {
		type = "sprite",
		pos = position,
		model = args.sprite,
		components = {
			{ 
				type = "smartcollider", 
				tag = tag, 
				flag = variables.collision.flags.foe, 
				mask = variables.collision.flags.player
			},
		}
	}

end
