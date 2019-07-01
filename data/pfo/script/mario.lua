function mario_removeenemy(mario, enemy) 
	local actions = {
		{ type = action.remove_object, args = { id = enemy.id}}
	}
	local s = script.make(actions)
	monkey.play(s)
end

function generic_hit(hitter, hit) 

	local hit_info = hit:getinfo()
	if (hit.tag == "player") then
		if (hit_info.invincible == true) then
			return
		end
	end
	hit_info.energy = hit_info.energy - 1	
	if (hit_info.energy > 0) then
		if (hit.x > hitter.x) then
			hit.vx = hit.flipx and -500 or 500
		 else
		 	hit.vx = hit.flipx and 500 or -500
		 end
		 if (hit.tag == "player") then
		 	hit_info.invincible = true
		 	local actions = {
				{ type = action.blink, args = { tag="player", duration = 5, blink_duration=0.1}},
				{ type = action.callfunc, args = { func = function() hit_info.invincible = false end }}
			}
			local s = script.make(actions)
			monkey.play(s)
		 end
	else
		local fx = {
			type = "sprite",
			model = "fx_1",
			pos = {hit.x, hit.y, 0},
		}
		local actions = {
			{ type = action.remove_object, args = {id=hit.id}},
			{ type = action.callfunc, args = { func= function()  
				local m1 = monkey.getEntity("main")
				local id = monkey.addEntity (fx, m1)
				local acs = {
					{ type = action.animate, args = {id = id, anim="default", sync=true}},
					{ type = action.remove_object, args= {id=id}}
				}
				local s1 = script.make(acs)
				monkey.play(s1)
				end}
			}
		}
		local s = script.make(actions)
		monkey.play(s)
	end
end


function player_hits ()
	print ("PLAYER HITS ENEMY")
end

function mario_goomba(mario, goomba, sx, sy) 

	if (goomba.state == "die") then
		return
	end
	if (mario.state == "jump" and mario.vy < 0 and sy > 0 and math.abs(sx) < 0.01) then
		mario.vy = -mario.vy
		local actions = {
			{ type = action.set_state, args = { id = goomba.id, state="die" }},	
			{ type = action.delay, args = { sec = 2}},
			{ type = action.remove_object, args = { id = goomba.id}}
		}
		local s = script.make(actions)
		monkey.play(s)
		return
	end

	print (mario.id)
	print (goomba.id)
	print (action.set_state == nil)
	local actions = {
		{ type = action.callfunc, args = { func = function() mario:enablecollision(false) end }},
		{ type = action.set_state, args = { id = mario.id, state="nil" }},
		{ type = action.animate, args = {id =mario.id, anim="die" }},
		{ type = action.delay, args = { sec = 1}},
		{ type = action.moveaccel, args = { id=mario.id, initial_velocity = {0, variables.jump_velocity}, acceleration={0,variables.gravity}, ystop = -30}},
		{ type = action.restart_room }
	}
	local s = script.make(actions)
    print ("qiqui")
	monkey.play(s)


	-- if (marioinfo.invincible == false) then
	-- 	suspendplay()
	-- 	if (marioinfo.supermario == false) then
	-- 		local s = script:new()
	-- 		s.actions = {
	-- 			[1] = {type="animate", actor="player", anim="dead"},
	-- 			[2] = {type="delay", sec=0.5, after={1}},
	-- 			[3] = {type="movegravity", actor ="player", velocity={0,50}, g = 100, ystop = 0, after={2}},
	-- 			[4] = { type="gotoroom", room=variables._room, after={3} }
	-- 		}
	-- 		monkey.play(s)
	-- 	else
	-- 		local s = script:new()
	-- 		marioinfo.supermario = false
	-- 		marioinfo.invincible = true
	-- 		s.actions = {
	-- 			[1] = { type="animate", actor = "player", anim="bigtosmall", loop=1},
	-- 			[2] = {type="callfunc", func = resumeplay, after={1} },
	-- 			[3] = {type="blink", actor="player", duration= 5, blinkduration=0.2, after={2}},
	-- 			[4] = {type="callfunc", func= function() marioinfo.invincible = false end, after={3} }
	-- 		}
	-- 		monkey.play(s)
	-- 	end
	-- end
end