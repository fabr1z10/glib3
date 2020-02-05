local d = strings.dialogues.fester

local f = function(n) 
	return {
		{ type = scumm.action.say, args = { actor="guybrush", lines = { d[n]}}},
		{ type = scumm.action.say, args = { actor="fester", lines = { d[14]}}},
		{ type = scumm.action.say, args = { actor="guybrush", lines = { d[15], d[16]}}},
		{ type = scumm.action.say, args = { actor="fester", lines = { d[17], d[18], d[19], d[20], d[21], d[22]}}},
		{ type = scumm.action.walkto, args = { tag="fester", pos ={100,10}}},
		{ type = scumm.action.turn, args = { tag="fester", dir="east" }},
		{ type = scumm.action.say, args = { actor="fester", lines = { d[23]}}},
		{ type = scumm.action.walkto, args = { tag="fester", pos ={0,10}}},
		{ type = action.remove_object, args = {tag="fester"}},
		{ type = scumm.action.turn, args = { tag="player", dir="south" }},
		{ type = scumm.action.say, args = { actor="guybrush", lines = { d[24]}}},
	} 
end

engine.dialogues.fester = {
	-- root
	init = function()
	end,
	close = function(n)
	end,
	nodes = {
		[1] = { children = {2, 3, 4 }},
		[2] = { text = d[6], active=true, children={5, 6, 7}, script = {
			{ type = scumm.action.say, args = { actor="guybrush", lines = { d[6]}}},
			{ type = scumm.action.walkto, args = { tag="fester", pos ={160,10}}},
			{ type = scumm.action.say, args = { actor="fester", lines = { d[9], d[10]}}},
		} },
		[3] = { text = d[7], active=true, children={5, 6, 7}, script = {
			{ type = scumm.action.say, args = { actor="guybrush", lines = { d[7]}}},
			{ type = scumm.action.walkto, args = { tag="fester", pos ={160,10}}},
			{ type = scumm.action.say, args = { actor="fester", lines = { d[25], d[10]}}},
		} },
		[4] = { text = d[8], active=true, children={5, 6, 7}, script = {
			{ type = scumm.action.say, args = { actor="guybrush", lines = { d[8]}}},
			{ type = scumm.action.walkto, args = { tag="fester", pos ={160,10}}},
			{ type = scumm.action.say, args = { actor="fester", lines = { d[26], d[10]}}},
		} },
		[5] = { text = d[11], active=true, script = f(11)},
		[6] = { text = d[12], active=true, script = f(12) },
		[7] = { text = d[13], active=true, script = f(13) },


	}
}