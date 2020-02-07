local d = strings.dialogues.lookout

local initDialogue = function(n) 
	return function() 
		local actions = {
			{ type = scumm.action.say, args = {actor="guybrush", lines = {d[n]}}},
			{ type = scumm.action.turn, args = {tag = "lookout.lookout", dir="south"}},
		}
		if not variables.talked_to_lookout then
			variables.talked_to_lookout = true
			table.insert (actions, { type = scumm.action.say, args = {actor="lookout.lookout", lines = {d[5], d[6], d[7], d[8], d[9]}}})
		else
			table.insert (actions, { type = scumm.action.say, args = {actor="lookout.lookout", lines = {d[5], d[43]}}})
		end
		return actions
	end
end

local lookout_turn = {
	{ type = scumm.action.turn, args = {tag = "lookout.lookout", dir="east"}},
	{ type = scumm.action.say, args = {actor="lookout.lookout", lines = {d[15], d[16]}}},
}

engine.dialogues.lookout = {
	-- root
	init = function()
		engine.dialogues.lookout.nodes[8].active = true 
	end,
	close = function(n)
		local actions = {
			{ type = scumm.action.turn, args = {tag = "lookout.lookout", dir ="west"}}
		}
		local s = script.make(actions)
		monkey.play(s)
	end,
	nodes = {
		[1] = { children = {2, 3, 4, 5 }},
		[2] = { text = d[1], active=true, script = initDialogue(1), children ={6,7,12,8,9,10,14,15}},
		[3] = { text = d[2], active=true, script = initDialogue(2), children ={6,7,12,8,9,10,14,15}},
		[4] = { text = d[3], active=true, script = initDialogue(3), children ={6,7,12,8,9,10,14,15}},
		[5] = { text = d[4], active=true, script = initDialogue(4), children ={6,7,12,8,9,10,14,15}},
		[6] = { text = d[10], active =true,
		 	script = { 
		 		{ type = scumm.action.say, args = { actor="guybrush", lines = {d[10],d[17]} }}, 
		 		{ type = scumm.action.say, args = { actor="lookout.lookout", lines = {d[18], d[19], d[20], d[21]} }} 
		 	},
		 	children = {11,12,8,9,10},
		 	deact = { 6, 7 }, act ={12} 
		},
		[7] = { text = d[11], active=true, script = {
				{ type = scumm.action.say, args = { actor="guybrush", lines = {d[11]}}},
		 		{ type = scumm.action.say, args = { actor="lookout.lookout", lines = {d[41]}}}
		 	},
		 	deact ={6, 7,12}, 
		 	act = {13},
		 	children = {13, 8, 9, 10} 
		},
		[8] = { text = d[12], active=true, script = lookout_turn, deact= {8}, children ={6,7,12,9,10} },
		[9] = { text = d[13], active=true, script = {
				{ type = scumm.action.say, args = { actor="guybrush", lines = {d[13]}}},
		 		{ type = scumm.action.say, args = { actor="lookout.lookout", lines = {d[30], d[31], d[32]}}}
		 	},
		 	children = {14,15,16,10},
		 	deact={6,7,8,9},
		 	act={14, 15}
		},		
		-- leave
		[10] = { text = d[14], active=true, script = {
				{ type = scumm.action.say, args = { actor="guybrush", lines = {d[14]}}},
		 		{ type = scumm.action.say, args = { actor="lookout.lookout", lines = {d[42]}}}
			}
		},
		[11] = { text = d[22], active=true, script = {
				{ type = scumm.action.say, args = { actor="guybrush", lines = {d[22]}}},
		 		{ type = scumm.action.say, args = { actor="lookout.lookout", lines = {d[23], d[24], d[25], d[26], d[27]}}}
		 	},
		 	children = {}
		},
		-- 2nd version of call me squinky
		[12] = { text = d[11], active=false, deact= {12, 7}, script = { 
				{ type = scumm.action.say, args = { actor="guybrush", lines = {d[11]}}},
		 		{ type = scumm.action.say, args = { actor="lookout.lookout", lines = {d[27]}}},
				{ type = scumm.action.say, args = { actor="guybrush", lines = {d[28]}}},
		 		{ type = scumm.action.say, args = { actor="lookout.lookout", lines = {d[29]}}}
		 	},
		 	children = {8, 9, 10}  
		},
		[13] = { text = d[48], active=false, deact= {13}, script = { 
				{ type = scumm.action.say, args = { actor="guybrush", lines = {d[48], d[17]}}},
		 		{ type = scumm.action.say, args = { actor="lookout.lookout", lines = {d[18], d[19], d[20], d[21], d[51]}}}
		 	},
		 	children = {8, 9, 10}
		},
		[14] = { text=d[34], active=false, script = {
				{ type = scumm.action.say, args = { actor="guybrush", lines = {d[34]}}},
		 		{ type = scumm.action.say, args = { actor="lookout.lookout", lines = {d[35], d[36], d[37]}}}
			},
		 	children = {15, 10},
		 	deact = {14} 
		},
		[15] = { text=d[38], active=false, script = {
				{ type = scumm.action.say, args = { actor="guybrush", lines = {d[38]}}},
		 		{ type = scumm.action.say, args = { actor="lookout.lookout", lines = {d[39], d[40]}}}
			},
		 	children = {14, 10},
		 	deact = {15} 
		},
		[16] = { text=d[52]},
		-- [17] = { text = d[1], active=false, script = curry(script.lookout.init_dialogue_2, 1), children ={6,7,12,8,9,10,14,15} },
		-- [18] = { text = d[2], active=false, script = curry(script.lookout.init_dialogue_2, 2), children ={6,7,12,8,9,10,14,15} },
		-- [19] = { text = d[3], active=false, script = curry(script.lookout.init_dialogue_2, 3), children ={6,7,12,8,9,10,14,15} },
		-- [20] = { text = d[4], active=false, script = curry(script.lookout.init_dialogue_2, 4), children ={6,7,12,8,9,10,14,15} },

	}
}