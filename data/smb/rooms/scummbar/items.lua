objects["scummbar_door_out"] = {
	text = strings.objects.door,
    tag = "door1",
    pos = {66, 19},
    dir = "west",
	walk = curry(walkToDoor, {obj = "scummbar_door_out", roomId = "village1"}),
	open = curry(operateDoor, { obj = "scummbar_door_out", open = true }),
	close = curry(operateDoor, { obj = "scummbar_door_out", open = false }),
	isopen = curry(isOpen, "scummbar"),
	setopen = curry2(setOpen, "scummbar")
}

objects["door_bar_kitchen"] = {
	text = strings.objects.door,
    tag = "door_bar_kitchen",
    pos = {600, 14},
	dir = "east",
	open = openBarKitchen,
	walk = enterBarKitchen,
	close = curry(operateDoor, {obj = "door_bar_kitchen", open = false} ),
	isopen = curry(isOpen, "kitchen"),
	setopen = curry2(setOpen, "kitchen")		
}

objects["fireplace"] = {
	text = strings.objects.fireplace,
	tag ="fireplace",
	pos = {506, 41},
	dir ="east",
	look = curry (_say, { character="guybrush", lines= { strings.scummbar[1] }} )
}

objects["ilp"] = {
	text = strings.objects.ilp,
	tag="ilp",
	pos={474,7},
	dir ="west",
 	talk = talkToPirates
}

objects["ilp1"] = {
	color = {85, 85, 255, 255},
	offset = {0, 60},
	tag ="ilp1"		
}

objects["ilp2"] = {
	color = {255, 255, 85, 255},
	offset = {0, 60},
	tag ="ilp2"		
}

objects["ilp3"] = {
	color = {255, 85, 255, 255},
	offset = {0, 60},
	tag ="ilp3"		
}

objects["dog"] = {
	text = strings.objects.dog,
	tag = "dog",
	pos = {289, 9},
	dir = "north",
	talk = talkToDog,
    color = {170, 170, 170, 255},
	offset = {0, 60},
}


objects["loom_pirate"] = {
	text = strings.objects.pirate,
	tag = "loompirate",
	pos = {239,15},
	dir = "east",
	color = {85, 85, 255, 255},
	offset = {0, 40},
	look = talkToLoom,
	talk = talkToLoom	
}

objects["estevan"] = {
	text = strings.objects.pirate,
	tag = "estevan",
	pos = {200,10},
	dir = "south",
	color = {170, 85, 0, 255},
	offset = {0, 40},
	look = talkToEstevan,
	talk = talkToEstevan	
}

objects["mancomb"] = {
	text = strings.objects.pirate,
	tag = "mancomb",
	pos = {123,17},
	dir = "north",
	color = {255, 85, 85, 255},
	offset = {0, 40},
	look = talkToMancomb,
	talk = talkToMancomb	
}

objects["pirates_listening"] = {
	text = strings.objects.pirates,
	tag="pirateslistening",
	pos = {123,17},
	dir = "north",
	talk = curry (_say, { character="guybrush", lines= { strings.scummbar[2], strings.scummbar[3] }} ),
	look = curry (_say, { character="guybrush", lines= { strings.scummbar[3] }} )
}

objects["sleeping_pirate"] = {
	text = strings.objects.pirate,
	tag = "sleepingpirate",
	pos = {52,14},
	dir ="south",
	talk = curry (_say, { character="guybrush", lines= { strings.scummbar[4] }} ),
	look = curry (_say, { character="guybrush", lines= { strings.scummbar[4] }} )
}