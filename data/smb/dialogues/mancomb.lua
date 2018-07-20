-- lookout dialogue

dialoguesMancomb = {}

local d = strings.dialogues.mancomb.text

function dialoguesMancomb.leave() 
	s = Script.create("_dial")
	s:add (say { character = "guybrush", lines = { d[6] }, noanim =true  })
	s:add (say { character = "mancomb", lines = {d[6]}, noanim = true})
	s:add ({ { type="animate", actor="mancomb", anim="blink", loop=1}, { type="animate", actor="mancomb", anim="idle" }})
	s:add (say { character = "mancomb", lines = {d[7]}, noanim = true})
	s:add ({{ type = "gotoroom", room = "scummbar" }})
	s:setsequence()
	return s
end

function dialoguesMancomb.leave2() 
	s = Script.create("_dial")
	s:add (say { character = "guybrush", lines = { d[44] }, noanim =true  })
	s:add (say { character = "mancomb", lines = {d[6]}, noanim = true})
	s:add ({ { type="animate", actor="mancomb", anim="blink", loop=1}, { type="animate", actor="mancomb", anim="idle" }})
	s:add (say { character = "mancomb", lines = {d[7]}, noanim = true})
	s:add ({{ type = "gotoroom", room = "scummbar" }})
	s:setsequence()
	return s
end

function dialoguesMancomb.noneofyourbusiness() 
	s = Script.create("_dial")
	s:add (say { character = "guybrush", lines = { d[22] }, noanim =true  })
	s:add (say { character = "mancomb", lines = {d[57]}, noanim = true})
	s:add ({ { type="animate", actor="mancomb", anim="blink", loop=1}, { type="animate", actor="mancomb", anim="idle" }})
	s:add ({{ type = "gotoroom", room = "scummbar" }})
	s:setsequence()
	return s
end

function dialoguesMancomb.insulted() 
	dialogues.mancomb[1].lines[6].active= true
	s = Script.create("_dial")
	s:add (say { character = "guybrush", lines = { d[15] }, noanim =true  })
	s:add ({ { type="animate", actor="mancomb", anim="idle", loop=1} })
	s:add (say { character = "mancomb", lines = {d[47]}, noanim = true})
	s:add ({ { type="animate", actor="mancomb", anim="blink", loop=1}, { type="animate", actor="mancomb", anim="idle" }})
	s:add (say { character = "mancomb", lines = {d[48]}, noanim = true})
	s:add ({ { type="animate", actor="mancomb", anim="blink", loop=1}, { type="animate", actor="mancomb", anim="idle" }})
	s:add ({{ type = "gotoroom", room = "scummbar" }})
	s:setsequence()
	return s
end

-- called when you've done talking to Mancomb... he says grog is going flat
function helper3() 
	variables.doneTalkMancomb = true	
	s:add (say { character = "mancomb", lines = {d[38]}, noanim = true})	
	s:add ({{ type = "gotoroom", room = "scummbar" }})
	s:setsequence()
	return s	
end

function dialoguesMancomb.leave4() 	
	s = Script.create("_dial")
	s:add (say { character = "guybrush", lines = { d[56] }, noanim =true  })
	s:add (say { character = "mancomb", lines = {d[6], d[7]}, noanim = true})
	s:add ({ { type="animate", actor="mancomb", anim="blink", loop=1}, { type="animate", actor="mancomb", anim="idle" }})
	return helper3(s)
end


function dialoguesMancomb.gothere() 	
	s = Script.create("_dial")
	s:add (say { character = "guybrush", lines = { d[36] }, noanim =true  })
	s:add (say { character = "mancomb", lines = {d[35], d[36]}, noanim = true})
	s:add ({ { type="animate", actor="mancomb", anim="blink", loop=1}, { type="animate", actor="mancomb", anim="idle" }})
	s:add (say { character = "mancomb", lines = {d[37]}, noanim = true})	
	return helper3(s)
end

function dialoguesMancomb.charge() 
	s = Script.create("_dial")
	s:add (say { character = "guybrush", lines = { d[5] }, noanim =true  })
	s:add (say { character = "mancomb", lines = {d[40], d[41]}, noanim = true})
	s:add ({ { type="animate", actor="mancomb", anim="blink", loop=1}, { type="animate", actor="mancomb", anim="idle" }})
	s:add ({{ type = "callfunc", func = curry(startDialogue, { dialogueId="mancomb", nodeId=5 })}})	
	s:setsequence()
	return s
