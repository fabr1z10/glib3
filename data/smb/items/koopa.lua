items.koopa = {}

function shell_end(entity)

	-- terminate script 
	print ("killing script: _shell" .. entity.tag)
	monkey.killscript("_shell" .. entity.tag)
end

items.koopa.create = function(args)
	local t = nextTag()	
	local s = {type="rect", width=16, height=24, offset={-8,0}}
	return {
		tag = t,
		pos = { args.x, args.y, args.z },
		components = {
			{ type="gfx", model = "koopa", anim="walk" },
			--{ type="collider", shape = s, tag = 22, flag= 1},
			{ type="multicollider", tag=koopaTag, flag=1, initialshape="default", shapes = {
				{ name ="default", type="rect", width=16, height=24, offset={-8,0} },
				{ name ="shell", type="rect", width=16, height=16, offset={-8,0} },
			}},
			{ type="controller2d", maxclimbangle = 80, maxdescendangle = 80, horizontalrays=4, verticalrays=4 },
			{ type="dynamics2d", jumpheight = 64, timetojumpapex = 0.5 },
			{ type="statemachine", initialstate = "walk",
				states = {
					{ id = "walk", init = { type="animcollider", anim="walk", collider="default" }, behavior= {type="enemywalk2d", speed=50, dir= args.dir, flip=true } },
					{ id = "shell", init = { type="animcollider", anim="shell", collider="shell" }, finalizer = { type="lua", func = shell_end }},
					{ id = "shellfly", init = { type="animcollider", anim="shell", collider="shell" }, behavior= {type="enemywalk2d", speed=100, dir= args.dir, flip=false }}
				}
			}
		}
	}
	
end



function mario_koopa(mario, koopa, sx, sy) 
	if (koopa.state == "walk" or koopa.state == "shellfly") then
		if (hitFromAbove(mario, sx, sy)) then
			mario.vy = -mario.vy
			koopa:changestate("shell")
			local s = script:new("_shell" .. koopa.tag)
			s.actions = {
				[1] = {type="delay", sec=2},
				[2] = {type="animate", actor = koopa.tag, anim="blink", after={1} },
				[3] = {type="delay", sec=2, after={2}},
				[4] = {type="changestate", actor = koopa.tag, state="walk", after={3}}
			}
			monkey.play(s)
		else
			mario_is_hit(mario)
		end
	elseif (koopa.state == "shell") then
		if (hitFromAbove(mario, sx, sy)) then
			mario.vy = -mario.vy
		end
		dir = (mario.x < koopa.x) and 1 or -1
		koopa:move(-sx, 0, 0)
		koopa:changestateparam("shellfly", { dir = dir})
	end
end