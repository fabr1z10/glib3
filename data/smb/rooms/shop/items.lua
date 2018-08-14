objects["sword"] = {
	text = strings.objects.sword,
	pos = {222, 19},
	tag = "sword",
	dir = "north",
	look = curry (_say, { character="guybrush", lines= { strings.shop[5] }} ),
	pick = curry (pickup, {obj = "sword"})
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
