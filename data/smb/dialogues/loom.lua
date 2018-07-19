-- lookout dialogue

dialoguesLoom = {}

local d = strings.dialogues.loom_pirate.text

function dialoguesLoom.aye() 
	s = Script.create("_dial")
	s:add (say { character = "guybrush", lines = { d[2] }, noanim =true  })
	s:add (say { character = "loom_pirate", lines = {d[1]}, noanim = true})
	s:add ({ { type="animate", actor="loompirate", anim="blink", loop=1}, { type="animate", actor="loompirate", anim="idle" }})
	s:add ({{ type = "callfunc", func = curry(startDialogue, { dialogueId="loom_pirate", nodeId=1 })}})	
	s:setsequence()
	return s
end

function dialoguesLoom.hat() 
	s = Script.create("_dial")
	s:add (say { character = "guybrush", lines = { d[3] }, noanim =true  })
	s:add (say { character = "loom_pirate", lines = {d[1]}, noanim = true})
	s:add ({{ type = "callfunc", func = curry(startDialogue, { dialogueId="loom_pirate", nodeId=1 })}})	
	s:add ({ { type="animate", actor="loompirate", anim="blink", loop=1}, { type="animate", actor="loompirate", anim="idle" }})
	s:setsequence()
	return s
end

function dialoguesLoom.leave() 
	s = Script.create("_dial")
	s:add (say { character = "guybrush", lines = { d[5] }, noanim =true  })
	s:add (say { character = "loom_pirate", lines = {d[1]}, noanim = true})
	s:add ({{ type = "gotoroom", room = "scummbar" }})
	s:setsequence()
	return s
end

function dialoguesLoom.loom() 
	variables.doneTalkLoom = true
	dialogues.loom_pirate[1].lines[3].active= false
	dialogues.loom_pirate[1].lines[5].active= true
	s = Script.create("_dial")
	s:add (say { character = "guybrush", lines = { d[4] }, noanim =true  })
	s:add (say { character = "loom_pirate", lines = {d[6], d[7], d[8], d[9],d[10], d[11], d[12], d[13]}, animstart="smile", animend="idle"})
	s:add ({{ type = "callfunc", func = curry(startDialogue, { dialogueId="loom_pirate", nodeId=1 })}})	
	s:setsequence()
	return s
end


function dialoguesLoom.pitch() 
	s = Script.create("_dial")
	s:add (say { character = "guybrush", lines = { d[14] }, noanim =true  })
	s:add (say { character = "loom_pirate", lines = {d[15]}, noanim=true })
	s:add ({{ type = "callfunc", func = curry(startDialogue, { dialogueId="loom_pirate", nodeId=1 })}})	
	s:add ({ { type="animate", actor="loompirate", anim="blink", loop=1}, { type="animate", actor="loompirate", anim="idle" }})
	s:setsequence()
	return s
end