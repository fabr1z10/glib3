local d = strings.dialogues.lowmoralfiber

function punch( n )
    return {
        { type = action.animate, args = {actor="village2.lmf2", anim="laugh"}},
        n > 0 and { type = action.say, args = {actor="village2.lmf2", lines={d[n]}, animate=false }} or {},
        { type = action.delay, args = {sec = 0.5}},
        { type = action.animate, args = {actor="village2.lmf3", anim="idle_s"}},
        { type = action.delay, args = {sec = 0.3}},
        { type = action.animate, args = {actor="village2.lmf3", anim="idle_e"}},
        { type = action.delay, args = {sec = 0.3}},
        { type = action.animate, args = {actor="village2.lmf3", anim="punch", sync=true }},
        { type = action.animate, args = {actor="village2.lmf2", anim="hit" }},
        { type = action.delay, args = {sec = 0.3}},
        { type = action.animate, args = {actor="village2.lmf3", anim="idle_e", sync=true }},
        { type = action.animate, args = {actor="village2.lmf2", anim="idle" }},
		{ type = action.animate, args = {actor="village2.lmf1", anim="rock"}}
	}
end

local s1 = {
	{ type = action.say, args = {actor="village2.lmf1", lines={d[11]}, animstart="talk", animend="idle"}},
	punch(12),
	{ type = action.say, args = {actor="village2.lmf1", lines={d[13]}, animstart="looknorth", animend="idle"}},
	{ type = action.say, args = {actor="village2.lmf1", lines={d[14]}, animstart="talk", animend="idle"}},
	{ type = action.say, args = {actor="village2.lmf3", lines={d[15]}, animstart="talk_s", animend="idle_e"}},
	{ type = action.say, args = {actor="village2.lmf3", lines={d[16]}, animstart="talk_e", animend="idle_e"}},
}

