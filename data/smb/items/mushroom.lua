items.mushroom = {}

items.mushroom.create = function(args)
	local t = nextTag()	
	local s = {type="rect", width=16, height=16, offset={-8,0}}
	return {
		tag = t,
		pos = { args.x, args.y, args.z },
		components = {
			{ type="gfx", model = "mushroom", anim="idle" },
			{ type="collider", shape = s, tag = 22, flag= 1},
			{ type="controller2d", maxclimbangle = 80, maxdescendangle = 80, horizontalrays=4, verticalrays=4 },
			{ type="dynamics2d", jumpheight = 64, timetojumpapex = 0.5 },
			{ type="statemachine", initialstate = "idle",
				states = {
					{ id = "idle", init = { type="animcollider", anim="idle", activate= {} }},
					{ id = "walk", init = { type="animcollider", anim="idle", activate={"enemycollider"} }, behavior= {type="enemywalk2d", speed=50, dir=-1, flip=false }}
				}
			}
		},
		children = {
			{ name="enemycollider", components = { {type="collider", shape=s, tag=mushroomTag, flag=4}, {type="gfx", shape=s, color = {255,0,0,255} }}}
		}
	}
end

function mario_mushroom(e1, e2) 
	e2:parent():remove()
	mario = e1:parent()
	info = mario:getinfo()
	if (info.supermario == false) then
		info.supermario = true
		--mario:resetstate()
		local ros = monkey.getEntity("restofscene")
		ros:enableupdate(false)
		mario:enablestatemachine(false)
		local s = script:new()
		s.actions = {
			[1] = { type="animate", actor = "player", anim="smalltobig", loop=1},
			[2] = {type="callfunc", func = resumeplay, after={1} }
		}
		monkey.play(s)
	end
end