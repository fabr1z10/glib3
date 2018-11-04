objects["cliffside"] = {
	text = strings.objects.cliffside,
	pos = {8, 71},
	walk = curry(changeRoom, "lookout")
}

objects["poster"] = {
    text = strings.objects.poster,
    pos = {269, 133},
    dir = "north",
    look = curry (_say, { character="guybrush", lines= { strings.village1[1], strings.village1[2] }} )
}

objects["village1_door"] = {
   	text = strings.objects.door,
    tag = "door1",
    pos = {715, 13},
    dir = "north",
	walk = curry(walkToDoor, { obj = "village1_door", roomId = "scummbar"}),
	open = curry(operateDoor, { obj = "village1_door", open = true }),
	close = curry(operateDoor, { obj = "village1_door", open = false }),
	isopen = curry(isOpen, "scummbar"),
	setopen = curry2(setOpen, "scummbar")
}

objects["archway"] = {
	text = strings.objects.archway,
    pos = {1008, 34}, -- location where the player will go
	dir = "east",
    walk = curry(changeRoom, "village2")
}