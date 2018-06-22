function openKitchenPierDoor()
	s = curry (operateDoor, {obj = objects.door_kitchen_pier, open = true})()
	table.insert (s, { type="activatewall", wall=0, active = false})
	table.insert (s, { type="activatewall", wall=1, active = false})
    return s
end
