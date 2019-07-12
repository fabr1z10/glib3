local d = strings.dialogues.pirates

engine.dialogues.importantpirates = {
	
	nodes = {
		[1] = { children = {2, 3, 4} },
		[2] = { text = d[2], active=true, script = {
				{ type = scumm.action.say, args = { actor = "guybrush",  lines = {d[2]} }},
				{ type = scumm.action.say, args = { actor = "scummbar.ilp1",  lines = {d[5]}}}
			}
		},
		[3] = { text = d[3], active=true, children = {5,6,7,8,9,10}, deact= {2,3,4}, act={5,6,7,8,9,10}, script = {
		 	{ type = scumm.action.say, args = { actor = "guybrush",  lines = {d[3]} }},
		 	{ type = scumm.action.say, args = { actor = "scummbar.ilp1",  lines = {d[6]} }},
		 	{ type = scumm.action.say, args = { actor = "scummbar.ilp2",  lines = {d[7]} }},
		 	{ type = scumm.action.say, args = { actor = "scummbar.ilp3",  lines = {d[8]} }},
		 	{ type = scumm.action.say, args = { actor = "scummbar.ilp1",  lines = {d[9]} }},
		 	{ type = scumm.action.say, args = { actor = "scummbar.ilp3",  lines = {d[10]} }},
		 	{ type = scumm.action.say, args = { actor = "scummbar.ilp1",  lines = {d[11], d[12]}}},
		 	{ type = scumm.action.say, args = { actor = "guybrush",  lines = {d[13]} }},
		 	{ type = scumm.action.say, args = { actor = "scummbar.ilp1",  lines = {d[14], d[15]}}},
		 	{ type = scumm.action.say, args = { actor = "scummbar.ilp3",  lines = {d[16]}}, ref = 1},
		 	{ type = scumm.action.say, args = { actor = "scummbar.ilp1",  lines = {d[17]}}, after={1} },
		 	{ type = scumm.action.say, args = { actor = "scummbar.ilp2",  lines = {d[17]}}, after={1} },
		 	{ type = scumm.action.say, args = { actor = "scummbar.ilp3",  lines = {d[17]}}, after={1} },
		 	{ type = scumm.action.say, args = { actor = "guybrush",  lines = {d[18], d[19]}, after={11,12,13} }},
		 	{ type = scumm.action.say, args = { actor = "scummbar.ilp2",  lines = {d[20]} }},
		 	{ type = scumm.action.say, args = { actor = "scummbar.ilp1",  lines = {d[21]} }},
		 	{ type = scumm.action.say, args = { actor = "scummbar.ilp2",  lines = {d[22]} }},
		 	{ type = scumm.action.say, args = { actor = "scummbar.ilp3",  lines = {d[23]} }},
		 	{ type = scumm.action.say, args = { actor = "scummbar.ilp2",  lines = {d[24]} }},
		 	{ type = scumm.action.say, args = { actor = "scummbar.ilp3",  lines = {d[25]} }},
		 	{ type = scumm.action.say, args = { actor = "scummbar.ilp2",  lines = {d[26], d[27], d[28], d[29]} }},
		 	{ type = scumm.action.say, args = { actor = "scummbar.ilp1",  lines = {d[30]} }, ref = 2},
		 	{ type = scumm.action.say, args = { actor = "scummbar.ilp1",  lines = {d[31]}}, after={2} },
		 	{ type = scumm.action.say, args = { actor = "scummbar.ilp2",  lines = {d[31]}}, after={2} },
		 	{ type = scumm.action.say, args = { actor = "scummbar.ilp3",  lines = {d[31]}}, after={2} },
		 	{ type = action.set_variable, args = { var="talked_to_important_pirates", value=true}}
		} },
		[4] = { text = d[4], active=true, script = {
			{ type = scumm.action.say, args = { actor = "guybrush", lines = {d[4]} }},
		 	{ type = scumm.action.say, args = { actor = "scummbar.ilp1",  lines = {d[5]} }}
			}
		},
		-- [5] = { text = d[32], active=false, deact={5}, act={11}, children = {5,11,6,12,7,13,8,9,10}, script = ms {
		-- 	{ action.say, { id = 1, actor = "guybrush",  lines = {d[32]} }},
		-- 	{ action.say, { id = 2, actor = "scummbar.ilp1",  lines = {d[42], d[43], d[44], d[45], d[46]}, animstart="talk", animend="idle" }},
		-- 	{ action.say, { id = 3, actor = "scummbar.ilp3",  lines = {d[47], d[48]}, animstart="talk", animend="idle" }},
		-- 	{ action.say, { id = 4, actor = "scummbar.ilp1",  lines = {d[49]}, animstart="talk", animend="idle", after={3} }},
		-- 	{ action.say, { id = 5, actor = "scummbar.ilp2",  lines = {d[49]}, animstart="talk", animend="idle", after={3} }},
		-- 	{ action.say, { id = 6, actor = "scummbar.ilp3",  lines = {d[49]}, animstart="talk", animend="idle", after={3} }},
		-- 	}
		-- },
		-- [6] = { text = d[33], active=false, deact={6}, act={12}, children = {5,11,6,12,7,13,8,9,10}, script = ms {
		-- 	{ action.say, { id = 1, actor = "guybrush",  lines = {d[33]} }},
		-- 	{ action.say, { id = 2, actor = "scummbar.ilp2",  lines = {d[52]}, animstart="talk", animend="idle" }},
		-- 	{ action.say, { id = 3, actor = "scummbar.ilp1",  lines = {d[53]}, animstart="talk", animend="idle" }},
		-- 	{ action.say, { id = 4, actor = "scummbar.ilp3",  lines = {d[54]}, animstart="talk", animend="idle" }},
		-- 	{ action.say, { id = 5, actor = "scummbar.ilp2",  lines = {d[55]}, animstart="talk", animend="idle" }},
		-- 	{ action.say, { id = 6, actor = "scummbar.ilp1",  lines = {d[56]}, animstart="talk", animend="idle" }},
		-- 	{ action.say, { id = 7, actor = "scummbar.ilp3",  lines = {d[57]}, animstart="talk", animend="idle" }},
		-- 	{ action.say, { id = 8, actor = "scummbar.ilp1",  lines = {d[58], d[59]}, animstart="talk", animend="idle" }},
		-- 	} 
		-- },
		-- [7] = { text = d[34], active=false, deact={7}, act={13}, children={5,11,6,12,7,13,8,9,10}, script = ms {
		-- 	{ action.say, { id = 1, actor = "guybrush",  lines = {d[34]} }},
		-- 	{ action.say, { id = 2, actor = "scummbar.ilp3",  lines = {d[61]}, animstart="talk", animend="idle" }},
		-- 	{ action.say, { id = 3, actor = "scummbar.ilp1",  lines = {d[62]}, animstart="talk", animend="idle" }},
		-- 	{ action.say, { id = 4, actor = "guybrush",  lines = {d[63]} }},
		-- 	{ action.say, { id = 5, actor = "scummbar.ilp1",  lines = {d[64]}, animstart="talk", animend="idle" }},
		-- 	{ action.say, { id = 6, actor = "scummbar.ilp2",  lines = {d[65], d[66]}, animstart="talk", animend="idle" }},
		-- 	{ action.say, { id = 7, actor = "scummbar.ilp1",  lines = {d[49]}, animstart="talk", animend="idle", after={6} }},
		-- 	{ action.say, { id = 8, actor = "scummbar.ilp2",  lines = {d[49]}, animstart="talk", animend="idle", after={6} }},
		-- 	{ action.say, { id = 9, actor = "scummbar.ilp3",  lines = {d[49]}, animstart="talk", animend="idle", after={6} }},
		-- 	} 
		-- },
		-- [8] = { text = d[35], active=false, deact={8}, children = {5,11,6,12,7,13,8,9,10}, script = ms {
		-- 	{ action.say, { id = 1, actor = "guybrush",  lines = {d[35]} }},
		-- 	{ action.say, { id = 2, actor = "scummbar.ilp1",  lines = {d[68]}, animstart="talk", animend="idle" }},
		-- 	}
		--  },
		-- [9] = { text = d[36], active=false, deact={9}, children = {5,11,6,12,7,13,8,9,10}, script= ms {
		-- 	{ action.say, { id = 1, actor = "guybrush",  lines = {d[36]} }},
		-- 	{ action.say, { id = 2, actor = "scummbar.ilp2",  lines = {d[69]}, animstart="talk", animend="idle" }},
		-- 	{ action.say, { id = 3, actor = "scummbar.ilp1",  lines = {d[70]}, animstart="talk", animend="idle" }},
		-- 	{ action.say, { id = 4, actor = "scummbar.ilp2",  lines = {d[71]}, animstart="talk", animend="idle" }},
		-- 	{ action.say, { id = 5, actor = "scummbar.ilp3",  lines = {d[72]}, animstart="talk", animend="idle" }},
		-- 	{ action.say, { id = 6, actor = "scummbar.ilp1",  lines = {d[73]}, animstart="talk", animend="idle" }},
		-- 	{ action.say, { id = 7, actor = "scummbar.ilp2",  lines = {d[74]}, animstart="talk", animend="idle" }},
		-- 	{ action.say, { id = 8, actor = "scummbar.ilp3",  lines = {d[75]}, animstart="talk", animend="idle" }},
		-- 	{ action.say, { id = 9, actor = "scummbar.ilp1",  lines = {d[76]}, animstart="talk", animend="idle" }},
		-- 	{ action.say, { id = 10, actor = "scummbar.ilp2",  lines = {d[77]}, animstart="talk", animend="idle" }},
		-- 	{ action.say, { id = 11, actor = "scummbar.ilp3",  lines = {d[78]}, animstart="talk", animend="idle" }},
		-- 	{ action.say, { id = 12, actor = "scummbar.ilp1",  lines = {d[79]}, animstart="talk", animend="idle" }},
		-- 	{ action.say, { id = 13, actor = "scummbar.ilp2",  lines = {d[80], d[81]}, animstart="talk", animend="idle" }},
		-- 	{ action.say, { id = 14, actor = "scummbar.ilp1",  lines = {d[82]}, animstart="talk", animend="idle" }},
		-- 	{ action.say, { id = 15, actor = "scummbar.ilp1",  lines = {d[49]}, animstart="talk", animend="idle", after={14} }},
		-- 	{ action.say, { id = 16, actor = "scummbar.ilp2",  lines = {d[49]}, animstart="talk", animend="idle", after={14} }},
		-- 	{ action.say, { id = 17, actor = "scummbar.ilp3",  lines = {d[49]}, animstart="talk", animend="idle", after={14} }},
		-- 	}
		--  },
		-- [10] = { text = d[37], active=false, script = ms {
		-- 	{ action.say, { id = 1, actor = "guybrush",  lines = {d[37]} }},
		-- 	{ action.say, { id = 2, actor = "scummbar.ilp1",  lines = {d[38]}, animstart="talk", animend="idle" }},
		-- 	{ action.say, { id = 3, actor = "scummbar.ilp2",  lines = {d[39]}, animstart="talk", animend="idle" }}
		-- 	}
		-- },
		-- [11] = { text= d[50], active=false, children = {5,11,6,12,7,13,8,9,10}, script = ms {
		-- 	{ action.say, { id = 1, actor = "guybrush",  lines = {d[50]} }},
		-- 	{ action.say, { id = 2, actor = "scummbar.ilp1",  lines = {d[42], d[43], d[44]}, animstart="talk", animend="idle" }},
		-- 	{ action.say, { id = 3, actor = "scummbar.ilp3",  lines = {d[51]}, animstart="talk", animend="idle" }},
		-- 	}
		-- },
		-- [12] = { text= d[60], active=false, children = {5,11,6,12,7,13,8,9,10}, script = ms {
		-- 	{ action.say, { id = 1, actor = "guybrush",  lines = {d[60]} }},
		-- 	{ action.say, { id = 2, actor = "scummbar.ilp2",  lines = {d[55]}, animstart="talk", animend="idle" }},
		-- 	{ action.say, { id = 3, actor = "scummbar.ilp1",  lines = {d[56]}, animstart="talk", animend="idle" }},
		-- 	{ action.say, { id = 4, actor = "scummbar.ilp3",  lines = {d[57]}, animstart="talk", animend="idle" }},
		-- 	{ action.say, { id = 5, actor = "scummbar.ilp1",  lines = {d[58], d[59]}, animstart="talk", animend="idle" }},
		-- 	}
		-- },
		-- [13] = { text= d[67], active=false, children = {5,11,6,12,7,13,8,9,10}, script = ms {
		-- 	{ action.say, { id = 1, actor = "guybrush",  lines = {d[67]} }},
		-- 	{ action.say, { id = 2, actor = "scummbar.ilp1",  lines = {d[62]}, animstart="talk", animend="idle" }},
		-- 	{ action.say, { id = 3, actor = "scummbar.ilp2",  lines = {d[65], d[66]}, animstart="talk", animend="idle" }},
		-- 	{ action.say, { id = 4, actor = "scummbar.ilp1",  lines = {d[49]}, animstart="talk", animend="idle", after={3} }},
		-- 	{ action.say, { id = 5, actor = "scummbar.ilp2",  lines = {d[49]}, animstart="talk", animend="idle", after={3} }},
		-- 	{ action.say, { id = 6, actor = "scummbar.ilp3",  lines = {d[49]}, animstart="talk", animend="idle", after={3} }},
		-- 	} 

		-- }
	}
}