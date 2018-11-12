items.midwaygate = {}

-- args:
-- mandatory:s
-- x, y     initial position
-- dir      walking direction (1 = right, -1 = left)
items.midwaygate.create = function(args)
	local pos = args.pos
	local t = nextTag()	
	--local s = {type="rect", width=16, height=16, offset={0,0}}
	return {
		tag = t,
		pos = {pos[1], pos[2], 0 },
		children = {
			{ pos = {32, 0, 0.1}, components = { {type="gfx", model="midway_gate", anim="idle" }}},
			{ pos = {32, 16, 0.1}, components = { {type="gfx", model="midway_gate", anim="idle" }}},
			{ pos = {32, 32, 0.1}, components = { {type="gfx", model="midway_gate", anim="idle" }}},
			{ pos = {32, 48, 0.1}, components = { {type="gfx", model="midway_gate_top", anim="idle" }}},
			{ pos = {0, 0, -0.1}, components = { {type="gfx", model="midway_gate_back", anim="idle" }}},
			{ pos = {0, 16, -0.1}, components = { {type="gfx", model="midway_gate_back", anim="idle" }}},
			{ pos = {0, 32, -0.1}, components = { {type="gfx", model="midway_gate_back_flag", anim="idle" }}},
			{ pos = {0, 48, -0.1}, components = { {type="gfx", model="midway_gate_back_top", anim="idle" }}},
			{ pos = {16, 32, 0.1}, components = { 
				{type="gfx", model="midway_flag", anim="idle" },
				{type="collider", shape = { type="rect", width=16, height = 3, offset= {0,12}}, tag = checkpointTag, flag = collisionFlags.enemy, mask = collisionFlags.player }
			} }
		-- 	{ name="enemycollider", components = { {type="collider", shape=s, tag=goombaTag, flag=4}, {type="gfx", shape=s, color = {255,0,0,255} }}}
		}
	}
end

function mario_checkpoint(e1, e2)
    e2:remove()
    print ("POLLLOOOO")
end
