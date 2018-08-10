objects["door_voodoolady_in"] = {
    text = strings.objects.door,
    tag = "door_voodoo",
    pos = {106, 40},
	dir = "west",
	walk = curry(walkToDoor, { obj = "door_voodoolady_in", roomId = "village2"}),
	open = curry(operateDoor, { obj = "door_voodoolady_in", open = true }),
	close = curry(operateDoor, { obj = "door_voodoolady_in", open = false }),
	isopen = curry(isOpen, "voodoolady"),
	setopen = curry2(setOpen, "voodoolady")		
}

objects["voodoolady"] = {
	tag="voodoolady",
	color= {0, 170, 0, 255},
	offset = {0, 60}
}

objects["baskets"] = {
	text = strings.objects.baskets,
	pos = {124, 20},
	dir = "south",
	open = curry (_say, { character="guybrush", lines= { strings.voodoolady[1], strings.voodoolady[2] }} ),
	close = curry (_say, { character="guybrush", lines= { strings.voodoolady[3] }} ),
	push = curry (_say, { character="guybrush", lines= { strings.voodoolady[3] }} ),
	pull = curry (_say, { character="guybrush", lines= { strings.voodoolady[3] }} ),
	look = curry (_say, { character="guybrush", lines= { strings.voodoolady[4] }} ),
	use = curry (_say, { character="guybrush", lines= { strings.voodoolady[3] }} ),
}

objects["basket"] = {
	text = strings.objects.basket,
	pos = {178, 19},
	dir = "south",
	open = curry (_say, { character="guybrush", lines= { strings.voodoolady[6]}} ),
	close = curry (_say, { character="guybrush", lines= { strings.voodoolady[3] }} ),
	push = curry (_say, { character="guybrush", lines= { strings.voodoolady[3] }} ),
	pull = curry (_say, { character="guybrush", lines= { strings.voodoolady[3] }} ),
	look = curry (_say, { character="guybrush", lines= { strings.voodoolady[5] }} ),
	use = curry (_say, { character="guybrush", lines= { strings.voodoolady[3] }} ),
}
	
objects["chickens"] = {
	text = strings.objects.chickens,
	pos = {94, 20},
	dir="south",
	pick =curry (_say, { character="guybrush", lines= { strings.voodoolady[8]}} ),
	look =curry (_say, { character="guybrush", lines= { strings.voodoolady[7]}} ),
}

objects["statue"] = {
	text = strings.objects.statue,
	pos = {185, 40},
	dir = "west",
	open = curry (_say, { character="guybrush", lines= { strings.voodoolady[3]}} ),
	close = curry (_say, { character="guybrush", lines= { strings.voodoolady[3] }} ),
	push = curry (_say, { character="guybrush", lines= { strings.voodoolady[3] }} ),
	pull = curry (_say, { character="guybrush", lines= { strings.voodoolady[3] }} ),
	look = curry (_say, { character="guybrush", lines= { strings.voodoolady[9] }} ),
	use = curry (_say, { character="guybrush", lines= { strings.voodoolady[3] }} ),
}

objects["knickknacks"] = {
	text = strings.objects.knickknacks,
	pos = {189, 41},
	dir ="north",
	look = lookknickknacks
}

objects["couch"] = {
	text = strings.objects.couch,
	pos = {209,40},
	dir ="north",
	look = curry (_say, { character="guybrush", lines= { strings.voodoolady[17] }} ),
	use = curry (_say, { character="guybrush", lines= { strings.voodoolady[16] }} )
}

objects["trunk"] = {
	text = strings.objects.trunk,
	pos = {260,14},
	dir ="south",
	look = curry (_say, { character="guybrush", lines= { strings.voodoolady[18] }} ),
	--look = curry (_say, { character="guybrush", lines= { strings.voodoolady[17] }} ),
	--use = curry (_say, { character="guybrush", lines= { strings.voodoolady[16] }} )
}

objects["rubberchicken"] = {
	text = strings.objects.chicken,
	tag = "rubberchicken",
	pos = {258,15},
	dir ="south",
	look = look_rubber_chicken,
	pick = pickup_rubber_chicken
}

objects["bones"] = {
	text = strings.objects.bones,
	pos = {264,12},
	dir ="south",
	look = curry (_say, { character="guybrush", lines= { strings.voodoolady[23], strings.voodoolady[24] }} ),
}

objects["chalice"] = {
	text = strings.objects.chalice,
	pos = {272,8},
	dir ="south",
	look = curry (_say, { character="guybrush", lines= { strings.voodoolady[25] }} ),
}

print ("FDUFUFU")