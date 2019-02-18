local d = strings.dialogues.citizen

local s1 = {
	{ type = action.say, args = { actor = "village2.citizen",  lines = {d[18]}, animstart="talk_start", animend="talk_end" }},
	{ ref = 2, type = action.animate, args = { id = 2, actor="village2.citizen", anim="open_jacket"}},
	{ ref = 3, type = action.say, after= {2}, args = { actor="village2.citizen", lines = {d[19]}, animstart="talk_start", animend="talk_end"}},
	{ ref = 4, type = action.delay, after= {2}, args = {sec= 2}},
	{ type = action.animate, after = {3,4}, args = {actor="village2.citizen", anim="open_jacket", fwd = false}},
    { type = action.say, after= {3,4}, args = {actor="village2.citizen", lines = {d[20]}, animstart="talk_start", animend="talk_end"}},
	{ type = action.animate, args = {actor="village2.citizen", anim="rollmap"}},
	{ type = action.say, args = {actor="village2.citizen", lines = {d[21], d[22]}, animstart="talk_start", animend="talk_end"}},
	{ type = action.animate, args = {actor="village2.citizen", anim="rollmap", fwd=false, sync = true}},
	{ type = action.say, args = {actor="village2.citizen", lines = {d[23]}, animstart="talk_start", animend="talk_end"}},
	{ type = action.set_variable, args = { var = "talked_to_citizen", value=true}},
	{ type = action.set_variable, args = { var="talked_about_map", value=true}}	
}

local s2 = function(n, k) 
	local lines = k and {d[k], d[6], d[7]} or {d[6], d[7]}
	return {
		{ type = action.say, args = { actor = "guybrush",  lines = {d[n]} }},
		{ type = action.say, args = { actor = "village2.citizen",  lines = lines, animstart="talk_start", animend="talk_end" }},
		{ type = action.set_variable, args = { var = "talked_to_citizen", value=true}}
	}
end

dialogues.citizen = {
	close = function()
		local actions = {
			{ type = action.animate, args = {actor="village2.citizen", anim="idle_s"}}
		}
		local s = ms2(actions) 
		monkey.play(s)
	end,
	nodes = {
		[1] = { children = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11} },
		[2] = { text = d[2], deact = {2,3,4,5}, act={6,7,8,9}, active=true, script = s2(2, nil)},
		[3] = { text = d[3], deact = {2,3,4,5}, act={6,7,8,9}, active=true, script = s2(3, nil)},
		[4] = { text = d[4], deact = {2,3,4,5}, act={6,7,8,9}, active=true, script = s2(4, 16)},
		[5] = { text = d[5], active=true, deact={2,3,4,5,6,7,8,9}, children ={10, 11}, script = 
			{
				{ type = action.say, args = { actor = "guybrush",  lines = {d[5]} }},
				{ type = action.say, args = { actor = "village2.citizen",  lines = {d[17]}, animstart="talk_start", animend="talk_end" }},
				s1
			}
		},
		[6] = { text = d[10], active = false, children ={10, 11}, script = msc {
			{
				{ action.say, { id = 1, actor = "guybrush",  lines = {d[10]} }},
				{ action.say, { id = 2, actor = "village2.citizen",  lines = {d[29], d[30], d[31], d[32]}, animstart="talk_start", animend="talk_end" }},
			},
			s1}
		},
		[7] = { text = d[11], active = false, children ={10, 11}, script = msc {
			{
				{ action.say, { id = 1, actor = "guybrush",  lines = {d[11]} }},
				{ action.say, { id = 2, actor = "village2.citizen",  lines = {d[33]}, animstart="talk_start", animend="talk_end" }},
			},
			s1}
		},
		[8] = { text = d[12], active = false, script = msc {
			{
				{ action.say, { id = 1, actor = "guybrush",  lines = {d[12]} }},
				{ action.say, { id = 2, actor = "village2.citizen",  lines = {d[29], d[30], d[31], d[32]}, animstart="talk_start", animend="talk_end" }},
			},
			s1}
		},
		[9] = { text = d[13], active = false, script = ms {
			{ action.say, { id = 1, actor = "guybrush",  lines = {d[13]} }},
			{ action.say, { id = 2, actor = "village2.citizen",  lines = {d[14], d[15]}, animstart="talk_start", animend="talk_end" }},
			}
		},
		[10] = { text = d[24], active = function() 
			return (variables.talked_about_map and (
				(variables.inventory["piece_of_eight"] == nil) or (variables.inventory["piece_of_eight"]<100)))
			end, script = ms {
				{ action.say, { id = 1, actor = "guybrush",  lines = {d[24]} }},
				{ action.say, { id = 2, actor = "village2.citizen",  lines = {d[26]}, animstart="talk_start", animend="talk_end" }},
			}
		},
		[11] = { text = d[25], active = function() 
			return (variables.talked_about_map and (
				(variables.inventory["piece_of_eight"] == nil) or (variables.inventory["piece_of_eight"]<100)))
			end, script = ms {
				{ action.say, { id = 1, actor = "guybrush",  lines = {d[25]} }},
				{ action.say, { id = 2, actor = "village2.citizen",  lines = {d[34], d[35]}, animstart="talk_start", animend="talk_end" }},
			}
		},

	}
}