local d = strings.dialogues.troll

dialogues.troll = {
	close = function()
		local s = script:new("_citizenclose")
		s.actions = {
			action.resume_script {id=1, script="_troll"},
		}
		monkey.play(s)
	end,
	nodes = {
		[1] = { children = {2, 3, 4, 19, 5, 6} },
		[2] = { text = d[4], deact={2}, active=true, children = {7,8,9,10}, script = ms {
			{ action.say, {id=1, actor="guybrush", lines = {d[4]}}},
			{ action.say, {id=2, actor="bridge.troll", lines = {d[9], d[10], d[11]}, animstart="idle", animend="idle"}},
		}},
		[3] = { text = d[5], deact={3}, active=true, script = ms {
			{ action.say, {id=1, actor="guybrush", lines = {d[5]}}},
			{ action.say, {id=2, actor="bridge.troll", lines = {d[19], d[20]}, animstart="idle", animend="idle"}},
		}},
		[4] = { text = d[6], deact={4}, act={19}, active=true, children = {11,12,13}, script = ms {
			{ action.say, {id=1, actor="guybrush", lines = {d[6]}}},
			{ action.say, {id=2, actor="bridge.troll", lines = {d[21]}, animstart="idle", animend="idle"}},
		}},
		[5] = { text = d[7], active=true, deact={7}, script = ms {
			{ action.say, {id=1, actor="guybrush", lines = {d[7]}}},
			{ action.say, {id=2, actor="bridge.troll", lines = {d[34], d[35]}, animstart="idle", animend="idle"}},
		}},
		[6] = { text = d[8], active=true, script = ms {
			{ action.say, {id=1, actor="guybrush", lines = {d[8]}}},
			{ action.say, {id=2, actor="bridge.troll", lines = {d[39]}, animstart="idle", animend="idle"}},
		}},
		[7] = { text = d[12], active=true, script = ms {
			{ action.say, {id=1, actor="guybrush", lines = {d[12]}}},
			{ action.say, {id=2, actor="bridge.troll", lines = {d[16], d[17]}, animstart="idle", animend="idle"}},
		}},
		[8] = { text = d[13], active=true, script = ms {
			{ action.say, {id=1, actor="guybrush", lines = {d[13]}}},
			{ action.say, {id=2, actor="bridge.troll", lines = {d[40], d[41]}, animstart="idle", animend="idle"}},
		}},
		[9] = { text = d[14], active=true, script = ms {
			{ action.say, {id=1, actor="guybrush", lines = {d[14]}}},
			{ action.say, {id=2, actor="bridge.troll", lines = {d[42], d[43], d[44], d[45], d[46]}, animstart="idle", animend="idle"}},
		}},
		[10] = { text = d[15], active=true, script = ms {
			{ action.say, {id=1, actor="guybrush", lines = {d[15]}}},
			{ action.say, {id=2, actor="bridge.troll", lines = {d[47]}, animstart="idle", animend="idle"}},
		}},
		[11] = { text = d[22], deact={2}, active=true, children = {7,8,9,10}, script = ms {
			{ action.say, {id=1, actor="guybrush", lines = {d[4]}}},
			{ action.say, {id=2, actor="bridge.troll", lines = {d[9], d[10], d[11]}, animstart="idle", animend="idle"}},
		}},
		[12] = { text = d[23], active=true, children = {14,15,16,17,18}, script = ms {
			{ action.say, {id=1, actor="guybrush", lines = {d[23]}}},
			{ action.say, {id=2, actor="bridge.troll", lines = {d[25]}, animstart="idle", animend="idle"}},
		}},
		[13] = { text = d[24], active=true, script = ms {
			{ action.say, {id=1, actor="guybrush", lines = {d[24]}}},
			{ action.say, {id=2, actor="bridge.troll", lines = {d[36], d[37]}, animstart="idle", animend="idle"}},
		}},
		[14] = { text = d[26], deact={14,15,16,17,18}, active=true, script = ms {
			{ action.say, {id=1, actor="guybrush", lines = {d[26]}}},
			{ action.say, {id=2, actor="bridge.troll", lines = {d[31], d[32], d[33]}, animstart="idle", animend="idle"}},
		}},
		[15] = { text = d[27], deact={14,15,16,17,18}, active=true, script = ms {
			{ action.say, {id=1, actor="guybrush", lines = {d[27]}}},
			{ action.say, {id=2, actor="bridge.troll", lines = {d[31], d[32], d[33]}, animstart="idle", animend="idle"}},
		}},
		[16] = { text = d[28], deact={14,15,16,17,18}, active=true, script = ms {
			{ action.say, {id=1, actor="guybrush", lines = {d[28]}}},
			{ action.say, {id=2, actor="bridge.troll", lines = {d[31], d[32], d[33]}, animstart="idle", animend="idle"}},
		}},
		[17] = { text = d[29], deact={14,15,16,17,18}, active=true, script = ms {
			{ action.say, {id=1, actor="guybrush", lines = {d[29]}}},
			{ action.say, {id=2, actor="bridge.troll", lines = {d[31], d[32], d[33]}, animstart="idle", animend="idle"}},
		}},
		[18] = { text = d[30], deact={14,15,16,17,18}, active=true, script = ms {
			{ action.say, {id=1, actor="guybrush", lines = {d[30]}}},
			{ action.say, {id=2, actor="bridge.troll", lines = {d[31], d[32], d[33]}, animstart="idle", animend="idle"}},
		}},
		[19] = {text=d[38], active=false, children = {14,15,16,17,18}, script = ms {
			{ action.say, {id=1, actor="guybrush", lines = {d[38]}}},
			{ action.say, {id=2, actor="bridge.troll", lines = {d[25]}, animstart="idle", animend="idle"}},
		}},

	}
}