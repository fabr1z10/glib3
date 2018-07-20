-- lookout dialogue

dialoguesLowmoralfiber = {}

local d = strings.dialogues.lowmoralfiber.text

function dialoguesLowmoralfiber.nicerat() 
	s = Script.create("_dial")
	s:adds( {
		say2 {character = "guybrush", lines = {d[1]}},
		say2 {character = "lmf1",lines = {d[6]}, animstart="talk", animend="idle2"},
		{ type= "callfunc", func = curry(startDialogue, { dialogueId="lowmoralfiber", nodeId=2 })}
	})
	return s

end

-- add laugh sequence
function insertLaughSequence(s) 
	s:adds ({
		{ type="animate", actor="lmf2", anim="laugh" },	
		{ type="delay", sec = 0.5 }, 
		{ type="animate", actor="lmf3", anim="punch1", loop=1 }
	})
	s:addp ({
		{ type="animate", actor="lmf3", anim="punch2" },
		{ type="animate", actor="lmf2", anim="hit"},
	})
	s:addb({type="delay", sec = 0.5 }, 2)

	s:adds({ 
		{type = "animate", actor="lmf3", anim="idle"},
		{type = "animate", actor="lmf2", anim="idle"}
	})
end

function dialoguesLowmoralfiber.intelligentrats() 
	s = Script.create("_dial")
	s:adds({
		say2 { character = "guybrush", lines = { d[7] }},
		say2 { character = "lmf1", lines = {d[11]}, animstart="talk", animend="idle2" },
		say2 { character = "lmf2", lines = {d[12]}, animstart="laugh", animend="laugh" }
	})
	insertLaughSequence(s)
	s:adds ({ 
		say2 {character="lmf1", lines = {d[13]}, animstart="looknorth", animend="idle2" },
		say2 {character="lmf1", lines = {d[14]}, animstart="talk", animend="idle2" },
		say2 {character="lmf3", lines = {d[15]}, animstart="talkfront", animend="talk" },
		say2 {character="lmf3", lines = {d[16]}, animstart="talk", animend="idle" },
		{ type= "animate", actor="lmf1", anim="idle"},
		{ type= "callfunc", func = curry(startDialogue, { dialogueId="lowmoralfiber", nodeId=3 })}
	})
	return s
end

function dialoguesLowmoralfiber.amazing()
	s = Script.create("_dial")
	s:adds({
		say2 { character = "guybrush", lines = { d[17] }},
		say2 { character="lmf3", lines = {d[21], d[22], d[23]}, animstart="talk", animend="idle" },
		say2 { character="lmf1", lines = {d[24]}, animstart="looknorth", animend="idle2" },
		{ type= "callfunc", func = curry(startDialogue, { dialogueId="lowmoralfiber", nodeId=1 })}
	})
	return s
end

function dialoguesLowmoralfiber.sneaky() 
	s = Script.create("_dial")
	s:adds({
		say2 { character = "guybrush", lines = { d[3] }},
		say2 { character="lmf3", lines = {d[25]}, animstart="talk", animend="idle" },
		{ type="animate", actor="lmf3", anim="openjacket", loop = 1},
		say2 { character="lmf3", lines = {d[26]}, animstart="talk", animend="idle" },
		{ type="animate", actor="lmf1", anim="looknorth"},
		{ type="animate", actor="lmf2", anim="idlefront"},
		{ type="animate", actor="lmf3", anim="idlefront"},
		{ type="delay", sec=1}, 
		{ type="animate", actor="lmf1", anim="idle2"},
		{ type="animate", actor="lmf2", anim="laugh"},
		say2 { character="lmf3", lines = {d[27]}, animstart="talk", animend="talk" },
		{ type="animate", actor="lmf3", anim="openjacket", loop = 1},
		say2 { character="lmf3", lines = {d[28], d[29]}, animstart="talk", animend="idle" },
	})
	insertLaughSequence(s)
	s:adds({
		say2 { character="lmf3", lines = {d[30]}, animstart="talk", animend="idle" },
		{ type= "callfunc", func = curry(startDialogue, { dialogueId="lowmoralfiber", nodeId=4 })}
	})
	return s
end