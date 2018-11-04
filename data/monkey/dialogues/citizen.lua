-- lookout dialogue

dialoguesCitizen = {}

local d = strings.dialogues.citizen.text

function dialoguesCitizen.what(n) 	
	s = Script.create("_dial")
	s:add (say { character = "guybrush", lines = { d[n] } })
	s:add (say { character = "citizen", lines = {d[6], d[7]}, animstart="talkside", animend="idle" })	
	s:add ({{ type = "callfunc", func = resumePlay }})
	s:setsequence()
	return s
	
end

function dialoguesCitizen.code()
	s = Script.create("_dial")
	s:add (say { character = "guybrush", lines = { d[4] } })
	s:add (say { character = "citizen", lines = {d[16], d[6], d[7]}, animstart="talkside", animend="idle" })	
	s:add ({{ type = "callfunc", func = resumePlay }})
	s:setsequence()
	return s
end

function dialoguesCitizen.somewhereelse()
	s = Script.create("_dial")
	s:add (say { character = "guybrush", lines = { d[13] } })
	s:add (say { character = "citizen", lines = {d[14], d[15]}, animstart="talkside", animend="idle" })	
	s:add ({{ type = "callfunc", func = resumePlay }})
	s:setsequence()
	return s
end

function helper1(s)
	variables.talkedToCitizen = 2
	s:add (say { character = "citizen", lines = {d[18]}, animstart="talkside", animend="talkside" })	
	s:add ({ 
		{ type="animate", actor="citizen", anim="openjacket", loop=1 }, 
		{ type="animate", actor="citizen", anim="openjacketidle" },
		{ type="delay", sec = 1}
	})
	s:add (say { character = "citizen", lines = {d[19]}, animstart="openjackettalk", animend="openjacketidle" })	
	s:add ({ 
		{ type="animate", actor="citizen", anim="closejacket", loop=1 }, 
		{ type="animate", actor="citizen", anim="idleside" },
		{ type="delay", sec = 0.5}
	})
	s:add (say { character = "citizen", lines = {d[20]}, animstart="talkside", animend="talkside" })	
	s:add ({ 
		{ type="animate", actor="citizen", anim="rollmap", loop=1 }, 
		{ type="animate", actor="citizen", anim="rollmapidle" },
		{ type="delay", sec = 1}
	})
	s:add (say { character = "citizen", lines = {d[21], d[22]}, animstart="rollmaptalk", animend="rollmapidle" })	
	s:add ({ 
		{ type="animate", actor="citizen", anim="unrollmap", loop=1 }, 
		{ type="animate", actor="citizen", anim="idleside" },
		{ type="delay", sec = 0.5}
	})
	s:add (say { character = "citizen", lines = {d[23]}, animstart="talkside", animend="idleside" })	
	s:add ({{ type = "callfunc", func = curry(startDialogue, { dialogueId="citizen", nodeId=3 })}})	
	s:setsequence()
	return s
end

function dialoguesCitizen.dominique()
	s = Script.create("_dial")
	s:add (say { character = "guybrush", lines = { d[5] } })
	s:add (say { character = "citizen", lines = {d[17]}, animstart="talkside", animend="talkside" })	
	return helper1(s)
end

function dialoguesCitizen.wantmap(n)
	s = Script.create("_dial")
	s:add (say { character = "guybrush", lines = { d[n] } })
	s:add (say { character = "citizen", lines = {d[29], d[30], d[31], d[32]}, animstart="talkside", animend="talkside" })	
	return helper1(s)
end

function dialoguesCitizen.sven()
	s = Script.create("_dial")
	s:add (say { character = "guybrush", lines = { d[11] } })
	s:add (say { character = "citizen", lines = {d[33]}, animstart="talkside", animend="talkside" })	
	return helper1(s)
end

function dialoguesCitizen.nomoney() 
	s = Script.create("_dial")
	s:add (say { character = "guybrush", lines = { d[24] } })
	s:add (say { character = "citizen", lines = {d[26]}, animstart="talkside", animend="idle" })	
	s:add ({{ type = "callfunc", func = resumePlay }})
	s:setsequence()
	return s
end

function dialoguesCitizen.nowant() 
	s = Script.create("_dial")
	s:add (say { character = "guybrush", lines = { d[25] } })
	s:add (say { character = "citizen", lines = {d[34], d[35]}, animstart="talkside", animend="idle" })	
	s:add ({{ type = "callfunc", func = resumePlay }})
	s:setsequence()
	return s
end