items.banzaibill = {}

-- args:
-- mandatory:s
-- x, y     initial position
-- dir      walking direction (1 = right, -1 = left)
items.banzaibill.create = function(args)
	local t = nextTag()	
	local z = args.z or 0
	return {
		tag = t,
		pos = { args.pos[1], args.pos[2], z },
		components = {
			{ type="gfx", model = "banzai_bill", anim="idle" },
			{ type="collider", tag=banzaiTag, flag=collisionFlags.enemy, mask = collisionFlags.player, shape = { 
				type="compound", shapes = { {type="rect", width = 32, height=64, offset={32,0}}, { type="circle", radius=32, offset = {32,32}}}
				--type="circle", radius=32, offset={32,32}
			}}
		}
	}
end

items.banzaibill.script = function(m) 
	local s = script:new()
	s.actions = {
		[1] = {type="move", to={0, m.pos[2]}, actor = m.tag, speed = 100},
		[2] = {type="callfunc", func = function() 
			local item = monkey.getEntity(m.tag)  
			item:remove() 
		end, after={1}}
	}
	monkey.play(s)
end


function mario_banzai(mario, goomba, sx, sy)
	
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