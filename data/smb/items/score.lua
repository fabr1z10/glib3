items.score = {}

items.score.create = function(args)
	local t = nextTag()	
	return {
		tag = t,
		pos = { args.pos[1], args.pos[2], args.z },
		components = {
			{ type="gfx", model = "score" .. args.score, anim="idle" },
		}
	}
end

items.score.script = function(m) 
	local s = script:new()
	s.actions = {
		[1] = {type="move", actor = m.tag, by = {0, 64}, speed = 100},
		[2] = {type="callfunc", func = function() monkey.removeEntity(m.tag) end, after={1} },	
	}
	monkey.play(s)
end

