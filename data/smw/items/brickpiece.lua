items.brickpiece = {}

items.brickpiece.create = function(arg)
	local pos = arg.pos
	local z = arg.z or 0
	local v = arg.velocity
    local b = nextTag()
	return {
		tag = b,
		pos = {pos[1], pos[2], z},
		components = {
			{ type="gfx", model="brickpiece", anim="idle", width = 16, height = 16},	
			{ type="info", velocity = v }
		}
	}
end

items.brickpiece.script = function(id) 
	local s = script:new()
	local m = monkey.getEntity(id.tag)
	local info = m:getinfo()
	s.actions = {
		[1] = {type="movegravity", actor = m.tag, velocity = info.velocity, g = 100, ystop = 0 },
		[2] = {type="callfunc", func = function() m:remove() end, after={1}}
	}
	monkey.play(s)
end

