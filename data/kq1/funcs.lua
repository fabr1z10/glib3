
function enterWater() 
	-- play enter water script
 	local s = script:new("_enterwater")
	-- disbale walking graham
	local a = monkey.getEntity("graham")
	a:setactive(false)
	local b = monkey.getEntity("drowning_graham")
	b:setactive(true)
	b:setposition(a.x,a.y, a.z)
	variables.drown = true
    s.actions = {
		[1] = { type = "delay", sec = 2},
		[2] = {type="callfunc", func = function() print("Drown!") end, after={1} }
	}
	monkey.play(s)
end

function startSwimming() 
	if (variables.drown == true) then
		local s = script:new("_startswim")
	    s.actions = {
			[1] = { type = "killscript", script="_enterwater" }
		}
		monkey.play(s)
		variables.drown = false

	end
end