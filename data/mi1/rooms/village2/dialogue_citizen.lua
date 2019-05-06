local d = strings.dialogues.citizen

local s1 = {
	{ type = scumm.action.say, args = { actor = "village2.citizen",  lines = {d[18]}, animstart="talk_e", animend="idle_e" }},
	{ type = action.animate, args = { tag="village2.citizen", anim="open_jacket", sync=true}},
	{ type = scumm.action.say, args = { actor="village2.citizen", lines = {d[19]}, animstart="talk_e_1", animend="idle_e_1"}},
	{ type = action.delay, args = {sec= 2}},
	{ type = action.animate, args = {tag="village2.citizen", anim="open_jacket", fwd = false, sync=true}},
    { type = scumm.action.say, args = {actor="village2.citizen", lines = {d[20]}, animstart="talk_e", animend="idle_e"}},
	{ type = action.animate, args = {tag="village2.citizen", anim="rollmap", sync=true}},
	{ type = scumm.action.say, args = {actor="village2.citizen", lines = {d[21], d[22]}, animstart="talk_e_2", animend="idle_e_2"}},
	{ type = action.animate, args = {tag="village2.citizen", anim="rollmap", fwd=false, sync = true}},
	{ type = action.say, args = {actor="village2.citizen", lines = {d[23]}, animstart="talk_e", animend="idle_e"}},
	{ type = action.set_variable, args = { var = "talked_to_citizen", value=true}},
	{ type = action.set_variable, args = { var="talked_about_map", value=true}}	
}

local s2 = function(n, k) 
	local lines = k and {d[k], d[6], d[7]} or {d[6], d[7]}
	return {
		{ type = scumm.action.say, args = { actor = "guybrush",  lines = {d[n]} }},
		{ type = scumm.action.say, args = { actor = "village2.citizen",  lines = lines, animstart="talk_e", animend="idle_e" }},
		{ type = action.set_variable, args = { var = "talked_to_citizen", value=true}}
	}
end

engine.dialogues.citizen = {
	close = function()
		local actions = {
			{ type = action.animate, args = {tag="village2.citizen", anim="idle_s"}}
		}
		local s = script.make(actions) 
		monkey.play(s)
	end,
	nodes = {
		[1] = { children = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11} },
		[2] = { text = d[2], deact = {2,3,4,5}, act={6,7,8,9}, active=true, script = s2(2, nil)},
		[3] = { text = d[3], deact = {2,3,4,5}, act={6,7,8,9}, active=true, script = s2(3, nil)},
		[4] = { text = d[4], deact = {2,3,4,5}, act={6,7,8,9}, active=true, script = s2(4, 16)},
		[5] = { text = d[5], active=true, deact={2,3,4,5,6,7,8,9}, children ={10, 11}, script = 
			{
				{ type = scumm.action.say, args = { actor = "guybrush",  lines = {d[5]} }},
				{ type = scumm.action.say, args = { actor = "village2.citizen",  lines = {d[17]}, animstart="talk_e", animend="idle_e" }},
				s1
			}
		},
		[6] = { text = d[10], active = false, children ={10, 11}, script = 
			{
				{ type = scumm.action.say, args = {actor = "guybrush",  lines = {d[10]}}},
				{ type = scumm.action.say, args = {actor = "village2.citizen",  lines = {d[29], d[30], d[31], d[32]}, animstart="talk_e", animend="idle_e" }},
				s1
			},
		},
		[7] = { text = d[11], active = false, children ={10, 11}, script =
			{
				{ type = scumm.action.say, args = { actor = "guybrush",  lines = {d[11]} }},
				{ type = scumm.action.say, args = { actor = "village2.citizen",  lines = {d[33]}, animstart="talk_e", animend="idle_e" }},
				s1
			},
		},
		[8] = { text = d[12], active = false, script =
			{
				{ type = scumm.action.say, args={ actor = "guybrush",  lines = {d[12]} }},
				{ type = scumm.action.say, args={ actor = "village2.citizen",  lines = {d[29], d[30], d[31], d[32]}, animstart="talk_e", animend="idle_e" }},
				s1
			}
		},
		[9] = { text = d[13], active = false, script = 
			{
				{ type=scumm.action.say, args={actor = "guybrush",  lines = {d[13]} }},
				{ type=scumm.action.say, args={actor = "village2.citizen",  lines = {d[14], d[15]}, animstart="talk_e", animend="idle_e" }},
			}
		},
		[10] = { text = d[24], active = function() 
			return (variables.talked_about_map and (
				(variables.inventory["piece_of_eight"] == nil) or (variables.inventory["piece_of_eight"]<100)))
			end, script = {
				{ type=scumm.action.say, args={actor = "guybrush",  lines = {d[24]} }},
				{ type=scumm.action.say, args={actor = "village2.citizen",  lines = {d[26]}, animstart="talk_e", animend="idle_e" }},
			}
		},
		[11] = { text = d[25], active = function() 
			return (variables.talked_about_map and (
				(variables.inventory["piece_of_eight"] == nil) or (variables.inventory["piece_of_eight"]<100)))
			end, script = {
				{ type=scumm.action.say, args={actor = "guybrush",  lines = {d[25]} }},
				{ type=scumm.action.say, args={actor = "village2.citizen",  lines = {d[34], d[35]}, animstart="talk_e", animend="idle_e" }},
			}
		},

	}
}