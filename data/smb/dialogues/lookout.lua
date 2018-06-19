-- lookout dialogue

dialoguesLookout = {}

local d = strings.dialogues.lookout.text

function dialoguesLookout.start(i) 
	 s = Script.create("_dial")
	 dialogues.lookout[1].lines[5].active= true
	 s:add (say { character = characters.guybrush, lines = { d[i] } })
	 s:add (turn { character = characters.lookout, face = "south"} )
	 if (variables.talkedToLookout == false) then
	 	s:add (say { character = characters.lookout, lines = { d[5], d[6], d[7], d[8], d[9] } })
	 else
		s:add (say { character = characters.lookout, lines = { d[5], strings.dialogues.lookout.randomLookoutMsg() } })
	 end
	 variables.talkedToLookout = true	
	 s:add ({{ type = "callfunc", func = curry(startDialogue, { dialogueId="lookout", nodeId=2 })}})
	 s:setsequence()
	 return s
end

function dialoguesLookout.iamguybrush() 
	 variables.lookoutKnowsName = true
	 dialogues.lookout[2].lines[11].active= true
	 s = Script.create("_dial")
	 s:add (say { character = characters.guybrush, lines = { d[10], d[17] } })
	 s:add (say { character = characters.lookout, lines = { d[18], d[19], d[20], d[21] } })
	 s:add ({{ type = "callfunc", func = curry(startDialogue, { dialogueId="lookout", nodeId=2 })}})
	 s:setsequence()
	 return s
end

function dialoguesLookout.whatiswrong() 
	 s = Script.create("_dial")
	 s:add (say { character = characters.guybrush, lines = { d[22] } })
	 s:add (say { character = characters.lookout, lines = { d[23], d[24], d[25], d[26] } })
	 s:add ({{ type = "callfunc", func = curry(startDialogue, { dialogueId="lookout", nodeId=2 })}})
	 s:setsequence()
	 return s
end

function dialoguesLookout.iamhere()
	 s = Script.create("_dial")
	 s:add (say { character = characters.guybrush, lines = { d[12] } })
	 s:add (turn { character = characters.lookout, face = "east"} )
	 s:add (say { character = characters.lookout, lines = { d[15], d[16] } })
	 s:add ({{ type = "callfunc", func = curry(startDialogue, { dialogueId="lookout", nodeId=2 })}})
	 s:setsequence()
	 return s
end

function dialoguesLookout.goodbye() 
	 s = Script.create("_dial")
	 s:add (say { character = characters.guybrush, lines = { d[14] } })
	 s:add (say { character = characters.lookout, lines = { d[42] } })
	 s:add (turn { character = characters.lookout, face = "west"} )
	 s:add ({{ type = "callfunc", func = resumePlay }})
	 s:setsequence()
	 return s
end

function dialoguesLookout.squinky() 
	 s = Script.create("_dial")
	 s:add (say { character = characters.guybrush, lines = { d[11] } })
	 if (variables.lookoutKnowsName == false) then
	 	s:add (say { character = characters.lookout, lines = { d[41] } })
	 else 
	 	s:add (say { character = characters.lookout, lines = { d[27] } })
	 	s:add (say { character = characters.guybrush, lines = { d[28] } })
	 	s:add (say { character = characters.lookout, lines = { d[29] } })
	 end
	 s:add ({{ type = "callfunc", func = curry(startDialogue, { dialogueId="lookout", nodeId=2 })}})
	 s:setsequence()
	 return s
end

function dialoguesLookout.whoareu()
	 dialogues.lookout[2].lines[41].active= true
	 dialogues.lookout[2].lines[42].active= true
	 dialogues.lookout[2].lines[10].active= false
	 dialogues.lookout[2].lines[11].active= false
	 dialogues.lookout[2].lines[20].active= false
	 s = Script.create("_dial")
	 s:add (say { character = characters.guybrush, lines = { d[13] } })
	 s:add (say { character = characters.lookout, lines = { d[30], d[31], d[32], d[33] } })
	 s:add ({{ type = "callfunc", func = curry(startDialogue, { dialogueId="lookout", nodeId=2 })}})
	 s:setsequence()
	 return s	
end

function dialoguesLookout.govworried()
	 s = Script.create("_dial")
	 s:add (say { character = characters.guybrush, lines = { d[34] } })
	 s:add (say { character = characters.lookout, lines = { d[35], d[36], d[37] } })
	 s:add ({{ type = "callfunc", func = curry(startDialogue, { dialogueId="lookout", nodeId=2 })}})
	 s:setsequence()
	 return s	
end


function dialoguesLookout.bat()
	 s = Script.create("_dial")
	 s:add (say { character = characters.guybrush, lines = { d[38] } })
	 s:add (say { character = characters.lookout, lines = { d[39], d[40] } })
	 s:add ({{ type = "callfunc", func = curry(startDialogue, { dialogueId="lookout", nodeId=2 })}})
	 s:setsequence()
	 return s	
end

function dialoguesLookout.thatsthreep()
	 s = Script.create("_dial")
	 s:add (say { character = characters.guybrush, lines = { d[47] } })
	 s:add (say { character = characters.lookout, lines = { d[49] } })
	 s:add ({{ type = "callfunc", func = curry(startDialogue, { dialogueId="lookout", nodeId=2 })}})
	 s:setsequence()
	 return s	
end