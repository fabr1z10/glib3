-- voodoo lady dialogue

dialoguesVoodooLady = {}

local d = strings.dialogues.voodoolady.text

function helper(s)
	s:adds( {
		{ type="callfunc", func = curry (setActive, {id = "mainbg", active=true })}
	})
	s:addp({
        { type= "walkto", actor="player", pos ={205, 40}},
		{ type= "scroll", cam ="maincam", by = {-176, 0}, speed = 50 }
    })
	s:addb({ type="callfunc", func = curry (setActive, {id = "bg2", active=false })}, 2)
	s:adds({
		{ type = "callfunc", func = resumePlay }
	})
	return s
end

function dialoguesVoodooLady.leave() 
	
	s = Script.create("_dial")
	
	s:adds( {
		say2 {character = "voodoolady",lines = {d[5], d[6]}, animstart="talk", animend="idle"}
	})
	return helper(s)
	-- 	{ type="callfunc", func = curry (setActive, {id = "mainbg", active=true })}
	-- })
	-- s:addp({
 --        { type= "walkto", actor="player", pos ={205, 40}},
	-- 	{ type= "scroll", cam ="maincam", by = {-176, 0}, speed = 50 }
 --    })
	-- s:addb({ type="callfunc", func = curry (setActive, {id = "bg2", active=false })}, 2)
	-- s:adds({
	-- 	{ type = "callfunc", func = resumePlay }
	-- })
	-- return s

end

function dialoguesVoodooLady.myname() 
	
	s = Script.create("_dial")
	s:adds( {
		say2 {character = "voodoolady",lines = {d[8], d[9], d[10], d[11], d[12], d[13], d[14], d[15],d[16], d[17]}, animstart="talk", animend="idle"},
		{ type= "callfunc", func = curry(startDialogue, { dialogueId="voodoolady", nodeId=2 })}
	})
	return s

end

function dialoguesVoodooLady.future() 
	
	s = Script.create("_dial")
	s:adds( {
		say2 {character = "voodoolady",lines = {d[22],d[23], d[24]}, animstart="talk", animend="idle"},
		{ type= "callfunc", func = curry(startDialogue, { dialogueId="voodoolady", nodeId=3 })}
	})
	return s

end

function dialoguesVoodooLady.tricks() 
	
	s = Script.create("_dial")
	s:adds( {
		say2 {character ="guybrush", lines ={d[18]} },
		say2 {character = "voodoolady",lines = {d[20], d[21]}, animstart="talk", animend="idle"},
		{ type= "callfunc", func = curry(startDialogue, { dialogueId="voodoolady", nodeId=1 })}
	})
	return s

end

function dialoguesVoodooLady.no() 
	dialogues.voodoolady[1].lines[4].active= true
	s = Script.create("_dial")
	s:adds( {
		say2 {character ="guybrush", lines ={d[26]} },
		say2 {character = "voodoolady",lines = {d[27]}, animstart="talk", animend="idle"},
		{ type= "callfunc", func = curry(startDialogue, { dialogueId="voodoolady", nodeId=1 })}
	})
	return s

end

function dialoguesVoodooLady.yes() 
	s = Script.create("_dial")
	s:adds( {
		say2 {character ="guybrush", lines ={d[25]} },
		say2 {character = "voodoolady",lines = {d[29]}, animstart="talk", animend="idle"},
		{ type = "animate", actor ="voodooladybody", anim="raisehands", loop = 1 },
		{ type = "animate", actor ="voodooladybody", anim="idle" },
		say2 {character = "voodoolady",lines = {d[30], d[31]}, animstart="talk", animend="idle"},
		say2 {character ="guybrush", lines ={d[32]} },
		say2 {character = "voodoolady",lines = {d[33]}, animstart="talk", animend="idle"},
		say2 {character ="guybrush", lines ={d[34], d[35]} },
		{ type = "animate", actor ="voodooladybody", anim="raisehands", loop = 1 },
		{ type = "animate", actor ="voodooladybody", anim="idle" },
		say2 {character = "voodoolady",lines = {d[36]}, animstart="talk", animend="idle"},
		say2 {character ="guybrush", lines ={d[37]} },
		say2 {character = "voodoolady",lines = {d[38]}, animstart="talk", animend="idle"},
		say2 {character ="guybrush", lines ={d[39]} },
		say2 {character = "voodoolady",lines = {d[40], d[41]}, animstart="talk", animend="idle"},
		{ type = "animate", actor ="voodooladybody", anim="raisehands", loop = 1 },
		{ type = "animate", actor ="voodooladybody", anim="idle" },
		say2 {character = "voodoolady",lines = {d[42],d[43],d[44],d[45]}, animstart="talk", animend="idle"},
		say2 {character ="guybrush", lines ={d[46], d[47]} },
		say2 {character = "voodoolady",lines = {d[48],d[49],d[50],d[51]}, animstart="talk", animend="idle"},
		{ type="delay", sec=1},
		{ type="callfunc", func = curry (setActive, {id = "voodooladybody", active=false })},
		{ type="callfunc", func = curry (setActive, {id = "voodoolady", active=false })},
		{ type="delay", sec=1},
		say2 {character ="guybrush", lines ={d[37]} },

	})
	return helper(s)

end