end

function dialoguesMancomb.guybrush() 
	s = Script.create("_dial")
	s:add (say { character = "guybrush", lines = { d[3] }, noanim =true  })
	s:add (say { character = "mancomb", lines = {d[9]}, noanim = true})
	s:add ({ { type="animate", actor="mancomb", anim="smile", loop=1} })
	s:add (say { character = "mancomb", lines = {d[10], d[11]}, noanim = true})
	s:add ({{ type = "callfunc", func = curry(startDialogue, { dialogueId="mancomb", nodeId=2 })}})	
	s:setsequence()
	return s
end

function dialoguesMancomb.ilikeguybrush() 
	s = Script.create("_dial")
	s:add (say { character = "guybrush", lines = { d[12] }, noanim =true  })
	s:add ({ { type="animate", actor="mancomb", anim="idle", loop=1} })
	s:add (say { character = "mancomb", lines = {d[16]}, noanim = true})
	s:add ({{ type = "callfunc", func = curry(startDialogue, { dialogueId="mancomb", nodeId=2 })}})	
	s:setsequence()
	return s
end

function dialoguesMancomb.dumbname() 
	s = Script.create("_dial")
	s:add (say { character = "guybrush", lines = { d[14] }, noanim =true  })
	s:add ({ { type="animate", actor="mancomb", anim="idle", loop=1} })
	s:add (say { character = "mancomb", lines = {d[45], d[46]}, noanim = true})
	s:add ({ { type="animate", actor="mancomb", anim="blink", loop=1}, { type="animate", actor="mancomb", anim="idle" }})
	s:add ({{ type = "callfunc", func = curry(startDialogue, { dialogueId="mancomb", nodeId=1 })}})	
	s:setsequence()
	return s
end

function dialoguesMancomb.yourname() 
	s = Script.create("_dial")
	s:add (say { character = "guybrush", lines = { d[13] }, noanim =true  })
	s:add ({ { type="animate", actor="mancomb", anim="idle", loop=1} })
	return helper2(s)
end

function dialoguesMancomb.whatwasyourname() 
	s = Script.create("_dial")
	s:add (say { character = "guybrush", lines = { d[49] }, noanim =true  })
	return helper2(s)
end

function helper2(s)
	s:add (say { character = "mancomb", lines = {d[17]}, noanim = true})
	if (variables.mancombKnowsWannabePirate == true) then
		s:add ({{ type = "callfunc", func = curry(startDialogue, { dialogueId="mancomb", nodeId=1 })}})	
	else
		s:add (say { character = "mancomb", lines = {d[18]}, noanim = true})
		s:add ({ { type="animate", actor="mancomb", anim="blink", loop=1}, { type="animate", actor="mancomb", anim="idle" }})
		s:add ({{ type = "callfunc", func = curry(startDialogue, { dialogueId="mancomb", nodeId=3 })}})	
	end
	s:setsequence()
	return s
end

function dialoguesMancomb.pirate() 	
	s = Script.create("_dial")
	s:add (say { character = "guybrush", lines = { d[19] }, noanim =true  })
	s:add (say { character = "mancomb", lines = {d[23]}, noanim = true})
	return helper1(s)
end

function dialoguesMancomb.fortune() 
	s = Script.create("_dial")
	s:add (say { character = "guybrush", lines = { d[20] }, noanim =true  })
	s:add (say { character = "mancomb", lines = {d[28]}, noanim = true})
	return helper1(s)
end

function dialoguesMancomb.dontknow() 
	s = Script.create("_dial")
	s:add (say { character = "guybrush", lines = { d[21] }, noanim =true  })
	s:add (say { character = "mancomb", lines = {d[50], d[51]}, noanim = true})
	return helper1(s)
end

function dialoguesMancomb.crew() 
	s = Script.create("_dial")
	s:add (say { character = "guybrush", lines = { d[4] }, noanim =true  })
	s:add (say { character = "mancomb", lines = {d[29], d[30]}, noanim = true})
	return helper1(s)
