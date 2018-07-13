function openKitchenPierDoor()
	if (objects.door_kitchen_pier.isopen()) then
		return nil
	end
	s = curry (operateDoor, {obj = "door_kitchen_pier", open = true})()
	table.insert (s, { type="activatewall", wall=0, active = false})
	table.insert (s, { type="activatewall", wall=1, active = false})
    return s
end

function closeKitchenPierDoor()
	if (not objects.door_kitchen_pier.isopen()) then
		return nil
	end
	s = curry (operateDoor, {obj = "door_kitchen_pier", open = false})()
	table.insert (s, { type="activatewall", wall=0, active = true})
	table.insert (s, { type="activatewall", wall=1, active = true})
    return s

end



function startSeagull(entity) 
print "ucci!"
	entity:setactive(false)
 	s = Script.create("_seagull")
    s:add ({
        { type = "callfunc", func = curry (createObject, { 
            pos = {0, 0, 2},
            gfx = { model = "seagull", anim = "flying" },
            tag = "seagull"
        })},
		{ type = "animate", actor="seagull", anim="flying", loop = 1 },
		{ type = "animate", actor="seagull", anim="eating" },
		{ type = "callfunc", func = function() variables.seagull = 1 end }
    })
	s:setsequence()
	monkey.play(s)
end

function lookatPotoStew()
	if (objects.potostew.meatin == false) then
		return say { character="guybrush", lines = { strings.kitchen[5] }} 
	else
		return say { character="guybrush", lines = { strings.kitchen[9] }} 
	end
end

function changeName() 
	objects.potostew.meatin = true
	objects.potostew.text = strings.objects.meatstew
	objects.meat.text = strings.objects.stewedmeat
end

function stewMeat() 
	return {
    	{ type="animate", actor="player", anim="operate_back" },
        { type="delay", sec="0.5" },
		{ type="animate", actor="player", anim="idle_back" },
		{ type="callfunc", func = curry(removeItemFromInventory, "meat")},
		{ type="callfunc", func = changeName }}
end

function pickMeatInStew()
	if (objects.potostew.meatin == true) then
		return {
	    	{ type="animate", actor="player", anim="operate_back" },
    	    { type="delay", sec="0.5" },
			{ type="animate", actor="player", anim="idle_back" },
			{ type="callfunc", func = curry(pickupItem, "meat")},
			{ type="callfunc", func = function() objects.potostew.meatin = false end }
		}
	else
		return defaultActions.pick()
	end
end

function birdReturns() 
	s = Script.create("_bird")
	if (inventory["fish"] ~= nil) then
		s:add({
			{ type="animate", actor="seagull", anim="nofish", loop = 1},
			{ type = "callfunc", func = curry(removeObject, "seagull") }
		})
	else
		s:add({
			{ type="animate", actor="seagull", anim="eating" },
			{ type ="callfunc", func = function() 
				if (variables.seagull == 1) then
					variables.seagull = 2 
				else
					variables.seagull = 2 
				end
			end
			}
		})
	end
	s:setsequence()
	monkey.play(s)
end


function hitPlank() 
 	s = Script.create(nil)
    s:add ({
        {
            type = "walkto",
            actor = "player",
            pos = {293, 12}
        },
		{
			type = "turn", actor = "player", face="south"
		},
		{ type="animate", actor="player", anim="plank"},
    	{ type="delay", sec="0.2" },
		{ type="animate", actor="player", anim="idle_front"},
		{ type="animate", actor="plank", anim="pushed"},
    	{ type="delay", sec="0.2" },
		{ type="animate", actor="plank", anim="default"}
	})
	table.insert(s.edges, {0,1})
	table.insert(s.edges, {1,2})
	table.insert(s.edges, {2,3})
	table.insert(s.edges, {3,4})
	table.insert(s.edges, {4,5})	
	table.insert(s.edges, {5,6})	
	table.insert(s.edges, {6,7})	
	if (variables.seagull == 1) then
		s:add({
			{ type = "callfunc", func = function() variables.seagull = 0 end },
			{ type="animate", actor="seagull", anim="jump1", loop =1} ,
			{ type="callfunc", func = birdReturns }
		})
	else 
		if (variables.seagull == 2) then
		s:add({
			{ type = "callfunc", func = function() variables.seagull = 0 end },
			{ type="animate", actor="seagull", anim="jump2", loop =1} ,
			{ type="callfunc", func = birdReturns }
		})
		end
	end



	if (variables.seagull > 0) then
		table.insert(s.edges, {4,8})	
		table.insert(s.edges, {8,9})	
		table.insert(s.edges, {9,10})	
	end
	monkey.play(s)
end

function getFish() 
	if (inventory["fish"] ~= nil) then
		-- I already have this
		return
	end
	if (variables.seagull == 0) then
		return pickup { obj = "fish" }
	else
		return say { character="guybrush", lines = { strings.kitchen[4] }} 
	end
end	