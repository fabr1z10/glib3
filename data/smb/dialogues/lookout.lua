-- lookout dialogue

dialoguesLookout = {}

local d = strings.dialogues.lookout

function dialoguesLookout.start(i) 
	 s = Script.create("_dial")
	 s:add (say { character = characters.guybrush, lines = { d[i] } })
	 s:add (turn { character = characters.lookout, face = "south"} )
	 s:add (say { character = characters.lookout, lines = { d[5], d[6], d[7], d[8], d[9] } })
	 s:add ({{ type = "callfunc", func = curry(startDialogue, { dialogueId="lookout", nodeId=1 })}})
	 s:setsequence()
	 return s

end