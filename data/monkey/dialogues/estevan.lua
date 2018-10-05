-- lookout dialogue

dialoguesEstevan = {}

local d = strings.dialogues.estevan.text

function dialoguesEstevan.leave() 
	s = Script.create("_dial")
	s:add (say { character = "guybrush", lines = { d[5] }, noanim =true  })
	s:add (say { character = "estevan", lines = {d[7]}, noanim = true})
	s:add ({{ type = "gotoroom", room = "scummbar" }})
	s:setsequence()
	return s
end

function dialoguesLoom.iamguybrush() 
	dialogues.estevan[1].lines[1].active= false
	dialogues.estevan[1].lines[5].active= true
	s = Script.create("_dial")
	s:add (say { character = "guybrush", lines = { d[2] }, noanim =true  })
	s:add (say { character = "estevan", lines = {d[8]}, noanim = true})
	s:add ({ { type="animate", actor="estevan", anim="blink", loop=1}, { type="animate", actor="estevan", anim="idle" }})
	s:add ({{ type = "callfunc", func = curry(startDialogue, { dialogueId="estevan", nodeId=1 })}})	
	s:setsequence()
	return s
end

function dialoguesLoom.darts() 
	s = Script.create("_dial")
	s:add (say { character = "guybrush", lines = { d[3] }, noanim =true  })
	s:add (say { character = "estevan", lines = {d[10], d[11]}, noanim = true})
	s:add ({ { type="animate", actor="estevan", anim="blink", loop=1}, { type="animate", actor="estevan", anim="idle" }})
	s:add (say { character = "estevan", lines = {d[12], d[13]}, noanim = true})
	s:add ({ { type="animate", actor="estevan", anim="blink", loop=1}, { type="animate", actor="estevan", anim="idle" }})
	s:add ({{ type = "callfunc", func = curry(startDialogue, { dialogueId="estevan", nodeId=1 })}})	
	s:setsequence()
	return s
end

function dialoguesLoom.drink() 
	s = Script.create("_dial")
	s:add (say { character = "guybrush", lines = { d[4] }, noanim =true  })
	s:add (say { character = "estevan", lines = {d[14], d[15], d[16]}, noanim = true})
	s:add ({ { type="animate", actor="estevan", anim="blink", loop=1}, { type="animate", actor="estevan", anim="idle" }})
	s:add (say { character = "estevan", lines = {d[17], d[18]}, noanim = true})
	s:add ({ { type="animate", actor="estevan", anim="blink", loop=1}, { type="animate", actor="estevan", anim="idle" }})
	s:add ({{ type = "callfunc", func = curry(startDialogue, { dialogueId="estevan", nodeId=1 })}})	
	s:setsequence()
	return s
end

function dialoguesLoom.eye() 
	s = Script.create("_dial")
	s:add (say { character = "guybrush", lines = { d[9] }, noanim =true  })
	s:add (say { character = "estevan", lines = {d[19], d[20], d[21]}, noanim = true})
	s:add ({ { type="animate", actor="estevan", anim="blink", loop=1}, { type="animate", actor="estevan", anim="idle" }})
	s:add ({{ type = "callfunc", func = curry(startDialogue, { dialogueId="estevan", nodeId=1 })}})	
	s:setsequence()
	return s
end
