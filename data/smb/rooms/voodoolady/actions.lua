local d = strings.dialogues.voodoolady.text

function gotoLady()
	local n = variables.talkedToVoodooLady and 7 or 1
	variables.talkedToVoodooLady = true
 	s = Script.create("_walk")
    s:adds({
		{ type="callfunc", func = startScript },
		{ type="callfunc", func = curry (setActive, {id = "bg2", active=true })}
	})
	s:addp({
        { type= "walkto", actor="player", pos ={125+176, 36}},
		{ type= "scroll", cam ="maincam", by = {176, 0}, speed = 50 }
    })
	s:addb({ type="callfunc", func = curry (setActive, {id = "mainbg", active=false })}, 2)
	s:adds({
		say2 { character="voodoolady", lines = {d[n]}, animstart="talk", animend="idle" },
		{ type= "callfunc", func = curry(startDialogue, { dialogueId="voodoolady", nodeId=1 })}
	})
	
	monkey.play(s)
end

function lookknickknacks() 
 	s = Script.create("_walk")
    s:adds({
		say2 {character ="guybrush", lines ={d[10], d[11], d[12], d[13]} },
		{ type="turn", actor="player", face="south" },
		say2 {character ="guybrush", lines ={d[14], d[15]} }
	})
	monkey.play(s)

end
