action.set_enemy_dir = function(args)
	glib.assert_either (args.tag, args.id, "id or tag")
	glib.assert (args.left, "left")
	return {type="setenemydir", tag = args.tag, id = args.id, left = args.left}
end

action.dropcharacters = function(args)
	return { type="dropcharacters", tag = args.tag, id = args.id }

end

function P(x, y) return {x*16,y*16} end

function add_score(n)
	variables.score = variables.score + n
	local l = monkey.getEntity("score_label")
	l:settext(string.format("%06d", variables.score))
end
function add_coin(n)
	variables.coin = variables.coin + n
	local l = monkey.getEntity("coin_label")
	l:settext(string.format("%02d", variables.coin))
end


variables.data = {
	sheets = {
		[1] = { img = "smb1.png", tilesize = {16, 16}}
	},	
	templates = {
		castle = {
			sheet = 1,
			width = 5,
			height = 5,
			data = {
				15, 1, 15, 1, 13, 4, 15, 1, 15, 1,
				15, 1, 15, 1, 15, 2, 15, 1, 15, 1,
				14, 3, 15, 3, 15, 3, 15, 3, 14, 3,
				-1   , 12, 3, 15, 1, 13, 3,    -1,
				-1   , 14, 3, 14, 3, 14, 3,    -1
			}
		},
		big_castle = {
			sheet = 1,
			width = 9,
			height = 11,
			data = {
				15, 1, 15, 1, 13, 4, 15, 1, 13, 4, 15, 1, 13, 4, 15, 1, 15, 1,
				15, 1, 15, 1, 15, 2, 15, 1, 15, 2, 15, 1, 15, 2, 15, 1, 15, 1,
				15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1,
				15, 1, 15, 1, 15, 1, 13, 4, 15, 1, 13, 4, 15, 1, 15, 1, 15, 1,
				15, 1, 15, 1, 15, 1, 15, 2, 15, 1, 15, 2, 15, 1, 15, 1, 15, 1,
				14, 3, 14, 3, 15, 3, 15, 3, 15, 3, 15, 3, 15, 3, 14, 3, 14, 3,
				-1, -1, 15, 1, 15, 1, 13, 4, 15, 1, 15, 1, -1, -1,
				-1, -1, 15, 1, 15, 1, 15, 2, 15, 1, 15, 1, -1, -1,
				-1, -1, 14, 3, 15, 3, 15, 3, 15, 3, 14, 3, -1, -1,
				-1, -1, -1   , 12, 3, 15, 1, 13, 3,    -1, -1, -1,
				-1, -1, -1   , 14, 3, 14, 3, 14, 3,    -1, -1, -1
			}

		},
		big_hill = {
			sheet = 1,
			width = 5,
			height = 3,
			data = {
				10, 2, 11, 2, 14, 2, 11, 2, 12, 2,
				   -1, 10, 2, 11, 2, 12, 2,    -1,
				   -1,    -1, 13, 2,    -1,    -1
			}
		},
		small_hill = {
			sheet = 1,
			width = 3,
			height = 2,
			data = {
				10, 2, 11, 2, 12, 2,
				   -1, 13, 2, 	 -1,
			}
		},
		bush1 = {
			sheet = 1,
			width = 3,
			height = 1,
			data = { 2,3,3,3,4,3}
		},
		bush2 = {
			sheet = 1,
			width = 4,
			height = 1,
			data = { 2,3,3,3,3,3,4,3}
		},
		bush3 = {
			sheet = 1,
			width = 5,
			height = 1,
			data = { 2,3,3,3,3,3,3,3,4,3}
		},
		cloud1 = {
			sheet = 1,
			width = 3,
			height = 2,
			data = { 
				5,4,6,4,7,4,
				5,3,6,3,7,3
			}
		},
		cloud2 = {
			sheet = 1,
			width = 4,
			height = 2,
			data = { 
				5,4,6,4,6,4,7,4,
				5,3,6,3,6,3,7,3
			}
		},
		cloud3 = {
			sheet = 1,
			width = 5,
			height = 2,
			data = { 
				5,4,6,4,6,4,6,4,7,4,
				5,3,6,3,6,3,6,3,7,3
			}
		},
		flag = { sheet=1, width=1, height= 10, data= {3,2,3,2,3,2,3,2,3,2,3,2,3,2,3,2,3,2,4,2}},
		pipe_x = {
			sheet =1, width= 4, height = 4, data = {2,5,3,5,4,5,1,4,2,4,3,4,4,4,1,4,-1,-1,0,4,1,4,-1,-1,0,3,1,3}
		},
		pipe_1_2 = {
			sheet =1, width= 4, height = 8, data = {2,5,3,5,4,5,1,4,2,4,3,4,4,4,1,4,-1,-1,0,4,1,4,-1,-1,0,4,1,4,-1,-1,0,4,1,4,-1,-1,0,4,1,4,-1,-1,0,4,1,4,-1,-1,0,4,1,4}
		}
	}
}

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