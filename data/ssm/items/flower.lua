items.flower = {}

items.flower.create = function(args)
	-- flower is created only if supermario is true
	local mario = monkey.getEntity("player")
	local marioinfo = mario:getinfo()
	if (marioinfo.supermario == false) then
		print ("NO SUPAMARIO")
		return items.mushroom.create(args)
	else
		local t = nextTag()	
		local s = {type="rect", width=16, height=16, offset={-8,0}}
		return {
			tag = t,
			pos = { args.x, args.y, args.z },
			components = {
				{ type="gfx", model = "flower", anim="idle" },
				-- type="collider", shape = s, tag = 22, flag= 1},
				{ type="multicollider", tag=flowerTag, flag=4, initialshape="default", shapes = {
					{ name ="default", type="rect", width=16, height=16, offset={-8,0} },
				}},
				{ type="controller2d", maxclimbangle = 80, maxdescendangle = 80, horizontalrays=4, verticalrays=4 },
				{ type="dynamics2d", jumpheight = 64, timetojumpapex = 0.5 },
				{ type="statemachine", initialstate = "idle",
					states = {
						{ id = "idle", init = { type="animcollider", anim="idle" }},
						{ id = "walk", init = { type="animcollider", anim="idle", collider = "default" } }
					}
				}
			}
		}
		-- children = {
		-- 	{ name="enemycollider", components = { {type="collider", shape=s, tag=mushroomTag, flag=4}, {type="gfx", shape=s, color = {255,0,0,255} }}}
		-- }
	end
end
items.flower.script = bonusRise

function mario_flower(mario, flower) 
	flower:remove()
	info = mario:getinfo()
	info.fire = true
	mario:resetstate()
	-- if (info.supermario == false) then
	-- 	info.supermario = true
	-- 	--mario:resetstate()
	-- 	local ros = monkey.getEntity("restofscene")
	-- 	ros:enableupdate(false)
	-- 	mario:enablestatemachine(false)
	-- 	local s = script:new()
	-- 	s.actions = {
	-- 		[1] = { type="animate", actor = "player", anim="smalltobig", loop=1},
	-- 		[2] = {type="callfunc", func = resumeplay, after={1} }
	-- 	}
	-- 	monkey.play(s)
	-- end
end