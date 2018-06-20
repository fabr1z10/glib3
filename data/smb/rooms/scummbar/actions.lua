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
			{ type="showmessage", color = characters.cook.color, message = strings.dialogues.cook[1], pos = {600,30,0} },
			{ type="showmessage", color = characters.cook.color, message = strings.dialogues.cook[3], pos = {600,30,0} },
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
     			s:add (turn { character = characters.cook, face = "east" })
     			s:add (say { character = characters.cook, lines = { strings.dialogues.cook[1], strings.dialogues.cook[2] }})
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