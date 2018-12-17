local d = strings.dialogues.voodoolady


local s1 = {
	{ action.noop, {id=1}},
	{ action.walkto, {id=2, actor="guybrush", pos={150, 30}}},
	{ action.scroll, {id=3, speed=50, to ={160, 72}, after={1}}},
	{ action.activate, {id = 4, tag="bg1", value=true, after={1}}},
	{ action.activate, {id = 5, tag="bg2", value=false, after={3}}},
	{ action.set_variable, {id=6, var="talking_to_voodoolady", value=false }}
}

local s2 = {
	{ action.noop, {id = 1}},
	{ action.say, {id = 2,actor="voodoolady.voodoolady", lines = {d[29]}, animstart="talk", animend="idle"}},
	{ action.animate_once, {id=3, actor="voodoolady.voodoolady_body", anim="raisehands"}},
	{ action.animate, {id=4, actor="voodoolady.voodoolady_body", anim="idle"}},
	{ action.say, {id =5, actor="voodoolady.voodoolady", lines = {d[30], d[31]}, animstart="talk", animend="idle"}},
	{ action.say, {id =6,actor="guybrush", lines = {d[32]}}},
	{ action.say, {id =7, actor="voodoolady.voodoolady", lines = {d[33]}, animstart="talk", animend="idle"}},
	{ action.delay, {id=8, sec=0.5}},
	{ action.say, {id =9,actor="guybrush", lines = {d[34], d[35]}}},
	{ action.animate_once, {id=10, actor="voodoolady.voodoolady_body", anim="raisehands"}},
	{ action.animate, {id=16, actor="voodoolady.voodoolady_body", anim="idle", after={10}}},
	{ action.say, {id =11, actor="voodoolady.voodoolady", lines = {d[36]}, animstart="talk", animend="idle", after={10}}},
	{ action.say, {id =12, actor="guybrush", lines = {d[37]}}},
	{ action.say, {id =13, actor="voodoolady.voodoolady", lines = {d[38]}, animstart="talk", animend="idle"}},
	{ action.say, {id =14, actor="guybrush", lines = {d[39]}}},
	{ action.say, {id =15, actor="voodoolady.voodoolady", lines = {d[40], d[41]}, animstart="talk", animend="idle"}},
	{ action.animate_once, {id=17, actor="voodoolady.voodoolady_body", anim="raisehands", after={15}}},
	{ action.animate, {id=18, actor="voodoolady.voodoolady_body", anim="idle"}},
	{ action.say, {id =19, after={17}, actor="voodoolady.voodoolady", lines = {d[42], d[43], d[44], d[45]}, animstart="talk", animend="idle"}},
	{ action.say, {id =20, actor="guybrush", lines = {d[46], d[47]}}},
	{ action.say, {id =21, actor="voodoolady.voodoolady", lines = {d[48], d[49], d[50], d[51]}, animstart="talk", animend="idle"}},
	{ action.delay, {id = 22, sec=1}},
	{ action.activate, {id = 23, name="voodoolady.voodoolady", value=false}},
	{ action.activate, {id = 24, name="voodoolady.voodoolady_body", value=false}},
	{ action.delay, {id = 25, sec=0.5}},
	{ action.say, {id =26, actor="guybrush", lines = {d[37]}}},
	{ action.set_variable, {id=27, var="voodoolady_told_future", value=true}}
}

dialogues.voodoolady = {
	close = function()
		-- local s = script:new("_citizenclose")
		-- s.actions = {
		-- 	action.animate {id=1,actor="village2.citizen", anim="idle"}
		-- }
		-- monkey.play(s)
	end,
	nodes = {
		[1] = { children = {2,3,12,4,9,10,11} },
		[2] = {text= d[2], active=true, children={5,6}, deact={2}, script = ms {
			{ action.say, {id = 1,actor="voodoolady.voodoolady", lines = {d[8], d[9],d[10],d[11],d[12],d[13],d[14]}, animstart="talk", animend="idle"}},
			{ action.delay, {id=2, sec=1}},
			{ action.say, {id = 1,actor="voodoolady.voodoolady", lines = {d[15],d[16],d[17]}, animstart="talk", animend="idle"}},

		}},
		[3] = {text= d[3], active=true, children = {7,8}, script = ms {
			{ action.say, {id = 1,actor="voodoolady.voodoolady", lines = {d[22],d[23],d[24]}, animstart="talk", animend="idle"}},
		}},
		[4] = {text= d[4], active=true, script = msc {
			{
				{ action.say, {id = 1,actor="voodoolady.voodoolady", lines = {d[5], d[6]}, animstart="talk", animend="idle"}}
			},
			s1
		}},
		[5] = {text=d[18], active=true, children = {3,4}, script = ms {
			{ action.say, {id = 1,actor="guybrush", lines = {d[18]}}},
			{ action.say, {id = 1,actor="voodoolady.voodoolady", lines = {d[20],d[21]}, animstart="talk", animend="idle"}},
		}},
		[6] = {text=d[19], active=true},
		[7] = {text=d[25], active=true, act={9,10,11}, deact={2,3,4}, script = msc { 
			{ { action.say, {id = 1,actor="guybrush", lines = {d[25]}}}}, s2, s1 }},
		[8] = {text=d[26], active=true, children = {2, 12, 4},act={12}, script = ms {
				{ action.say, {id = 1,actor="guybrush", lines = {d[26]}}},
				{ action.say, {id = 2,actor="voodoolady.voodoolady", lines = {d[27]}, animstart="talk", animend="idle"}},
		}},
		[9] = {text=d[52], active=false, script = msc {	
			{
				{ action.say, {id = 1,actor="guybrush", lines = {d[52], d[55]}}},
			},
			s1
		}},
		[10] = {text=d[53], active=false, script = msc {	
			{
				{ action.say, {id = 1,actor="guybrush", lines = {d[53], d[55]}}},
			},
			s1
		}},
		[11] = {text=d[54], active=false, script = msc {	
			{
				{ action.say, {id = 1,actor="guybrush", lines = {d[54]}}},
			},
			s1
		}},
		[12] = {text=d[28], active=false, script = msc {
			{
				{ action.say, {id = 1,actor="voodoolady.voodoolady", lines = {d[56]}, animstart="talk", animend="idle"}},
			}, s2, s1
		}}




	}	
}