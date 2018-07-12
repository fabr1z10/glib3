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
		{ type = "animate", actor="seagull", anim="flying", loop = 2 },
		{ type = "animate", actor="seagull", anim="eating" },
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