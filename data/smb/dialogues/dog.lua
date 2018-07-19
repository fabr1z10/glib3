-- lookout dialogue

dialoguesDog = {}

local d = strings.dialogues.dog.text

function dialoguesDog.grrr() 
	s = Script.create("_dial")
	s:add (say { character = "guybrush", lines = { d[5] } })
	s:add (say { character = "dog", lines = {d[6]}, noanim = true})
	s:add ({{ type = "callfunc", func = resumePlay }})
	s:setsequence()
	return s
end

function dialoguesDog.yip() 
	s = Script.create("_dial")
	s:add (say { character = "guybrush", lines = { d[17] } })
	s:add (say { character = "dog", lines = {d[13]}, noanim = true})
	s:add ({{ type = "callfunc", func = resumePlay }})
	s:setsequence()
	return s
end

function dialoguesDog.woof() 
	s = Script.create("_dial")
	s:add (say { character = "guybrush", lines = { d[2] } })
	s:add (say { character = "dog", lines = {d[7], d[8], d[9], d[10], d[11], d[12], d[13] }, noanim = true})
	s:add ({{ type = "callfunc", func = curry(startDialogue, { dialogueId="dog", nodeId=2 })}})
	s:setsequence()
	return s
end

function dialoguesDog.arf() 
	s = Script.create("_dial")
	s:add (say { character = "guybrush", lines = { d[2] } })
	s:add (say { character = "dog", lines = {d[33], d[34], d[9], d[10], d[11], d[12], d[13] }, noanim = true})
	s:add ({{ type = "callfunc", func = curry(startDialogue, { dialogueId="dog", nodeId=2 })}})
	s:setsequence()
	return s
end

function dialoguesDog.ruff() 
	s = Script.create("_dial")
	s:add (say { character = "guybrush", lines = { d[4] } })
	s:add (say { character = "dog", lines = {d[35], d[9], d[10], d[11], d[12], d[13] }, noanim = true})
	s:add ({{ type = "callfunc", func = curry(startDialogue, { dialogueId="dog", nodeId=2 })}})
	s:setsequence()
	return s
end

function dialoguesDog.worf() 
	s = Script.create("_dial")
	s:add (say { character = "guybrush", lines = { d[14] } })
	s:add (say { character = "dog", lines = {d[18] }, noanim = true})
	s:add ({{ type = "callfunc", func = resumePlay }})
	s:setsequence()
	return s
end

function dialoguesDog.aroof() 
	s = Script.create("_dial")
	s:add (say { character = "guybrush", lines = { d[15] } })
	s:add (say { character = "dog", lines = {d[19], d[20] }, noanim = true})
	s:add ({{ type = "callfunc", func = resumePlay }})
	s:setsequence()
	return s
end

function dialoguesDog.lechuck() 
	variables.doneTalkDog = true
	s = Script.create("_dial")
	s:add (say { character = "guybrush", lines = { d[16] } })
	s:add (say { character = "dog", lines = {d[21], d[22], d[23], d[24], d[25], d[26], d[27], d[28], d[29], d[30], d[31], d[32] }, noanim = true})
	s:add ({{ type = "callfunc", func = resumePlay }})
	s:setsequence()
	return s
end