local d = strings.dialogues.pirates

dialogues.importantpirates = {
	
	nodes = {
		[1] = { children = {2, 3, 4,5,6,7,8,9,10} },
		[2] = { text = d[2], active=true, script = ms {
			{ action.say, { id = 1, actor = "guybrush",  lines = {d[2]} }},
			{ action.say, { id = 2, actor = "scummbar.ilp1",  lines = {d[5]}, animstart="talk", animend="idle" }}
			}
		},
		[3] = { text = d[3], active=true, children = {5,6,7,8,9,10}, deact={2,3,4}, act={5,6,7,8,9,10}, script = ms {
			{ action.say, { id = 1, actor = "guybrush",  lines = {d[3]} }},
			{ action.say, { id = 2, actor = "scummbar.ilp1",  lines = {d[6]}, animstart="talk", animend="idle" }},
			{ action.say, { id = 3, actor = "scummbar.ilp2",  lines = {d[7]}, animstart="talk", animend="idle" }},
			{ action.say, { id = 4, actor = "scummbar.ilp3",  lines = {d[8]}, animstart="talk", animend="idle" }},
			{ action.say, { id = 5, actor = "scummbar.ilp1",  lines = {d[9]}, animstart="talk", animend="idle" }},
			{ action.say, { id = 6, actor = "scummbar.ilp3",  lines = {d[10]}, animstart="talk", animend="idle" }},
			{ action.say, { id = 7, actor = "scummbar.ilp1",  lines = {d[11], d[12]}, animstart="talk", animend="idle" }},
			{ action.say, { id = 8, actor = "guybrush",  lines = {d[13]} }},
			{ action.say, { id = 9, actor = "scummbar.ilp1",  lines = {d[14], d[15]}, animstart="talk", animend="idle" }},
			{ action.say, { id = 10, actor = "scummbar.ilp3",  lines = {d[16]}, animstart="talk", animend="idle" }},
			{ action.say, { id = 11, actor = "scummbar.ilp1",  lines = {d[17]}, animstart="talk", animend="idle", after={10} }},
			{ action.say, { id = 12, actor = "scummbar.ilp2",  lines = {d[17]}, animstart="talk", animend="idle", after={10} }},
			{ action.say, { id = 13, actor = "scummbar.ilp3",  lines = {d[17]}, animstart="talk", animend="idle", after={10} }},
			{ action.say, { id = 14, actor = "guybrush",  lines = {d[18], d[19]}, after={11,12,13} }},
			{ action.say, { id = 15, actor = "scummbar.ilp2",  lines = {d[20]}, animstart="talk", animend="idle" }},
			{ action.say, { id = 16, actor = "scummbar.ilp1",  lines = {d[21]}, animstart="talk", animend="idle" }},
			{ action.say, { id = 17, actor = "scummbar.ilp2",  lines = {d[22]}, animstart="talk", animend="idle" }},
			{ action.say, { id = 18, actor = "scummbar.ilp3",  lines = {d[23]}, animstart="talk", animend="idle" }},
			{ action.say, { id = 19, actor = "scummbar.ilp2",  lines = {d[24]}, animstart="talk", animend="idle" }},
			{ action.say, { id = 20, actor = "scummbar.ilp3",  lines = {d[25]}, animstart="talk", animend="idle" }},
			{ action.say, { id = 21, actor = "scummbar.ilp2",  lines = {d[26], d[27], d[28], d[29]}, animstart="talk", animend="idle" }},
			{ action.say, { id = 22, actor = "scummbar.ilp1",  lines = {d[30]}, animstart="talk", animend="idle" }},
			{ action.say, { id = 23, actor = "scummbar.ilp1",  lines = {d[31]}, animstart="talk", animend="idle", after={22} }},
			{ action.say, { id = 24, actor = "scummbar.ilp2",  lines = {d[31]}, animstart="talk", animend="idle", after={22} }},
			{ action.say, { id = 25, actor = "scummbar.ilp3",  lines = {d[31]}, animstart="talk", animend="idle", after={22} }},
		} },
		[4] = { text = d[4], active=true, script = ms {
			{ action.say, { id = 1, actor = "guybrush",  lines = {d[4]} }},
			{ action.say, { id = 2, actor = "scummbar.ilp1",  lines = {d[5]}, animstart="talk", animend="idle" }}
			}
		},
		[5] = { text = d[32], active=false },
		[6] = { text = d[33], active=false },
		[7] = { text = d[34], active=false },
		[8] = { text = d[35], active=false },
		[9] = { text = d[36], active=false },
		[10] = { text = d[37], active=false, script = ms {
			{ action.say, { id = 1, actor = "guybrush",  lines = {d[37]} }},
			{ action.say, { id = 2, actor = "scummbar.ilp1",  lines = {d[38]}, animstart="talk", animend="idle" }},
			{ action.say, { id = 3, actor = "scummbar.ilp2",  lines = {d[39]}, animstart="talk", animend="idle" }}
			}
		},
	}
}