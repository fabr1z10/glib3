items.rex = {}

-- args:
-- mandatory:s
-- x, y     initial position
-- dir      walking direction (1 = right, -1 = left)
items.rex.create = function(args)
	local pos = args.pos
	local dir = args.dir
	local z = args.z or 0

	local t = nextTag()	
	--local s = {type="rect", width=16, height=16, offset={0,0}}
	return {
		tag = t,
		pos = {pos[1], pos[2], z },
		components = {
			{ type="gfx", model = "rex", anim="walk" },
			--{ type="collider", shape = s, tag = 22, flag= 1},
			{ type="multicollider", tag=rexTag, flag=collisionFlags.enemy, mask = collisionFlags.player, initialshape="default", shapes = {
				{ name ="default", type="rect", width=16, height=16, offset={-8,0} },
			}},
			{ type="controller2d", maxclimbangle = 80, maxdescendangle = 80, horizontalrays=4, verticalrays=4 },
			{ type="dynamics2d", jumpheight = 64, timetojumpapex = 0.5 },
			{ type="statemachine", initialstate = "walk",
				states = {
					{ id = "walk", init = { type="animcollider", anim="walk", collider="default" }, behavior= {type="enemywalk2d", speed=50, dir= dir, flip=false, flip_when_platform_ends = true }},
					{ id = "walksmall", init = { type="animcollider", anim="walksmall", collider="default" }, behavior= {type="enemywalk2d", speed=50, dir= dir, flip=false, flip_when_platform_ends = true }},
					{ id = "dead", init = { type="animcollider", anim="dead" }}
				}
			}
		},
		-- children = {
		-- 	{ name="enemycollider", components = { {type="collider", shape=s, tag=goombaTag, flag=4}, {type="gfx", shape=s, color = {255,0,0,255} }}}
		-- }
	}
end



function mario_rex(mario, goomba, sx, sy)
	
	-- if (mario.state == "jump" and mario.vy < 0 and sy > 0 and math.abs(sx) < 0.01) then
	-- 	mario.vy = -mario.vy
	-- 	goomba:changestate("dead")
	-- 	local s = script:new()
	-- 	s.actions = {
	-- 		[1] = {type="delay", sec=2},
	-- 		[2] = {type="callfunc", func = function() goomba:remove() end, after={1}}
	-- 	}
	-- 	monkey.play(s)
	-- else
	-- 	mario_is_hit(mario)
	-- end
end