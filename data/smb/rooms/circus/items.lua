objects["purple_clown"] = {
	text = strings.objects.fettuccini,
	tag = "purpleclown",
	pos = {178, 9},
	dir ="south",
	offset = {0, 60},
    color = {255, 85, 255, 255},
	give = {
		pot = showPot
	}
}

objects["green_clown"] = {
	text = strings.objects.fettuccini,
	pos = {178, 9},
	dir ="south",
	tag = "greenclown",
	offset = {0, 60},
    color = {85, 255, 85, 255},
	give = {
		pot = showPot
	}
}

objects["outside"] = {
	text = strings.objects.outside,
    pos = {279, 32}, -- location where the player will go
    walk = curry(changeRoom, "clearing")
}