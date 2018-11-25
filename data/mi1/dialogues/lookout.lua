dialogues.lookout = {
	-- root
	init = function()
		room.dialogues.lookout.nodes[8].active = true 
	end,
	nodes = {
		[1] = { children = {2, 3, 4, 5} },
		[2] = { text = d[1], active=true, script = curry(room.scripts.ciaooo, 1), children ={6,7,12,8,9,10,14,15} },
		[3] = { text = d[2], active=true, script = curry(room.scripts.ciaooo, 2), children ={6,7,12,8,9,10,14,15} },
		[4] = { text = d[3], active=true, script = curry(room.scripts.ciaooo, 3), children ={6,7,12,8,9,10,14,15} },
		[5] = { text = d[4], active=true, script = curry(room.scripts.ciaooo, 4), children ={6,7,12,8,9,10,14,15} },
		[6] = { text = d[10], active =true,
			script = curry(make_dialogue, { 
				{objects.guybrush, {d[10],d[17]} }, 
				{room.items.lookout, {d[18], d[19], d[20], d[21]} } 
			}),
			children = {11,12,8,9,10},
			deact = { 6, 7 }, act ={12} },
		[7] = { text = d[11], active=true, script = curry(make_dialogue, {
				{objects.guybrush, {d[11]}},
				{room.items.lookout, {d[41]}}
			}),
			deact ={6, 7,12}, 
			act = {13},
			children = {13, 8, 9} },
		[8] = { text = d[12], active=true, script = room.scripts.lookout_turn, deact= {8}, children ={6,7,12,9,10} },
		[9] = { text = d[13], active=true, script = curry(make_dialogue, {
				{ objects.guybrush, {d[13]}},
				{ room.items.lookout, {d[30], d[31], d[32], d[33]}},
			}),
			children = {14,15,16,10},
			deact={6,7,8,9},
			act={14, 15}
		},
		
		-- leave
		[10] = { text = d[14], active=true, script = curry(make_dialogue, {{objects.guybrush, {d[14]}}}) },
		[11] = { text = d[22], active=true, script = curry(make_dialogue, {
				{ objects.guybrush, {d[11]}},
				{ room.items.lookout, {d[23], d[24], d[25], d[26], d[27]}},
			}),
			children = {}
		},
		-- 2nd version of call me squinky
		[12] = { text = d[11], active=false, deact= {12, 7},
			script = curry(make_dialogue, { 
				{objects.guybrush, {d[11]}}, 
				{room.items.lookout, {d[27]}},
				{objects.guybrush, {d[28]}},
				{room.items.lookout, {d[29]}}
			}),
			children = {8, 9, 10}  
		},
		[13] = { text = d[48], active=false, deact= {13},
			script = curry(make_dialogue, { 
				{objects.guybrush, {d[13],d[17]} }, 
				{room.items.lookout, {d[18], d[19], d[20], d[21], d[51]} } 
			}),
			children = {8, 9, 10}
		},
		[14] = { text=d[34], active=false, script = curry(make_dialogue, {
				{objects.guybrush, {d[34]} }, 
				{room.items.lookout, {d[35], d[36], d[37]}}
			}),
			children = {15, 10},
			deact = {14} 
		},
		[15] = { text=d[38], active=false, script = curry(make_dialogue, {
				{objects.guybrush, {d[38]} }, 
				{room.items.lookout, {d[39], d[40] }}
			}),
			children = {14, 10},
			deact = {15} 
		},
		[16] = { text=d[52]} 
	}
}