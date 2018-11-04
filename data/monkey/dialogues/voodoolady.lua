-- voodoo lady dialogue

dialoguesVoodooLady = {}

local d = strings.dialogues.voodoolady.text

function helper(s)
	return {
		[0] = { type= "callfunc", func = curry (setActive, {id = "mainbg", active=true })},
		[1] = { type= "walkto", actor="player", pos ={205, 40}, after= {0} },
		[2] = { type= "scroll", cam ="maincam", by = {-176, 0}, speed = 50, after={0} },
		[3] = { type= "callfunc", func = curry (setActive, {id = "bg2", active=false }), after={1,2}},
		[4] = { type= "callfunc", func = resumePlay }
	}
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
	return {
		[0] = say {character = "voodoolady",lines = {d[8], d[9], d[10], d[11], d[12], d[13], d[14], d[15],d[16], d[17]}, animstart="talk", animend="idle"},
		[1] = { type= "callfunc", func = curry(startDialogue, { dialogueId="voodoolady", nodeId=2 }), after = {0} }
	}

end

function dialoguesVoodooLady.future() 
	return {
		[0] = say {character = "voodoolady",lines = {d[22],d[23], d[24]}, animstart="talk", animend="idle"},
		[1] = { type= "callfunc", func = curry(startDialogue, { dialogueId="voodoolady", nodeId=3 }), after = {0} }
	}
end

function dialoguesVoodooLady.tricks() 
	return {
		[0] = say {character ="guybrush", lines ={d[18]} },
		[1] = say {character = "voodoolady",lines = {d[20], d[21]}, animstart="talk", animend="idle", after ={0}},
		[2] = { type= "callfunc", func = curry(startDialogue, { dialogueId="voodoolady", nodeId=1 }), after={1}}
	}
end

function dialoguesVoodooLady.no() 
	dialogues.voodoolady[1].lines[4].active= true
	return {
		[0] = say {character ="guybrush", lines ={d[26]} },
		[1] = say {character = "voodoolady",lines = {d[27]}, animstart="talk", animend="idle", after={0} },
		[2] = { type= "callfunc", func = curry(startDialogue, { dialogueId="voodoolady", nodeId=1 }), after={1}}
	}

end

function dialoguesVoodooLady.yes() 
	return {
		[0] = say {character ="guybrush", lines ={d[25]} },
		[1] = say {character = "voodoolady",lines = {d[29]}, animstart="talk", animend="idle", after={0} },
		[2] = { type = "animate", actor ="voodooladybody", anim="raisehands", loop = 1, after={1} },
		[3] = { type = "animate", actor ="voodooladybody", anim="idle", after={2} },
		[4] = say {character = "voodoolady",lines = {d[30], d[31]}, animstart="talk", animend="idle", after={3} },
		[5] = say {character ="guybrush", lines ={d[32]}, after={4} },
		[6] = say {character = "voodoolady",lines = {d[33]}, animstart="talk", animend="idle", after={5} },
		[7] = say {character ="guybrush", lines ={d[34], d[35]}, after={6} },
		[8] = { type = "animate", actor ="voodooladybody", anim="raisehands", loop = 1, after={7} },
		[9] = { type = "animate", actor ="voodooladybody", anim="idle", after={8} },
		[10] = say {character = "voodoolady",lines = {d[36]}, animstart="talk", animend="idle", after={9} },
		[11] = say {character ="guybrush", lines ={d[37]}, after={10} },
		[12] = say {character = "voodoolady",lines = {d[38]}, animstart="talk", animend="idle", after={11} },
		[13] = say {character ="guybrush", lines ={d[39]}, after={12} },
		[14] = say {character = "voodoolady",lines = {d[40], d[41]}, animstart="talk", animend="idle", after={13} },
		[15] = { type = "animate", actor ="voodooladybody", anim="raisehands", loop = 1, after={14} },
		[16] = { type = "animate", actor ="voodooladybody", anim="idle", after={15} },
		[17] = say2 {character = "voodoolady",lines = {d[42],d[43],d[44],d[45]}, animstart="talk", animend="idle", after={16} },
		[18] = say2 {character ="guybrush", lines ={d[46], d[47]}, after={17} },
		[19] = say2 {character = "voodoolady",lines = {d[48],d[49],d[50],d[51]}, animstart="talk", animend="idle", after={18} },
		[20] = { type="delay", sec=1, after={19} },
		[21] = { type="callfunc", func = curry (setActive, {id = "voodooladybody", active=false }), after = {20} },
		[22] = { type="callfunc", func = curry (setActive, {id = "voodoolady", active=false }), after={21}},
		[23] = { type="delay", sec=1, after={22} },
		[24] = say {character ="guybrush", lines ={d[37]}, after={23} },
	}
	
end