local d = strings.dialogues.lookout

dialogues.lookout = {
	-- root
	init = function()
		dialogues.lookout.nodes[8].active = true 
	end,
	close = function(n)
		local s = script:new()
		s.actions = {
			[1] = { type="turn", actor = "lookout", dir ="west"}, 
		}
		monkey.play(s)
	end,
	nodes = {
		[1] = { children = {2, 3, 4, 5, 17, 18, 19, 20} },
		[2] = { text = d[1], active=true, script = curry(script.lookout.init_dialogue, 1), children ={6,7,12,8,9,10,14,15}, deact={2,3,4,5}, act={17,18,19,20} },
		[3] = { text = d[2], active=true, script = curry(script.lookout.init_dialogue, 2), children ={6,7,12,8,9,10,14,15}, deact={2,3,4,5}, act={17,18,19,20} },
		[4] = { text = d[3], active=true, script = curry(script.lookout.init_dialogue, 3), children ={6,7,12,8,9,10,14,15}, deact={2,3,4,5}, act={17,18,19,20} },
		[5] = { text = d[4], active=true, script = curry(script.lookout.init_dialogue, 4), children ={6,7,12,8,9,10,14,15}, deact={2,3,4,5}, act={17,18,19,20} },
		[6] = { text = d[10], active =true,
			script = curry(make_dialogue, { 
				{items.guybrush, {d[10],d[17]} }, 
				{items.lookout.lookout, {d[18], d[19], d[20], d[21]} } 
			}),
			children = {11,12,8,9,10},
			deact = { 6, 7 }, act ={12} },
		[7] = { text = d[11], active=true, script = curry(make_dialogue, {
				{items.guybrush, {d[11]}},
				{items.lookout.lookout, {d[41]}}
			}),
			deact ={6, 7,12}, 
			act = {13},
			children = {13, 8, 9, 10} },
		[8] = { text = d[12], active=true, script = script.lookout.turn, deact= {8}, children ={6,7,12,9,10} },
		[9] = { text = d[13], active=true, script = curry(make_dialogue, {
				{ items.guybrush, {d[13]}},
				{ items.lookout.lookout, {d[30], d[31], d[32], d[33]}},
			}),
			children = {14,15,16,10},
			deact={6,7,8,9},
			act={14, 15}
		},
		
		-- leave
		[10] = { text = d[14], active=true, script = curry(make_dialogue, {
			{items.guybrush, {d[14]}},
			{items.lookout.lookout, {d[42]}}
		}) },
		[11] = { text = d[22], active=true, script = curry(make_dialogue, {
				{ items.guybrush, {d[11]}},
				{ items.lookout.lookout, {d[23], d[24], d[25], d[26], d[27]}},
			}),
			children = {}
		},
		-- 2nd version of call me squinky
		[12] = { text = d[11], active=false, deact= {12, 7},
			script = curry(make_dialogue, { 
				{items.guybrush, {d[11]}}, 
				{items.lookout.lookout, {d[27]}},
				{items.guybrush, {d[28]}},
				{items.lookout.lookout, {d[29]}}
			}),
			children = {8, 9, 10}  
		},
		[13] = { text = d[48], active=false, deact= {13},
			script = curry(make_dialogue, { 
				{items.guybrush, {d[48],d[17]} }, 
				{items.lookout.lookout, {d[18], d[19], d[20], d[21], d[51]} } 
			}),
			children = {8, 9, 10}
		},
		[14] = { text=d[34], active=false, script = curry(make_dialogue, {
				{items.guybrush, {d[34]} }, 
				{items.lookout.lookout, {d[35], d[36], d[37]}}
			}),
			children = {15, 10},
			deact = {14} 
		},
		[15] = { text=d[38], active=false, script = curry(make_dialogue, {
				{items.guybrush, {d[38]} }, 
				{items.lookout.lookout, {d[39], d[40] }}
			}),
			children = {14, 10},
			deact = {15} 
		},
		[16] = { text=d[52]},
		[17] = { text = d[1], active=false, script = curry(script.lookout.init_dialogue_2, 1), children ={6,7,12,8,9,10,14,15} },
		[18] = { text = d[2], active=false, script = curry(script.lookout.init_dialogue_2, 2), children ={6,7,12,8,9,10,14,15} },
		[19] = { text = d[3], active=false, script = curry(script.lookout.init_dialogue_2, 3), children ={6,7,12,8,9,10,14,15} },
		[20] = { text = d[4], active=false, script = curry(script.lookout.init_dialogue_2, 4), children ={6,7,12,8,9,10,14,15} },

	}
}