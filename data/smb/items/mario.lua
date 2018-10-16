
function mario_is_hit(mario)
	marioinfo = mario:getinfo()
	if (marioinfo.invincible == false) then
		suspendplay()
		if (marioinfo.supermario == false) then
			local s = script:new()
			s.actions = {
				[1] = {type="animate", actor="player", anim="dead"},
				[2] = {type="delay", sec=0.5, after={1}},
				[3] = {type="movegravity", actor ="player", velocity={0,50}, g = 100, ystop = 0, after={2}},
				[4] = { type="gotoroom", room=variables._room, after={3} }
			}
			monkey.play(s)
		else
			local s = script:new()
			marioinfo.supermario = false
			marioinfo.invincible = true
			s.actions = {
				[1] = { type="animate", actor = "player", anim="bigtosmall", loop=1},
				[2] = {type="callfunc", func = resumeplay, after={1} },
				[3] = {type="blink", actor="player", duration= 5, blinkduration=0.2, after={2}},
				[4] = {type="callfunc", func= function() marioinfo.invincible = false end, after={3} }
			}
			monkey.play(s)
		end
	end
end
