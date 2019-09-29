function mario_end_level(arg)
print ("CIANEIEIEIE")

	local p = monkey.getEntity("player")
	local s = script:new()
	local sw = monkey.getEntity(arg.goal)
	sw:setactive(false)
	s.actions = {
		[1] = { type="changestate", actor="player", state="nophys"},
		[2] = { type="animate", actor ="player", anim="slide", flipx = false, after={1}},
		[3] = { type="move", to={p.x, arg.y}, speed = 50, actor = "player", after={2}},	
		[4] = { type="move", by={0, arg.deltayflag}, speed = 50, actor = "flag", after={2}},	
		[5] = { type="changestate", actor="player", state="idle", after={3}},
		[6] = { type="virtualkey", key = 262, action = 1, after={5}},

	}
	monkey.play(s)

end

function mario_complete() 
	local s = script:new()
	s.actions = {
		[1] = { type="virtualkey", key = 262, action = 0},
		[2] = { type="callfunc", after={1}, func = function ()  
			local m = monkey.getEntity("player")
			m:setactive(false)
		end }
	}
	monkey.play(s)

end



