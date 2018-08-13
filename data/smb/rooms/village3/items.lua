objects["village3_archway"] = {
	text = strings.objects.archway,
	pos = {770, 10},
	dir = "east",
	walk = curry(changeRoom, "village2")
}

objects["door_village_shop"] = {
	text = strings.objects.door,
    tag = "door_shop",
    pos = {667, 22},
	dir = "north",
	walk = curry(walkToDoor, { obj = "door_village_shop", roomId = "shop"}),
	open = curry(operateDoor, { obj = "door_village_shop", open = true }),
	close = curry(operateDoor, { obj = "door_village_shop", open = false }),
	isopen = curry(isOpen, "shop"),
	setopen = curry2(setOpen, "shop")
}