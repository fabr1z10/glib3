local d = strings.dialogues.lowmoralfiber

local s1 = {
	{ action.say, {id=1, actor="village2.lmf1", lines={d[11]}, animstart="talk", animend="idle2"}},
	{ action.say, {id=2, actor="village2.lmf2", lines={d[12]}, animstart="laugh"}},
	{ action.animate_once, {id=3, actor="village2.lmf3", anim="punch1"}},
	{ action.animate_once, {id=4, actor="village2.lmf3", anim="punch2", after={3}}},
	{ action.animate_once, {id=5, actor="village2.lmf2", anim="hit", after={3}}},
	{ action.animate, {id=6, actor="village2.lmf2", anim="idle", after={5}}},
	{ action.animate, {id=7, actor="village2.lmf3", anim="idle", after={4}}},
	{ action.say, {id=8, actor="village2.lmf1", lines={d[13]}, animstart="looknorth", animend="idle2"}},
	{ action.say, {id=9, actor="village2.lmf1", lines={d[14]}, animstart="talk", animend="idle2"}},
	{ action.say, {id=10, actor="village2.lmf3", lines={d[15]}, animstart="talkfront", animend="idle"}},
	{ action.say, {id=11, actor="village2.lmf3", lines={d[16]}, animstart="talk", animend="idle"}},
}

