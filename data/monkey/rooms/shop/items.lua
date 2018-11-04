objects["sword"] = {
	text = strings.objects.sword,
	pos = {222, 19},
	tag = "sword",
	dir = "north",
	look = curry (_say, { character="guybrush", lines= { strings.shop[5] }} ),
	pick = curry (pickup, {obj = "sword"})
}

objects["shovel"] = {
	text = strings.objects.shovel,
	pos = {157, 69},
	tag = "shovel",
	dir = "west",
	look = curry (_say, { character="guybrush", lines= { strings.shop[6] }} ),
	pick = curry (pickup, {obj = "shovel"})
}

objects["storekeeper"] = {
	text = strings.objects.storekeeper,
	tag = "storekeeper",
	pos = {235, 7},
	dir = "east",
	offset = {0, 60},
    color = {255, 85, 255, 255},
	talk = talkToStorekeeper
}

objects["sign"] = {
	text = strings.objects.sign,
	pos = {235, 7},
	tag ="sign",
	dir = "east",
	look = curry (_say, { character="guybrush", lines= { strings.shop[7] }} ),
	pick = curry (_say, { character="guybrush", lines= { strings.shop[8], strings.shop[9] }} )
}

objects["bell"] = {
	text = strings.objects.bell,
	pos = {235, 7},
	tag ="bell",
	dir = "east",
	look = curry (_say, { character="guybrush", lines= { strings.shop[7] }} ),
	pick = curry (_say, { character="guybrush", lines= { strings.shop[8], strings.shop[9] }} )
}


objects["door_shop_village"] = {
	text = strings.objects.door,
    tag = "door_shop",
    pos = {85, 15},
	dir = "west",
	walk = walkToShopDoor,--curry(walkToDoor, { obj = "door_shop_village", roomId = "village3"}),
	open = curry(operateDoor, { obj = "door_shop_village", open = true }),
	close = curry(operateDoor, { obj = "door_shop_village", open = false }),
	isopen = curry(isOpen, "shop"),
	setopen = curry2(setOpen, "shop")
}