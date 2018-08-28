objects["forest7_6"] = {
	text = strings.objects.path,
    pos = {10, 32}, -- location where the player will go
	dir="west",
    walk = curry(changeRoom, "forest6")
}

objects["forest7_9"] = {
	text = strings.objects.path,
	pos={154,70},
	dir="north",
    walk = curry(changeRoom, "forest9")
}
