function openBarKitchen() 
	-- if the door is already open, nothing to do
	if (objects.door_bar_kitchen.isopen() == false) then
		s = script:new("_cook2")
		s.actions = {
			[1] = { type="suspendscript", script ="_cook" },
		    [2] = { type="animate", actor="player", anim="operate_right", after={1} },
            [3] = { type="delay", sec="0.5", after={2} },
            [4] = { type="animate", actor = objects.door_bar_kitchen.tag, anim = "open", after={3} },
            [5] = { type="animate", actor="player", anim= "idle_right", after={4} },
			[6] = { type="showmessage", color = objects.cook.color, message = strings.dialogues.cook[1], pos = {600,30,0}, after={5} },
			[7] = { type="showmessage", color = objects.cook.color, message = strings.dialogues.cook[3], pos = {600,30,0}, after={6} },
            [8] = { type="animate", actor = objects.door_bar_kitchen.tag, anim = "close", after={7} },
			[9] = { type="resumescript", script ="_cook", after={8} }
		}
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
     			
     			local s = script:new("_cook2")
     			s.actions = {
					[1] = {type = "suspendscript", script ="_cook" },
     				[2] = { type="turn", actor ="cook", face = "east", after={1} },
     				[3] = say { character = "cook", lines = { strings.dialogues.cook[1], strings.dialogues.cook[2] }, after={2} },
     				-- restore animation and flip
     				[4] = { type="animate", actor="cook", anim=anim, flipx = fx, after={3} },
     				[5] = { type= "resumescript", script ="_cook", after={4} },
     			}
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