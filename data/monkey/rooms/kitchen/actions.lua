function openKitchenPierDoor()
	if (objects.door_kitchen_pier.isopen()) then
		return nil
	end
	local s = operateDoor {obj="door_kitchen_pier", open = true}
	--s = curry (operateDoor, {obj = "door_kitchen_pier", open = true})()
	local c = script:new()
	c.actions = {
		[1] = { type="activatewall", wall=0, active = false},
		[2] = { type="activatewall", wall=1, active = false, after={1}}
	}	
	s:push {script=c, at="end"}
    return s
end

function closeKitchenPierDoor()
	if (not objects.door_kitchen_pier.isopen()) then
		return nil
	end
	local s = operateDoor {obj="door_kitchen_pier", open = false}
	--s = curry (operateDoor, {obj = "door_kitchen_pier", open = false})()
	local c = script:new()
	c.actions = {
		[1] = { type="activatewall", wall=0, active = true},
		[2] = { type="activatewall", wall=1, active = true, after={1}}
	}	
	s:push {script=c, at="end"}

	--table.insert (s, { type="activatewall", wall=0, active = true})
	--table.insert (s, { type="activatewall", wall=1, active = true})
    return s

end



function startSeagull(entity) 
	entity:setactive(false)
 	local s = script:new("_seagull")
    s.actions = {
        [1] = { type = "callfunc", func = curry (createObject, { 
            pos = {0, 0, 2},
            gfx = { model = "seagull", anim = "flying" },
            tag = "seagull"
        })},
		[2] = { type = "animate", actor="seagull", anim="flying", loop = 1, after={1} },
		[3] = { type = "animate", actor="seagull", anim="eating", after={2} },
		[4] = { type = "callfunc", func = function() variables.seagull = 1 end, after = {3} }
    }
	monkey.play(s)
end

function lookatPotoStew()
	if (objects.potostew.meatin == false) then
		return _say { character="guybrush", lines = { strings.kitchen[5] }} 
	else
		return _say { character="guybrush", lines = { strings.kitchen[9] }} 
	end
end

function changeName() 
	objects.potostew.meatin = true
	objects.potostew.text = strings.objects.meatstew
	objects.meat.text = strings.objects.stewedmeat
end

function stewMeat() 
	local s = script:new()	
	s.actions = {
    	[1] = { type="animate", actor="player", anim="operate_back" },
        [2] = { type="delay", sec="0.5", after={1} },
		[3] = { type="animate", actor="player", anim="idle_back", after={2} },
		[4] = { type="callfunc", func = curry(removeItemFromInventory, "meat"), after={3}},
		[5] = { type="callfunc", func = changeName, after={4}}
	}
	return s
end

function pickMeatInStew()
	if (objects.potostew.meatin == true) then
		local s = script:new()
		s.actions = {
	    	[1] = { type="animate", actor="player", anim="operate_back" },
    	    [2] = { type="delay", sec="0.5", after={1} },
			[3] = { type="animate", actor="player", anim="idle_back", after={2} },
			[4] = { type="callfunc", func = curry(pickupItem, "meat"), after={3}},
			[5] = { type="callfunc", func = function() objects.potostew.meatin = false end, after={4} },
		}
		return s
	else
		return defaultActions.pick()
	end
end

function birdReturns() 
	s = script:new("_bird")
	if (inventory["fish"] ~= nil) then
		s.actions = {
			[1] = { type="animate", actor="seagull", anim="nofish", loop = 1},
			[2] = { type = "callfunc", func = curry(removeObject, "seagull"), after={1} }
		}
	else
		s.actions = {
			[1] = { type="animate", actor="seagull", anim="eating" },
			[2] = { type ="callfunc", after={1}, func = function()
				if (variables.seagull == 1) then
					variables.seagull = 2 
				else
					variables.seagull = 2 
				end
			end
			}
		}
	end
	monkey.play(s)
end


function hitPlank() 
 	s = script:new()
    s.actions = {
        [1] = { type = "walkto", actor = "player", pos = {293, 12}},
		[2] = { type = "turn", actor = "player", face="south", after={1} },
		[3] = { type = "animate", actor="player", anim="plank", after={2} },
    	[4] = { type = "delay", sec="0.2", after={3} },
		[5] = { type = "animate", actor="player", anim="idle_front", after={4} },
		[6] = { type = "animate", actor="plank", anim="pushed", after={5} },
    	[7] = { type = "delay", sec="0.2", after={6} },
		[8] = { type = "animate", actor="plank", anim="default", after={7} }
	}
	if (variables.seagull == 1) then
		s.actions[9] = { type = "callfunc", func = function() variables.seagull = 0 end, after={8} }
		s.actions[10] = { type="animate", actor="seagull", anim="jump1", loop =1, after={9} } 
		s.actions[11] = { type="callfunc", func = birdReturns, after={10}}
	else 
		if (variables.seagull == 2) then
			s.actions[9] = { type = "callfunc", func = function() variables.seagull = 0 end, after={8} }
			s.actions[10] = { type="animate", actor="seagull", anim="jump2", loop =1, after={9}}
			s.actions[11] = { type="callfunc", func = birdReturns, after={10}}
		end
	end



	--if (variables.seagull > 0) then
--		table.insert(s.edges, {4,8})	
--		table.insert(s.edges, {8,9})	
--		table.insert(s.edges, {9,10})	
--	end
	monkey.play(s)
end

function getFish() 
	if (inventory["fish"] ~= nil) then
		-- I already have this
		return nil
	end
	if (variables.seagull == 0) then
		return pickup { obj = "fish" }
	else
		return _say { character="guybrush", lines = { strings.kitchen[4] }} 
	end
end	