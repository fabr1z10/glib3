-- lookout dialogue

dialoguesLookout = {}

local d = strings.dialogues.lookout.text

function dialoguesLookout.start(i) 
	s = script:new("_dial")
	dialogues.lookout[1].lines[5].active= true
	s.actions = {
		[1] = say { character = "guybrush", lines = { d[i] } },
		[2] = { type="turn", actor= "lookout", face = "south", after={1} },
		[3] = variables.talkedToLookout and say { character = "lookout", lines = { d[5], strings.dialogues.lookout.randomLookoutMsg() }, after={2}} or
    		say { character = "lookout", lines = { d[5], d[6], d[7], d[8], d[9] }, after={2} },
		[4] = { type = "callfunc", func = curry(startDialogue, { dialogueId="lookout", nodeId=2 }), after={3} }
	}
	variables.talkedToLookout = true	
	return s
end

function dialoguesLookout.iamguybrush() 
	variables.lookoutKnowsName = true
	dialogues.lookout[2].lines[11].active= true
	s = script:new("_dial")
	s.actions = {
		[1] = say { character = "guybrush", lines = { d[10], d[17] } },
		[2] = say { character = "lookout", lines = { d[18], d[19], d[20], d[21] }, after={1} },
	 	[3] = { type = "callfunc", func = curry(startDialogue, { dialogueId="lookout", nodeId=2 }), after={2}}
	}
	return s
end

function dialoguesLookout.whatiswrong() 
	s = script:new("_dial")
	s.actions = {
		[1] = say { character = "guybrush", lines = { d[22] } },
	 	[2] = say { character = "lookout", lines = { d[23], d[24], d[25], d[26] }, after={1} },
		[3] = { type = "callfunc", func = curry(startDialogue, { dialogueId="lookout", nodeId=2 }), after={2} }
	}
	return s
end

function dialoguesLookout.iamhere()
	s = script:new("_dial")
	s.actions = {
		[1] = say { character = "guybrush", lines = { d[12] } },
		[2] = { type="turn", actor= "lookout", face = "east", after={1}},
	 	[3] = say { character = "lookout", lines = { d[15], d[16] }, after={2} },
	 	[4] = { type = "callfunc", func = curry(startDialogue, { dialogueId="lookout", nodeId=2 }), after={3}}
	}
	return s
end

function dialoguesLookout.goodbye() 
	s = script:new("_dial")
	s.actions = {
		[1] = say { character = "guybrush", lines = { d[14] } },
	 	[2] = say { character = "lookout", lines = { d[42] }, after={1}},
	 	[3] = { type="turn", actor="lookout", face = "west", after={2} },
	 	[4] = { type = "callfunc", func = resumePlay, after={3} }
	}
	return s
end

function dialoguesLookout.squinky() 
	s = script:new("_dial")
	s.actions[1] = say { character = "guybrush", lines = { d[11] } }
	if (variables.lookoutKnowsName == false) then
		s.actions[2] = say { character = "lookout", lines = { d[41] }, after={1} }
	else 
	 	s.actions[2] = say { character = "lookout", lines = { d[27] }, after={1} }
	 	s.actions[3] = say { character = "guybrush", lines = { d[28] }, after={2} }
	 	s.actions[4] = say { character = "lookout", lines = { d[29] }, after={3} }
	end
	s.actions[#s.actions+1] = { type = "callfunc", func = curry(startDialogue, { dialogueId="lookout", nodeId=2 }), after={#s.actions} }
    return s
end

function dialoguesLookout.whoareu()
	dialogues.lookout[2].lines[41].active= true
	dialogues.lookout[2].lines[42].active= true
	dialogues.lookout[2].lines[10].active= false
	dialogues.lookout[2].lines[11].active= false
	dialogues.lookout[2].lines[20].active= false
	s = script:new("_dial")
	s.actions = {
		[1] = say { character = "guybrush", lines = { d[13] } },
		[2] = say { character = "lookout", lines = { d[30], d[31], d[32], d[33] }, after={1} },
		[3] = { type = "callfunc", func = curry(startDialogue, { dialogueId="lookout", nodeId=2 }), after={2}}
	}
	return s	
end

function dialoguesLookout.govworried()
	s = script:new("_dial")
	s.actions = {
		[1] = say { character = "guybrush", lines = { d[34] } },
		[2] = say { character = "lookout", lines = { d[35], d[36], d[37] }, after={1}},
		[3] = { type = "callfunc", func = curry(startDialogue, { dialogueId="lookout", nodeId=2 }), after={2}}
	}
	return s	
end


function dialoguesLookout.bat()
	s = script:new("_dial")
	s.actions = {
		[1]= say { character = "guybrush", lines = { d[38] } },
		[2] = say { character = "lookout", lines = { d[39], d[40] }, after={1} },
		[3]= { type = "callfunc", func = curry(startDialogue, { dialogueId="lookout", nodeId=2 }), after={2}}
	}	
	return s	
end

function dialoguesLookout.thatsthreep()
	s = script:new("_dial")
	s.actions = {
		[1] =say { character = "guybrush", lines = { d[47] } },
		[2] = say { character = "lookout", lines = { d[49] }, after={2} },
		[3] = { type = "callfunc", func = curry(startDialogue, { dialogueId="lookout", nodeId=2 }), after={2}}
	}	
	return s	
end