local marioAcc = 0.05
local marioSpeed = 75

items.mario = {}

items.mario.create = function(args)
	return 
	{	
		tag="player",
		pos = {args.pos[1], args.pos[2], 0},
		components = {
			{ type="gfx", model="mario", anim="idle" },
			{ type="controller2d", maxclimbangle = 80, maxdescendangle = 80, horizontalrays=4, verticalrays=4 },
			{ type="dynamics2d", jumpheight = 80, timetojumpapex = 0.5 },
			{ type="multicollider", tag=1, flag=1, initialshape="small", shapes = {
				{ name ="small", type="rect", width=14, height=16, offset={-8,0}},
				{ name ="big", type="rect", width=14, height=32, offset={-8,0}},
				{ name ="duck", type="rect", width=14, height=24, offset={-8,0}}
			}},
			{ type="statemachine", initialstate = "idle",
				states = {
				 	{ id = "idle", init = { type="luaanim", func = curry21(marioinit, "idle") }, behavior = { type ="idle2d", acceleration = marioAcc }},
					{ id = "walk", init = { type="luaanim", func = curry21(marioinit, "walk") }, behavior = { type ="walk2d", acceleration = marioAcc, speed= marioSpeed }},
					{ id = "jump", init = { type="luaanim", func = curry21(marioinit, "jump") }, behavior = { type ="jump2d", acceleration = marioAcc, speed= marioSpeed }},
					{ id = "duck", init = { type="animcollider", anim= "duck", collider="duck" }, behavior = { type ="idle2d", acceleration = marioAcc, speed= marioSpeed }},
				},
				keys = {
				 	{ current = "idle", key =  262, next="walk" },
				 	{ current = "idle", key =  263, next="walk" },
				 	{ current = "idle", key =  265, next="jump" },
				 	{ current = "idle", key =  264, func=mario_duck},
					-- --{ current = "idle", key =  262, next="duck" },
					{ current = "walk", key =  265, next="jump" },
					{ current = "walk", key = 264, func=mario_duck},
					{ current = "duck", key = 264, press=false, next="idle" }
					-- event key release when duck returning to idle
				}
			},
			{ type="info", supermario = false, fire = false, invincible = false },
			{ type="follow", cam ="maincam", relativepos={0,0,5}, up={0,1,0} }
		 },
	}
end

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
