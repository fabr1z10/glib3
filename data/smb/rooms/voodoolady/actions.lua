local d = strings.voodoolady
local d1 = strings.dialogues.voodoolady.text

function gotoLady()
	local n = variables.talkedToVoodooLady and 7 or 1
	variables.talkedToVoodooLady = true
	local s = script:new()
	s.name="_walk"
 	s.actions = {
		[1] = { type= "callfunc", func = startScript },
		[2] = { type= "callfunc", func = curry (setActive, {id = "bg2", active=true }), after = {1} },
        [3] = { type= "walkto", actor="player", pos ={125+176, 36}, after={2} },
		[4] = { type= "scroll", cam ="maincam", by = {176, 0}, speed = 50, after={2} },
		[5] = { type= "callfunc", func = curry (setActive, {id = "mainbg", active=false }), after = {3,4} },
		[6] = say { character="voodoolady", lines = {d1[n]}, animstart="talk", animend="idle", after={5} },
		[7] = { type= "callfunc", func = curry(startDialogue, { dialogueId="voodoolady", nodeId=1 }), after = {6} }
	}
	s:dump()
    monkey.play(s)	
end

function lookknickknacks() 
	s = script:new()
 	s.actions = {
		[1] = say {character ="guybrush", lines ={d[10], d[11], d[12], d[13] }},
		[2] = { type = "turn", actor = "player", face = "south", after = {1} },
		[3] = say {character ="guybrush", lines ={d[14], d[15]}, after={2} }
	}
	return s

end
