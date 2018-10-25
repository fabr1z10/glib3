items.goomba = {}

-- args:
-- mandatory:
-- x, y     initial position
-- dir      walking direction (1 = right, -1 = left)
items.goomba.create = function(args)
	print ("DODODODO")
print (tostring(args.dir))
	local t = nextTag()	
	local s = {type="rect", width=16, height=16, offset={-8,0}}
	local z = args.z or 0
	return {
		tag = t,
		pos = { args.pos[1]*16, args.pos[2]*16, z },
		components = {
			{ type="gfx", model = "goomba", anim="walk" },
			--{ type="collider", shape = s, tag = 22, flag= 1},
			{ type="multicollider", tag=goombaTag, flag=1, initialshape="default", shapes = {
				{ name ="default", type="rect", width=16, height=16, offset={-8,0} },
			}},
			{ type="controller2d", maxclimbangle = 80, maxdescendangle = 80, horizontalrays=4, verticalrays=4 },
			{ type="dynamics2d", jumpheight = 64, timetojumpapex = 0.5 },
			{ type="statemachine", initialstate = "walk",
				states = {
					{ id = "walk", init = { type="animcollider", anim="walk", collider="default" }, behavior= {type="enemywalk2d", speed=50, dir= args.dir, flip=false }},
					{ id = "dead", init = { type="animcollider", anim="dead" }}
				}
			}
		},
		-- children = {
		-- 	{ name="enemycollider", components = { {type="collider", shape=s, tag=goombaTag, flag=4}, {type="gfx", shape=s, color = {255,0,0,255} }}}
		-- }
	}
end



function mario_goomba(mario, goomba, sx, sy)
	
	if (mario.state == "jump" and mario.vy < 0 and sy > 0 and math.abs(sx) < 0.01) then
		mario.vy = -mario.vy
		goomba:changestate("dead")
		local s = script:new()
		s.actions = {
			[1] = {type="delay", sec=2},
			[2] = {type="callfunc", func = function() goomba:remove() end, after={1}}
		}
		monkey.play(s)
	else
		mario_is_hit(mario)
	end
end