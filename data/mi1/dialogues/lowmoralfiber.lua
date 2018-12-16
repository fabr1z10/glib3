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
		[1] = { children = {2, 3, 4, 15, 19, 5, 6} },
		[2] = { text = d[1], active=true, deact={2}, children = {7,8,9,10}, script = ms {
			{ action.say, {id=1, actor="guybrush", lines={d[1]}}},
			{ action.say, {id=2, actor="village2.lmf1", lines={d[6]}, animstart="talk", animend="idle2"}},			
		}},
		[3] = { text = d[2], active=true},
		[4] = { text = d[3], active=function() return variables.talked_to_citizen end},
		[5] = { text = d[4], active=true},
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
		[9] = { text = d[9], active=true},
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
		[17] = { text = d[32], active=true},
		[18] = { text = d[33], active=true},
		[19] = { text = d[67], active=false, children={2,3,19,5,6}, script = ms {
			{ action.say, {id=1, actor="guybrush", lines={d[67]}}},
			{ action.say, {id=2, actor="village2.lmf3", lines={d[42]}, animstart="talk", animend="idle"}},
			{ action.add_to_inventory, {id=3, name="pieces_of_eight", qty=2} }

		}}



	}
}