-- lookout dialogue

dialoguesLowmoralfiber = {}

local d = strings.dialogues.lowmoralfiber.text

function dialoguesLowmoralfiber.nicerat(n) 
	s = Script.create("_dial")
	s:adds( {
		say2 {character = "guybrush", lines = {d[n]}},
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

function dialoguesLowmoralfiber.intelligentrats(n) 
	s = Script.create("_dial")
	s:adds({
		say2 { character = "guybrush", lines = { d[n] }},
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

function dialoguesLowmoralfiber.amazing(n)
	s = Script.create("_dial")
	s:adds({
		say2 { character = "guybrush", lines = { d[n[1]] }},
		say2 { character="lmf3", lines = {d[n[2]], d[22], d[23]}, animstart="talk", animend="idle" },
		say2 { character="lmf1", lines = {d[24]}, animstart="looknorth", animend="idle2" },
		{ type= "callfunc", func = curry(startDialogue, { dialogueId="lowmoralfiber", nodeId=1 })}
	})
	return s
end

function dialoguesLowmoralfiber.vermin()
	dialogues.lowmoralfiber[1].lines[1].active= false
	dialogues.lowmoralfiber[1].lines[6].active= true
	s = Script.create("_dial")
	s:adds({
		say2 { character = "guybrush", lines = { d[2] }},
		say2 { character = "rat", lines = { d[34], d[35] }, noanim = true },
		say2 { character="lmf1", lines = {d[36], d[37]}, animstart="looknorth", animend="idle2" },
		say2 { character="lmf3", lines = {d[38]}, animstart="talk", animend="idle" },
		say2 { character="lmf2", lines = {d[39]}, animstart="laugh", animend="laugh" }
	})
	insertLaughSequence(s)
	s:adds({
		{ type = "callfunc", func = resumePlay }
	})
	return s
end

function dialoguesLowmoralfiber.areyoupirates()
	s = Script.create("_dial")
	s:adds({
		say2 { character = "guybrush", lines = { d[4] }},
		{ type="animate", actor="lmf1", anim="looknorth"},
		{ type="animate", actor="lmf2", anim="idlefront"},
		{ type="animate", actor="lmf3", anim="idlefront"},
		{ type="delay", sec=1}, 
		say2 { character="lmf3", lines = {d[43]}, animstart="talk", animend="idle" },
		{ type="animate", actor="lmf2", anim="laugh"},
		say2 { character="lmf1", lines = {d[44]}, animstart="talk", animend="idle2" },
	})
	insertLaughSequence(s)
	s:adds({
		{ type="animate", actor="lmf1", anim="looknorth"},
		say2 { character="lmf3", lines = {d[45], d[46]}, animstart="talk", animend="idle" },
		say2 { character="lmf1", lines = {d[47]}, animstart="talk", animend="idle2" },
		{ type= "callfunc", func = curry(startDialogue, { dialogueId="lowmoralfiber", nodeId=5 })}
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

function dialoguesLowmoralfiber.getminutes(n)
	s = Script.create("_dial")
	s:adds({
		say2 { character = "guybrush", lines = { d[n] }},
		say2 { character="lmf3", lines = {d[42]}, animstart="talk", animend="idle" },
		{ type= "callfunc", func = curry(pickupItem, "minutes" )},
		{ type= "callfunc", func = curry(pickupItemQty, {name = "pieceofeight", qty = 2})},
			{ type= "callfunc", func = curry(startDialogue, { dialogueId="lowmoralfiber", nodeId=1 })}
	})
	return s
end

function dialoguesLowmoralfiber.leave(n)
	s = Script.create("_dial")
	s:adds({
		say2 { character = "guybrush", lines = { d[n] }},
		{ type = "callfunc", func = resumePlay }

	})
	return s
end

function dialoguesLowmoralfiber.nothanks() 
	dialogues.lowmoralfiber[1].lines[7].active= true
	s = Script.create("_dial")
	s:adds({
		say2 { character = "guybrush", lines = { d[31] }},
		say2 { character="lmf3", lines = {d[66]}, animstart="talk", animend="idle" },
		{ type= "callfunc", func = curry(startDialogue, { dialogueId="lowmoralfiber", nodeId=1 })}
	})
	return s
end

function dialoguesLowmoralfiber.onmyway() 
	dialogues.lowmoralfiber[1].lines[7].active= true
	return dialoguesLowmoralfiber.leave(32)
end

function dialoguesLowmoralfiber.keg() 
	s = Script.create("_dial")
	s:adds({
		say2 { character = "guybrush", lines = { d[48] }},
	})
	s:addp({
		{ type="animate", actor="lmf2", anim="idlefront"},
		say2 { character="lmf1", lines = {d[52]}, animstart="talk", animend="looknorth" },
		say2 { character="lmf3", lines = {d[53]}, animstart="talk", animend="idlefront" },
	})
	s:addb({ type="delay", sec=1}, 3)
	s:addp({
		say2 { character="lmf1", lines = {d[53]}, animstart="talk", animend="looknorth" },
		say2 { character="lmf3", lines = {d[52]}, animstart="talk", animend="idlefront" },
	})
	s:addb({ type="delay", sec=1}, 2)
	s:adds({
		{ type="animate", actor="lmf2", anim="idle"},
		say2 { character="lmf3", lines = {d[54], d[55]}, animstart="talk", animend="idle" },
		{ type= "callfunc", func = curry(startDialogue, { dialogueId="lowmoralfiber", nodeId=1 })}
	})
	return s
end

function dialoguesLowmoralfiber.winesauce() 
	dialogues.lowmoralfiber[1].lines[6].active= true
	s = Script.create("_dial")
	s:adds({
		say2 { character = "guybrush", lines = { d[9] }},
		{ type="animate", actor="lmf2", anim="laugh"},	
		say2 { character="lmf1", lines = {d[59]}, animstart="talk", animend="idle2" },
	})
	insertLaughSequence(s)
	s:adds({
		{ type = "callfunc", func = resumePlay }
	})
	return s
end

function dialoguesLowmoralfiber.pillage()
	s = Script.create("_dial")
	s:adds({
		say2 { character = "guybrush", lines = { d[51] }},
		{ type="animate", actor="lmf1", anim="looknorth"},
		{ type="animate", actor="lmf2", anim="idlefront"},
		say2 { character="lmf3", lines = {d[58]}, animstart="talk", animend="idlefront" },
		say2 { character="lmf1", lines = {d[59]}, animstart="talk", animend="looknorth" },
		say2 { character="lmf3", lines = {d[60]}, animstart="talk", animend="idlefront" },
		say2 { character="lmf1", lines = {d[61], d[62]}, animstart="talk", animend="looknorth" },
		say2 { character="lmf3", lines = {d[63]}, animstart="talk", animend="idlefront" },
		{ type="delay", sec = 1},
		{ type="animate", actor="lmf1", anim="idle2"},
		{ type="animate", actor="lmf2", anim="idle"},
		say2 { character="lmf3", lines = {d[64], d[65]}, animstart="talk", animend="idle" },
		{ type= "callfunc", func = curry(startDialogue, { dialogueId="lowmoralfiber", nodeId=1 })}
	})
	return s
end