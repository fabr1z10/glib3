local d = strings.dialogues.citizen

dialogues.citizen = {
	close = function()
		print ("CANENENENENEN!!!!")
		local s = script:new("_citizenclose")
		s.actions = {
			action.animate {id=1,actor="village2.citizen", anim="idle"}
		}
		monkey.play(s)
	end,
	nodes = {
		[1] = { children = {2, 3, 4, 5} },
		[2] = { text = d[2], active=true, script = ms {
			{ action.say, { id = 1, actor = "guybrush",  lines = {d[2]} }},
			{ action.say, { id = 2, actor = "village2.citizen",  lines = {d[6], d[7]}, animstart="talkside", animend="idleside" }},
			{ action.set_variable, { id = 3, var = "talked_to_citizen", value=true}},
			}
		},
		[3] = { text = d[3], active=true, script = ms {
			{ action.say, { id = 1, actor = "guybrush",  lines = {d[3]} }},
			{ action.say, { id = 2, actor = "village2.citizen",  lines = {d[6], d[7]}, animstart="talkside", animend="idleside" }},
			{ action.set_variable, { id = 3, var = "talked_to_citizen", value=true}},
			}
		},
		[4] = { text = d[4], active=true, script = ms {
			{ action.say, { id = 1, actor = "guybrush",  lines = {d[4]} }},
			{ action.say, { id = 2, actor = "village2.citizen",  lines = {d[16], d[6], d[7]}, animstart="talkside", animend="idleside" }},
			{ action.set_variable, { id = 3, var = "talked_to_citizen", value=true}},
			}
		},
		[5] = { text = d[5], active=true},
	}
}