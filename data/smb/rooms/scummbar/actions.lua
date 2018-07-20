function openBarKitchen() 
	-- if the door is already open, nothing to do
	if (objects.door_bar_kitchen.isopen() == false) then
		s = Script.create("_cook2")
		s:add( {
			{ type="suspendscript", script ="_cook" },
		    { type="animate", actor="player", anim="operate_right" },
            { type="delay", sec="0.5" },
            { type="animate", actor = objects.door_bar_kitchen.tag, anim = "open" },
            { type="animate", actor="player", anim= "idle_right" },
			{ type="showmessage", color = objects.cook.color, message = strings.dialogues.cook[1], pos = {600,30,0} },
			{ type="showmessage", color = objects.cook.color, message = strings.dialogues.cook[3], pos = {600,30,0} },
            { type="animate", actor = objects.door_bar_kitchen.tag, anim = "close" },
			{ type="resumescript", script ="_cook" }
		})
		s:setsequence()
		monkey.play(s)
	end 
end

function enterBarKitchen() 
	
	-- if door is closed, nothing happens
	if (objects.door_bar_kitchen.isopen() == false) then
		-- close, do nothing
		return {}
	else
		cook = monkey.getEntity("cook")
		if (cook.isnil) then
			-- cook is in the kitchen!!! it can't be
			return {}
		else
			if (cook.x > 320) then
     			local anim = cook.anim
     			local fx = cook.flipx
     			print ("COOK IS AROUND AND AT " .. cook.x .. " ANIM = " .. anim .. " fx = " .. tostring(fx))
     			
     			s = Script.create("_cook2")
         		s:add ({ {type = "suspendscript", script ="_cook" } })
     			s:add (turn { character = "cook", face = "east" })
     			s:add (say { character = "cook", lines = { strings.dialogues.cook[1], strings.dialogues.cook[2] }})
     			-- restore animation and flip
     			s:add ({ { type="animate", actor="cook", anim=anim, flipx = fx } })
     			s:add ({ { type = "resumescript", script ="_cook" }})
     			s:setsequence()
     			monkey.play(s)	
			else
				return changeRoom("kitchen")
			end
			

		end
	end


	

end

function talkToPirates() 
	local lines = variables.talkedToPirates and{strings.dialogues.pirates.text[40], strings.dialogues.pirates.text[41]} or {strings.dialogues.pirates.text[1]}
	local a = say { character = "ilp2", lines = lines, animstart ="talk", animend="idle" }
	table.insert (a, 
        { type = "callfunc", func = curry(startDialogue, { dialogueId="pirates", nodeId=1, init = true })}
    )
	return a
end

function talkToDog() 
	if (variables.doneTalkDog) then
		local a = say { character = "dog", lines = {strings.dialogues.dog.text[1] }, noanim = true}
		return a
	else 
		local a = say { character = "dog", lines = {strings.dialogues.dog.text[1] }, noanim = true}
		table.insert (a, 
	        { type = "callfunc", func = curry(startDialogue, { dialogueId="dog", nodeId=1, init = true })}
	    )
		return a
	end
end

function talkToLoom()
	if (variables.doneTalkLoom == true) then
		local a = say { character = "guybrush", lines = {strings.dialogues.loom_pirate.text[16] } }
		return a
	else
		return changeRoom("loom")
	end
end

function talkToEstevan()
	return changeRoom("estevan")
end

function talkToMancomb()
	if (variables.doneTalkMancomb == true) then
		local a = say { character = "guybrush", lines = {strings.dialogues.mancomb.text[39] } }
		return a
	else
		return changeRoom("mancomb")
	end	
end