items.goomba = {}

items.goomba.create = function(args)
	local t = nextTag()	
	local s = {type="rect", width=16, height=16, offset={-8,0}}
	return {
		tag = t,
		pos = { args.x, args.y, args.z },
		components = {
			{ type="gfx", model = "goomba", anim="walk" },
			{ type="collider", shape = s, tag = 22, flag= 1},
			{ type="controller2d", maxclimbangle = 80, maxdescendangle = 80, horizontalrays=4, verticalrays=4 },
			{ type="dynamics2d", jumpheight = 64, timetojumpapex = 0.5 },
			{ type="statemachine", initialstate = "walk",
				states = {
					{ id = "walk", init = { type="animcollider", anim="walk", activate={"enemycollider"} }, behavior= {type="enemywalk2d", speed=50, dir= args.dir, flip=false }},
					{ id = "dead", init = { type="animcollider", anim="dead", activate={} }}
				}
			}
		},
		children = {
			{ name="enemycollider", components = { {type="collider", shape=s, tag=goombaTag, flag=4}, {type="gfx", shape=s, color = {255,0,0,255} }}}
		}
	}
end



function mario_goomba(e1, e2) 
	local mario = e1:parent()
	if (mario.state == "jump" and mario.vy < 0) then
		mario.vy = -mario.vy
		e2:parent():changestate("dead")
		local s = script:new()
		s.actions = {
			[1] = {type="delay", sec=2},
			[2] = {type="callfunc", func = function() e2:parent():remove() end, after={1}}
		}
		monkey.play(s)
	else
		marioinfo = mario:getinfo()
		if (not mario.invincible) then
			suspendplay()
			local s = script:new()
			s.actions = {
				[1] = {type="animate", actor="player", anim="dead"},
				[2] = {type="delay", sec=0.5, after={1}},
				[3] = {type="movegravity", actor ="player", velocity={0,50}, g = 100, ystop = 0, after={2}},
				[4] = { type="gotoroom", room=variables._room, after={3} }
			}
			monkey.play(s)
		end
	end
end