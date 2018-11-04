function lookCitizen()
	local s = script:new()
	s.actions = {
		[1] = say { character = "citizen", lines = { strings.village2[1] }, animstart ="talkfront", animend="idle" }
	}	
	return s
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
	local s = script:new()
	s.actions = {
		[1] = say { character = "citizen", lines = l, animstart="talkside", animend="idleside" },
		[2] = { type = "callfunc", after={1}, func = curry(startDialogue, { dialogueId="citizen", nodeId=startNode, init = true })}
	}
	return s
end

function door_transport(args) 
	local s = script:new()
	s.actions = {
		
		[1] = { type = "animate", actor = args.doorfrom, anim="open" },
		[2] = { type = "delay", sec=0.5, after={1} },
		[3] = { type = "callfunc", func = curry(setActive, {id="player", active=false}), after={2} },
		[4] = { type = "animate", actor = args.doorfrom, anim="close", after={3} },
		[5] = { type = "scroll", cam ="maincam", to = args.dest, speed = 200, after={4} },
		[6] = { type = "animate", actor = args.doorto, anim="open", after={5} },
		[7] = { type = "delay", sec=0.5, after={6} },
		[8] = { type = "animate", actor = args.doorto, anim="close", after={7} },
		[9] = { type = "callfunc", func = curry(setActive, {id="player", active=true}), after={8} },
		[10] = { type = "move", actor ="player", to = args.playerdest, immediate = true, after={9} },
		[11] = { type = "animate", actor="player", anim = args.anim, flip = args.flip, after={10} }

		
		
		
		-- [9] = { type = "animate", actor = args.doorto, anim="close", after={8} },
	}
	return s
end