dialogues.lowmoralfiber = {
	close = function()
		-- local s = script:new("_citizenclose")
		-- s.actions = {
		-- 	action.animate {id=1,actor="village2.citizen", anim="idle"}
		-- }
		-- monkey.play(s)
	end,
	nodes = {
		[1] = { children = {2, 20, 3, 4, 15, 19, 5, 6} },
		[2] = { text = d[1], active=true, deact={2, 3}, children = {7,8,9,10}, script = ms {
			{ action.say, {id=1, actor="guybrush", lines={d[1]}}},
			{ action.say, {id=2, actor="village2.lmf1", lines={d[6]}, animstart="talk", animend="idle2"}},			
		}},
		[3] = { text = d[2], active=true, deact={3}, script = ms {
			{ action.say, {id=1, actor="guybrush", lines={d[2]}}},		
			{ action.say, {id=2, actor="village2.rat", lines={d[34], d[35]}, animate=false}},		
			{ action.say, {id=3, actor="village2.lmf1", lines={d[36], d[37]}, animstart="looknorth", animend="idle"}},		
			{ action.say, {id=4, actor="village2.lmf3", lines={d[38]}, animstart="talk", animend="idle"}},		
			{ action.say, {id=5, actor="village2.lmf2", lines={d[12]}, animstart="laugh"}},
			{ action.animate_once, {id=6, actor="village2.lmf3", anim="punch1"}},
			{ action.animate_once, {id=7, actor="village2.lmf3", anim="punch2", after={6}}},
			{ action.animate_once, {id=8, actor="village2.lmf2", anim="hit", after={6}}},
			{ action.animate, {id=9, actor="village2.lmf2", anim="idle", after={8}}},
			{ action.animate, {id=10, actor="village2.lmf3", anim="idle", after={7}}},
		}},
		[4] = { text = d[3], active=function() return variables.talked_to_citizen end},
		[5] = { text = d[4], deact={4}, active=true, children={21,22,23,24}, script = ms {
			{ action.say, {id=1, actor="guybrush", lines={d[4]}}},			
			{ action.animate, {id=2, after={1}, actor="village2.lmf1", anim="looknorth"}},
			{ action.animate, {id=3, after={1}, actor="village2.lmf2", anim="idlefront"}},
			{ action.animate, {id=4, after={1}, actor="village2.lmf3", anim="idlefront"}},
			{ action.delay, {id=5, sec=1}},
			{ action.say, {id=6, actor="village2.lmf3", lines={d[43]}, animstart="talk", animend="idle"}},
			{ action.animate, {id=7, actor="village2.lmf2", anim="laugh"}},
			{ action.say, {id=8, actor="village2.lmf1", lines={d[44]}, animstart="talk", animend="idle2"}},
			{ action.animate_once, {id=9, actor="village2.lmf3", anim="punch1"}},
			{ action.animate_once, {id=10, actor="village2.lmf3", anim="punch2", after={9}}},
			{ action.animate_once, {id=11, actor="village2.lmf2", anim="hit", after={9}}},
			{ action.animate, {id=12, actor="village2.lmf2", anim="idle", after={11}}},
			{ action.animate, {id=13, actor="village2.lmf3", anim="idle", after={10}}},
			{ action.say, {id=14, actor="village2.lmf3", lines={d[45], d[46]}, animstart="talk", animend="idle"}},
			{ action.say, {id=15, actor="village2.lmf1", lines={d[47]}, animstart="talk", animend="idle2"}},
		}},
		[6] = { text = d[5], active=true, script = ms {
			{ action.say, {id=1, actor="guybrush", lines={d[5]}}},
		}},
		[7] = { text = d[7], active=true, children = {11,12,13,14}, script = msc {
			{
				{ action.say, {id=1, actor="guybrush", lines={d[7]}}},
			},
			s1
		}},
		[8] = { text = d[8], active=true, children = {11,12,13,14}, script = msc {
			{
				{ action.say, {id=1, actor="guybrush", lines={d[8]}}},
			},
			s1
		}},
		[9] = { text = d[9], act={20}, active=true, script = ms {
			{ action.say, {id=1, actor="guybrush", lines={d[9]}}},
			{ action.animate, {id=2, actor="village2.lmf2", anim="laugh"}},
			{ action.say, {id=3, after={1}, actor="village2.lmf1", lines={d[57]}, animstart="talk", animend="idle2"}},
			{ action.animate_once, {id=4, actor="village2.lmf3", anim="punch1"}},
			{ action.animate_once, {id=5, actor="village2.lmf3", anim="punch2", after={4}}},
			{ action.animate_once, {id=6, actor="village2.lmf2", anim="hit", after={4}}},
			{ action.animate, {id=7, actor="village2.lmf2", anim="idle", after={6}}},		
			{ action.animate, {id=8, actor="village2.lmf3", anim="idle", after={5}}},		
		}},
		[10] = { text = d[10], active=true},
		[11] = { text = d[17], active=true, children = {4,5,6}, script = ms {
			{ action.say, {id=1, actor="guybrush", lines={d[17]}}},
			{ action.say, {id=2, actor="village2.lmf3", lines={d[21], d[22], d[23]}, animstart="talk", animend="idle"}},
			{ action.say, {id=3, actor="village2.lmf1", lines={d[24]}, animstart="looknorth", animend="idle2"}},
		}},
		[12] = { text = d[18], active=true, children = {4,5,6}, script = ms {
			{ action.say, {id=1, actor="guybrush", lines={d[18]}}},
			{ action.say, {id=2, actor="village2.lmf3", lines={d[41], d[22], d[23]}, animstart="talk", animend="idle"}},
			{ action.say, {id=3, actor="village2.lmf1", lines={d[24]}, animstart="looknorth", animend="idle2"}},
		}},
		[13] = { text = d[19], active=true},
		[14] = { text = d[20], active=true},
		[15] = { text = d[68], children ={16,17,18}, deact={15}, active = function () return not(variables.talked_to_citizen) end, script = ms {
			{ action.say, {id=1, actor="guybrush", lines={d[68]}}},
			{ action.say, {id=2, actor="village2.lmf3", lines={d[25]}, animstart="talk", animend="idle"}},
			{ action.animate_once, {id=3, actor="village2.lmf3", anim="openjacket"}},
			{ action.say, {id=4, actor="village2.lmf3", lines={d[26]}, animstart="talk", animend="idle"}},
			{ action.animate, {id=5, actor="village2.lmf1", anim="looknorth"}},
			{ action.animate, {id=6, actor="village2.lmf2", anim="idlefront"}},
			{ action.animate, {id=7, actor="village2.lmf3", anim="idlefront"}},
			{ action.delay, { id=8, sec=1}},
			{ action.animate, {id=9, actor="village2.lmf1", anim="idle2", after={8}}},
			{ action.animate, {id=10, actor="village2.lmf2", anim="laugh"}},
			{ action.say, {id=11, actor="village2.lmf3", lines={d[27]}, animstart="talk", animend="idle"}},
			{ action.animate_once, {id=12, actor="village2.lmf3", anim="openjacket"}},
			{ action.say, {id=13, actor="village2.lmf3", lines={d[28], d[29]}, animstart="talk", animend="idle"}},
			{ action.animate_once, {id=14, actor="village2.lmf3", anim="punch1"}},
			{ action.animate_once, {id=15, actor="village2.lmf3", anim="punch2", after={14}}},
			{ action.animate_once, {id=16, actor="village2.lmf2", anim="hit", after={14}}},
			{ action.animate, {id=18, actor="village2.lmf2", anim="idle", after={15}}},
			{ action.say, {id=17, actor="village2.lmf3", lines={d[30]}, animstart="talk", animend="idle"}},
		}},
		[16] = { text = d[31], active=true, act={19}, children={2,3,19,5,6}, script = ms {
			{ action.say, {id=1, actor="guybrush", lines={d[31]}}},
			{ action.say, {id=2, actor="village2.lmf3", lines={d[66]}, animstart="talk", animend="idle"}}
		}},
		[17] = { text = d[32], active=true, act = {19}, script = ms {
			{ action.say, {id=1, actor="guybrush", lines={d[32]}}},
		}},
		[18] = { text = d[33], active=true},
		[19] = { text = d[67], active=false, children={2,3,19,5,6}, script = ms {
			{ action.say, {id=1, actor="guybrush", lines={d[67]}}},
			{ action.say, {id=2, actor="village2.lmf3", lines={d[42]}, animstart="talk", animend="idle"}},
			{ action.add_to_inventory, {id=3, name="pieces_of_eight", qty=2} }

		}},
		[20] = { text = d[40], active = false, deact={20}, script = msc {
			{
				{ action.say, {id=1, actor="guybrush", lines={d[40]}}},
			},
			s1
		}},
		[21] = {text = d[48], active=true, children = {2, 20, 3, 4, 15, 19, 5, 6}, script = ms {
			{ action.say, {id=1, actor="guybrush", lines={d[48]}}},
			{ action.say, {id=2, actor="village2.lmf3", lines={d[53]}, after={1}, animstart="talk", animend="idle"}},
			{ action.say, {id=3, actor="village2.lmf1", lines={d[52]}, after={1}, animstart="talk", animend="idle2"}},
			{ action.animate, {id=4, actor="village2.lmf2", anim="idlefront", after={1}}},
			{ action.animate, {id=5, actor="village2.lmf1", anim="looknorth", after={3}}},
			{ action.animate, {id=6, actor="village2.lmf3", anim="idlefront", after={2}}},
			{ action.delay, {id=7, sec=1}},
			{ action.say, {id=8, after={7}, actor="village2.lmf3", lines={d[52]}, after={7}, animstart="talk", animend="idle"}},
			{ action.say, {id=9, after={7}, actor="village2.lmf1", lines={d[53]}, after={7}, animstart="talk", animend="idle2"}},
			{ action.animate, {id=10, actor="village2.lmf1", anim="looknorth", after={9}}},
			{ action.animate, {id=11, actor="village2.lmf3", anim="idlefront", after={8}}},
			{ action.delay, {id=12, sec=1}},
			{ action.say, {id=13, actor="village2.lmf3", lines={d[54], d[55]}, animstart="talk", animend="idle"}},
			{ action.animate, {id=14, actor="village2.lmf2", anim="idle", after={12}}},

		}},
		[22] = {text = d[49], active=true},
		[23] = {text = d[50], active=true},
		[24] = {text = d[51], active=true},




	}
}