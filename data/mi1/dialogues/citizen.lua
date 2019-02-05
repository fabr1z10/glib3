local d = strings.dialogues.citizen

local s1 = {
	{ action.say, { id = 1, actor = "village2.citizen",  lines = {d[18]}, animstart="talkside", animend="idleside" }},
	{ action.animate_once, { id = 2, actor="village2.citizen", anim="openjacket"}},
	{ action.animate, { id = 3, actor="village2.citizen", anim="openjacketidle"}},
	{ action.delay, {id=4, sec=1}},
	{ action.say, { id = 5, actor="village2.citizen", lines = {d[19]}, animstart="openjackettalk", animend="openjacketidle"}},
	{ action.animate_once, { id = 6, actor="village2.citizen", anim="closejacket"}},
	{ action.animate, { id = 7, actor="village2.citizen", anim="idleside"}},			
	{ action.delay, {id=8, sec=1}},
    { action.say, { id = 9, actor="village2.citizen", lines = {d[20]}, animstart="talkside", animend="idleside"}},
	{ action.animate_once, { id = 10, actor="village2.citizen", anim="rollmap"}},
	{ action.say, { id = 11, actor="village2.citizen", lines = {d[21], d[22]}, animstart="rollmaptalk", animend="rollmapidle"}},
	{ action.animate_once, { id = 12, actor="village2.citizen", anim="unrollmap"}},
	{ action.say, { id = 13, actor="village2.citizen", lines = {d[23]}, animstart="talkside", animend="idleside"}},
	{ action.set_variable, { id = 14, var = "talked_to_citizen", value=true}},
	{ action.set_variable, {id=15, var="talked_about_map", value=true}}	
}


dialogues.citizen = {
	close = function()
		local s = script:new("_citizenclose")
		s.actions = {
			action.animate {id=1,actor="village2.citizen", anim="idle"}
		}
		monkey.play(s)
	end,
	nodes = {
		[1] = { children = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11} },
		[2] = { text = d[2], deact = {2,3,4,5}, act={6,7,8,9}, active=true, script = ms {
			{ action.say, { id = 1, actor = "guybrush",  lines = {d[2]} }},
			{ action.say, { id = 2, actor = "village2.citizen",  lines = {d[6], d[7]}, animstart="talk", animend="idle_e" }},
			{ action.set_variable, { id = 3, var = "talked_to_citizen", value=true}},
			}
		},
		[3] = { text = d[3], deact = {2,3,4,5}, act={6,7,8,9}, active=true, script = ms {
			{ action.say, { id = 1, actor = "guybrush",  lines = {d[3]} }},
			{ action.say, { id = 2, actor = "village2.citizen",  lines = {d[6], d[7]}, animstart="talkside", animend="idleside" }},
			{ action.set_variable, { id = 3, var = "talked_to_citizen", value=true}},
			}
		},
		[4] = { text = d[4], deact = {2,3,4,5}, act={6,7,8,9}, active=true, script = ms {
			{ action.say, { id = 1, actor = "guybrush",  lines = {d[4]} }},
			{ action.say, { id = 2, actor = "village2.citizen",  lines = {d[16], d[6], d[7]}, animstart="talkside", animend="idleside" }},
			{ action.set_variable, { id = 3, var = "talked_to_citizen", value=true}},
			}
		},
		[5] = { text = d[5], active=true, deact={2,3,4,5,6,7,8,9}, children ={10, 11}, script = msc {
			{
				{ action.say, { id = 1, actor = "guybrush",  lines = {d[5]} }},
				{ action.say, { id = 2, actor = "village2.citizen",  lines = {d[17]}, animstart="talkside", animend="idleside" }},
			},
			s1}
		},
		[6] = { text = d[10], active = false, children ={10, 11}, script = msc {
			{
				{ action.say, { id = 1, actor = "guybrush",  lines = {d[10]} }},
				{ action.say, { id = 2, actor = "village2.citizen",  lines = {d[29], d[30], d[31], d[32]}, animstart="talkside", animend="idleside" }},
			},
			s1}
		},
		[7] = { text = d[11], active = false, children ={10, 11}, script = msc {
			{
				{ action.say, { id = 1, actor = "guybrush",  lines = {d[11]} }},
				{ action.say, { id = 2, actor = "village2.citizen",  lines = {d[33]}, animstart="talkside", animend="idleside" }},
			},
			s1}
		},
		[8] = { text = d[12], active = false, script = msc {
			{
				{ action.say, { id = 1, actor = "guybrush",  lines = {d[12]} }},
				{ action.say, { id = 2, actor = "village2.citizen",  lines = {d[29], d[30], d[31], d[32]}, animstart="talkside", animend="idleside" }},
			},
			s1}
		},
		[9] = { text = d[13], active = false, script = ms {
			{ action.say, { id = 1, actor = "guybrush",  lines = {d[13]} }},
			{ action.say, { id = 2, actor = "village2.citizen",  lines = {d[14], d[15]}, animstart="talkside", animend="idleside" }},
			}
		},
		[10] = { text = d[24], active = function() 
			return (variables.talked_about_map and (
				(variables.inventory["piece_of_eight"] == nil) or (variables.inventory["piece_of_eight"]<100)))
			end, script = ms {
				{ action.say, { id = 1, actor = "guybrush",  lines = {d[24]} }},
				{ action.say, { id = 2, actor = "village2.citizen",  lines = {d[26]}, animstart="talkside", animend="idleside" }},
			}
		},
		[11] = { text = d[25], active = function() 
			return (variables.talked_about_map and (
				(variables.inventory["piece_of_eight"] == nil) or (variables.inventory["piece_of_eight"]<100)))
			end, script = ms {
				{ action.say, { id = 1, actor = "guybrush",  lines = {d[25]} }},
				{ action.say, { id = 2, actor = "village2.citizen",  lines = {d[34], d[35]}, animstart="talkside", animend="idleside" }},
			}
		},

	}
}