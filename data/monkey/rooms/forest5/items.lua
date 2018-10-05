objects["forest5_4"] = {
	text = strings.objects.path,
    pos = {0, 32}, -- location where the player will go
	dir="west",
    walk = curry(changeRoom, "forest4")
}

objects["forest5_6"] = {
	text = strings.objects.path,
	pos={310,32},
	dir="east",
    walk = curry(changeRoom, "forest6")
}