end

function dialoguesMancomb.pirateleaders() 	
	s = Script.create("_dial")
	s:add (say { character = "guybrush", lines = { d[42] }, noanim =true  })
	return helper1(s)
end

function helper1(s)
	variables.mancombKnowsWannabePirate = true
	dialogues.mancomb[1].lines[3].active= false
	dialogues.mancomb[1].lines[5].active= true
	s:add ({ { type="animate", actor="mancomb", anim="blink", loop=1}, { type="animate", actor="mancomb", anim="idle" }})
	s:add (say { character = "mancomb", lines = {d[24], d[25]}, noanim = true})
	s:add ({ { type="animate", actor="mancomb", anim="blink", loop=1}, { type="animate", actor="mancomb", anim="idle" }})
	s:add (say { character = "mancomb", lines = {d[26]}, noanim = true})
	s:add ({ { type="animate", actor="mancomb", anim="blink", loop=1}, { type="animate", actor="mancomb", anim="idle" }})
	s:add ({{ type = "callfunc", func = curry(startDialogue, { dialogueId="mancomb", nodeId=1 })}})	
	s:setsequence()
	return s
end

function dialoguesMancomb.governor(n) 	
	s = Script.create("_dial")
	s:add (say { character = "guybrush", lines = { d[n] }, noanim =true  })
	s:add (say { character = "mancomb", lines = {d[31], d[32]}, noanim = true})
	s:add ({ { type="animate", actor="mancomb", anim="blink", loop=1}, { type="animate", actor="mancomb", anim="idle" }})	
	s:add (say { character = "mancomb", lines = {d[33]}, noanim = true})
	return helper1(s)
end

function dialoguesMancomb.whynot() 	
	s = Script.create("_dial")
	s:add (say { character = "guybrush", lines = { d[34] }, noanim =true  })
	s:add (say { character = "mancomb", lines = {d[52], d[53]}, noanim = true})
	s:add ({ { type="animate", actor="mancomb", anim="blink", loop=1}, { type="animate", actor="mancomb", anim="idle" }})	
	s:add ({{ type = "callfunc", func = curry(startDialogue, { dialogueId="mancomb", nodeId=6})}})	
	s:setsequence()
	return s
end

function helper5(s) 
	s:add ({ { type="animate", actor="mancomb", anim="blink", loop=1}, { type="animate", actor="mancomb", anim="idle" }})	
	s:add (say { character = "mancomb", lines = {d[59], d[60]}, noanim = true})
	s:add ({ { type="animate", actor="mancomb", anim="blink", loop=1}, { type="animate", actor="mancomb", anim="idle" }})	
	s:add (say { character = "mancomb", lines = {d[61]}, noanim = true})
	s:add ({ { type="animate", actor="mancomb", anim="smile", loop=1} })
	s:add (say { character = "mancomb", lines = {d[62]}, noanim = true})
	s:add ({ { type="animate", actor="mancomb", anim="idle", loop=1} })
	s:add ({{ type = "callfunc", func = curry(startDialogue, { dialogueId="mancomb", nodeId=1})}})	
	s:setsequence()
	return s
end


function dialoguesMancomb.howsthat()
	s = Script.create("_dial")
	s:add (say { character = "guybrush", lines = { d[54] }, noanim =true  })
	return helper5(s)
end

function dialoguesMancomb.whoisthispirate() 	
	s = Script.create("_dial")
	s:add (say { character = "guybrush", lines = { d[55] }, noanim =true  })
	s:add (say { character = "mancomb", lines = {d[58]}, noanim = true})
	return helper5(s)

end

function dialoguesMancomb.iamwelcome() 	
	s = Script.create("_dial")
	s:add (say { character = "guybrush", lines = { d[35] }, noanim =true  })
	s:add (say { character = "mancomb", lines = {d[64], d[65]}, noanim = true})
	s:add ({ { type="animate", actor="mancomb", anim="blink", loop=1}, { type="animate", actor="mancomb", anim="idle" }})	
	s:add ({{ type = "callfunc", func = curry(startDialogue, { dialogueId="mancomb", nodeId=1})}})	
	s:setsequence()
	return s
end