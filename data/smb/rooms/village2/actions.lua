function lookCitizen()	
	local a = say { character = "citizen", lines = { strings.village2[1] }, animstart ="talkfront", animend="idle"}
	return a	
end

function talkCitizen()
	local l = {}
	local startNode = 1
	if (variables.talkedToCitizen == 0) then
		l = { strings.dialogues.citizen.text[1] }
		variables.talkedToCitizen = 1
	elseif (variables.talkedToCitizen == 1) then
		l = { strings.dialogues.citizen.text[8], strings.dialogues.citizen.text[9] }
		startNode = 2
	else 
		l = { strings.dialogues.citizen.text[8], strings.dialogues.citizen.text[9], strings.dialogues.citizen.text[27], strings.dialogues.citizen.text[28] }
		startNode = 3
	end
	local a = say { character = "citizen", lines = l, animstart="talkside", animend="idleside" }	
	table.insert (a, 
		{ type = "callfunc", func = curry(startDialogue, { dialogueId="citizen", nodeId=startNode, init = true })}
	)
	return a
end