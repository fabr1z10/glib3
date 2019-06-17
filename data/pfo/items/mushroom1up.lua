items.mushroom1up = {}

items.mushroom1up.create = function(args)
	local t = nextTag()	
	local s = {type="rect", width=16, height=16, offset={-8,0}}
	return {
		tag = t,
		pos = { args.pos[1], args.pos[2], args.z },
		components = {
			{ type="gfx", model = "mushroom1up", anim="idle" },
			-- type="collider", shape = s, tag = 22, flag= 1},
			{ type="multicollider", tag=mushroom1upTag, flag=4, initialshape="default", shapes = {
				{ name ="default", type="rect", width=16, height=16, offset={-8,0} },
			}},
			{ type="controller2d", maxclimbangle = 80, maxdescendangle = 80, horizontalrays=4, verticalrays=4 },
			{ type="dynamics2d", jumpheight = 64, timetojumpapex = 0.5 },
			{ type="statemachine", initialstate = "idle",
				states = {
					{ id = "idle", init = { type="animcollider", anim="idle" }},
					{ id = "walk", init = { type="animcollider", anim="idle", collider = "default" }, behavior= {type="enemywalk2d", speed=50, dir=-1, flip=false }}
				}
			}
		},
		-- children = {
		-- 	{ name="enemycollider", components = { {type="collider", shape=s, tag=mushroomTag, flag=4}, {type="gfx", shape=s, color = {255,0,0,255} }}}
		-- }
	}
end

items.mushroom1up.script = bonusRise

function mario_mushroom1up(mario, mushroom) 
	mushroom:remove()
	print ("1UP!")
end