local s2 = {
	{ type = action.say, args = {actor="village2.lmf3", lines={d[22], d[23]}, animstart="talk_e", animend="idle_e"}},
	{ type = action.say, args = {actor="village2.lmf1", lines={d[24]}, animstart="looknorth", animend="idle"}},
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
		[2] = { text = d[1], active=true, deact={2, 3, 22}, children = {7,8,9,10}, script = {
			{ type = action.say, args = {actor="guybrush", lines={d[1]}}},
			{ type = action.say, args = {actor="village2.lmf1", lines={d[6]}, animstart="talk", animend="idle"}}		
		}},
		[3] = { text = d[2], active=true, deact={2,3}, act = {20}, script = {
			{ type = action.say, args = {actor = "guybrush", lines={d[2]}}},		
			{ type = action.say, args = {actor = "village2.rat", lines={d[34], d[35]}, animate=false}},		
			{ type = action.say, args = {actor="village2.lmf1", lines={d[36], d[37]}, animstart="looknorth", animend="idle"}},		
			{ type = action.say, args = {actor="village2.lmf3", lines={d[38]}, animstart="talk_e", animend="idle_e"}},
			punch(39)
		}},
		[4] = { text = d[3], active=function() return variables.talked_to_citizen end},
		[5] = { text = d[4], deact={5}, active=true, children={21,22,23,24}, script = {
			{ ref = 1, type = action.say, args = {actor="guybrush", lines={d[4]}}},			
			{ type = action.animate, after={1}, args = {actor="village2.lmf1", anim="looknorth"}},
			{ type = action.animate, after={1}, args = {actor="village2.lmf2", anim="idle_s"}},
			{ type = action.animate, after={1}, args = {actor="village2.lmf3", anim="idle_s"}},
			{ type = action.delay, args = {sec=1}},
			{ type = action.say, args = {actor="village2.lmf3", lines={d[43]}, animstart="talk_e", animend="idle_e"}},
			{ type = action.animate, args = {actor="village2.lmf2", anim="laugh"}},
			{ type = action.say, args = {actor="village2.lmf1", lines={d[44]}, animstart="talk", animend="idle"}},
			punch(0),
			{ type = action.say, args = {actor="village2.lmf3", lines={d[45], d[46]}, animstart="talk_e", animend="idle_e"}},
			{ type = action.say, args = {actor="village2.lmf1", lines={d[47]}, animstart="talk", animend="rock"}},
		}},
		[6] = { text = d[5], active=true, script = ms {
			{ action.say, {id=1, actor="guybrush", lines={d[5]}}},
		}},
		[7] = { text = d[7], active=true, children = {11,12,13,14}, script = { { type = action.say, args = {actor="guybrush", lines={d[7]}}}, s1}},
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
		[11] = { text = d[17], active=true, children = {3,15,4,5,6}, script = {
			{ type = action.say, args = {actor="guybrush", lines={d[17]}}},
			{ type = action.say, args = {actor="village2.lmf3", lines={d[21]}, animstart="talk_e", animend="idle_e"}},
			s2
		}},
		[12] = { text = d[18], active=true, children = {3,15,4,5,6}, script = {
			{ type = action.say, args = {actor="guybrush", lines={d[18]}}},
			{ type = action.say, args = {actor="village2.lmf3", lines={d[41]}, animstart="talk_e", animend="idle_e"}},
			s2
		}},
		[13] = { text = d[19], active=true, children = {3,15,4,5,6}, script =  {
			{ type = action.say, args = {actor="guybrush", lines={d[19]}}},
			{ type = action.say, args = {actor="village2.lmf3", lines={d[56]}, animstart="talk_e", animend="idle_e"}},
			s2
		}},
		[14] = { text = d[20], active=true},
		[15] = { text = d[68], children ={16,17,18}, deact={15}, active = function () return not(variables.talked_to_citizen) end, script = {
			{ type = action.say, args = {actor="guybrush", lines={d[68]}}},
			{ ref = 1, type = action.say, args = {actor="village2.lmf3", lines={d[25]}, animstart="talk_e", animend="idle_e"}},
			{ type = action.animate, args = {actor="village2.lmf3", anim="open_jacket", sync = true}},
			{ type = action.animate, args = {actor="village2.lmf3", anim="open_jacket", sync = true, fwd=false}},
			{ ref = 2, type = action.say, after={1}, args = {actor="village2.lmf3", lines={d[26]}, animstart="h_talk_e", animend="idle_e"}},
			{ type = action.animate, args = {actor="village2.lmf1", anim="looknorth"}},
			{ type = action.animate, after={2}, args = {actor="village2.lmf2", anim="idle_s"}},
			{ type = action.animate, after={2}, args = {actor="village2.lmf3", anim="idle_s"}},
			{ type = action.delay, args = {sec=1}},
			{ type = action.animate, args = {actor="village2.lmf1", anim="idle"}},
			{ ref = 3, type = action.animate, args = {actor="village2.lmf2", anim="laugh"}},
			{ type = action.animate, after = {3}, args = {actor="village2.lmf3", anim="open_jacket", sync = true}},
			{ type = action.animate, args = {actor="village2.lmf3", anim="open_jacket", sync= true, fwd=false}},
			{ type = action.say, after={3}, args = {actor="village2.lmf3", lines={d[27],d[28], d[29]}, animstart="h_talk_e", animend="idle_e"}},
			punch(0),
			{ type = action.say, args = {actor="village2.lmf3", lines={d[30]}, animstart="talk_e", animend="idle_e"}},
		}},
		[16] = { text = d[31], active=true, act={19}, children={2,3,19,5,6}, script = {
			{ type = action.say, args = {actor="guybrush", lines={d[31]}}},
			{ type = action.say, args = {actor="village2.lmf3", lines={d[66]}, animstart="talk_e", animend="idle_e"}}
		}},
		[17] = { text = d[32], active=true, act = {19}, script = { { type=action.say, args = {id=1, actor="guybrush", lines={d[32]}}}}},
		[18] = { text = d[33], active=true, deact={18,19}, children = {2,3,5,6}, script = {
			{ type = action.say, args = {actor="guybrush", lines={d[33]}}},
			{ type = action.say, args = {actor="village2.lmf3", lines={d[42]}, animstart="talk_e", animend="idle_e"}},
			{ type = action.add_to_inventory, args = {name="pieces_of_eight", qty=2} }
		}},
		[19] = { text = d[67], active=false, children={2,3,19,5,6}, script = ms {
			{ type = action.say, args = {actor="guybrush", lines={d[67]}}},
			{ type = action.say, args = {actor="village2.lmf3", lines={d[42]}, animstart="talk_e", animend="idle_e"}},
			{ type = action.add_to_inventory, args = {name="pieces_of_eight", qty=2} }
		}},
		[20] = { text = d[40], active = false, deact={20}, children = {11,12,13,14}, script = {
			{ type = action.say, args = {id=1, actor="guybrush", lines={d[40]}}},
			s1
		}},
		[21] = {text = d[48], active=true, children = {2, 20, 3, 4, 15, 19, 5, 6}, script = {
			{ ref = 1, type = action.say, args = {actor="guybrush", lines={d[48]}}},
			{ ref = 2, type = action.say, after={1}, args = {actor="village2.lmf3", lines={d[53]}, animstart="talk_e", animend="idle_e"}},
			{ ref = 3, type = action.say, after={1}, args = {actor="village2.lmf1", lines={d[52]}, animstart="talk", animend="idle"}},
			{ type = action.animate, after={1}, args = {actor="village2.lmf2", anim="idle_s"}},
			{ type = action.animate, after={2,3}, args= {actor="village2.lmf1", anim="looknorth" }},
			{ type = action.animate, after={2,3}, args= {actor="village2.lmf3", anim="idle_s" }},
			{ ref = 6, type = action.delay, args = {sec=1}},
			{ ref = 4, type = action.say, after={6}, args = {actor="village2.lmf3", lines={d[52]}, animstart="talk_e", animend="idle_e"}},
			{ ref = 5, type = action.say, after={6}, args = {actor="village2.lmf1", lines={d[53]}, animstart="talk", animend="idle"}},
			{ type = action.animate, after={4,5}, args= {actor="village2.lmf1", anim="looknorth" }},
			{ type = action.animate, after={4,5}, args= {actor="village2.lmf3", anim="idle_s" }},
			{ type = action.delay, args = {sec=1}},
			{ type = action.say, args = {actor="village2.lmf3", lines={d[54], d[55]}, animstart="talk_e", animend="idle_e"}},
			{ type = action.animate, args = {actor="village2.lmf2", anim="idle", }},
			{ type = action.animate, args = {actor="village2.lmf1", anim="rock", }},
		}},
		[22] = {text = d[49], active=true, children = {7,8,9,10}, script = {
			{ type = action.say, args = {actor="guybrush", lines={d[1]}}},
			{ type = action.say, args = {actor="village2.lmf1", lines={d[6]}, animstart="talk", animend="idle"}}		
		}},
		[23] = {text = d[50], active=true, script = { {type=action.say, args = {actor="guybrush", lines={d[50]}}}}},
		[24] = {text = d[51], active=true, script = {
			{ type = action.say, args = {actor="guybrush", lines={d[51]}}},
			{ type = action.animate, args= {actor="village2.lmf1", anim="looknorth" }},
			{ type = action.say, args = {actor="village2.lmf3", lines={d[58]}, animstart="talk_e", animend="idle_e"}},
			{ type = action.animate, args = {actor="village2.lmf2", anim="idle_s"}},
			{ type = action.animate, args= {actor="village2.lmf3", anim="idle_s" }},
			{ type = action.say, args = {actor="village2.lmf1", lines={d[59]}, animstart="talk", animend="idle"}},
			{ type = action.animate, args= {actor="village2.lmf1", anim="looknorth" }},
			{ type = action.say, args = {actor="village2.lmf3", lines={d[60]}, animstart="talk_e", animend="idle_e"}},
			{ type = action.animate, args= {actor="village2.lmf3", anim="idle_s" }},
			{ type = action.say, args = {actor="village2.lmf1", lines={d[61], d[62]}, animstart="talk", animend="idle"}},
			{ type = action.animate, args= {actor="village2.lmf1", anim="looknorth" }},
			{ type = action.say, args = {actor="village2.lmf3", lines={d[63]}, animstart="talk_e", animend="idle_e"}},
			{ type = action.animate, args= {actor="village2.lmf3", anim="idle_s" }},
			{ type = action.delay, args = {sec=1}},
			{ type = action.animate, args= {actor="village2.lmf1", anim="rock" }},
			{ type = action.animate, args= {actor="village2.lmf2", anim="idle" }},
			{ type = action.say, args = {actor="village2.lmf3", lines={d[64], d[65]}, animstart="talk_e", animend="idle_e"}},
		}},




	}
}