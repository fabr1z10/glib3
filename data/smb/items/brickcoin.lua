items.brickcoin = {}

items.brickcoin.create = function(args)
	local t = nextTag()	
	return {
		tag = t,
		pos = { args.pos[1], args.pos[2], args.z },
		components = {
			{ type="gfx", model = "brickcoin", anim="idle" },
		},
	}
end

items.brickcoin.script = function(m) 
	print (m.tag .. " " .. tostring(m.y))
	local s = script:new()
	s.actions = {
		[1] = {type="movegravity", actor = m.tag, velocity = {0,100}, g = 100, ystop = m.pos[2]+16},
		[2] = {type="callfunc", func = function() monkey.removeEntity(m.tag) end, after={1} },	
		[3] = {type="callfunc", func = curry(CreateItem, {id="score", args= { pos={m.pos[1], m.pos[2]+16}, z=1, score=100}}), after={1}}
		-- generate score
	}
	monkey.play(s)
end

