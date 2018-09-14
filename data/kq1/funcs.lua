
function enterWater() 
	-- play enter water script
	if (variables.status == 0) then
	 	local s = script:new("_enterwater")
		-- disbale walking graham
		local a = monkey.getEntity("graham")
		a:setactive(false)
		local b = monkey.getEntity("drowning_graham")
		b:setactive(true)
		b:setposition(a.x,a.y, a.z)
		variables.status = 1
	    s.actions = {
			[1] = { type = "delay", sec = 2},
			[2] = {type="callfunc", func = function() print("Drown!") end, after={1} }
		}
		monkey.play(s)
	end
end

function exitWater() 
	if (variables.status == 2) then
		-- disbale swimming graham
		local a = monkey.getEntity("swimming_graham")
		a:setactive(false)
		local b = monkey.getEntity("graham")
		b:setactive(true)
		b:setposition(a.x,a.y, a.z)
		variables.status = 0
	end

end

function startSwimming() 
	if (variables.status == 1) then
		local s = script:new("_startswim")
	    s.actions = {
			[1] = { type = "killscript", script="_enterwater" }
		}
		monkey.play(s)
		variables.drown = false
		local a = monkey.getEntity("drowning_graham")
		a:setactive(false)
		local b = monkey.getEntity("swimming_graham")
		b:setactive(true)
		b:setposition(a.x,a.y, a.z)
		variables.status = 2
	end
end