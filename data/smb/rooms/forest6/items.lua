objects["forest6_5"] = {
	text = strings.objects.path,
    pos = {237, 70}, -- location where the player will go
	dir="north",
    walk = curry(changeRoom, "forest5")
}

objects["forest6_8"] = {
	text = strings.objects.path,
	pos={310,32},
	dir="east",
    walk = curry(changeRoom, "forest8")
}
objects["forest6_7"] = {
	text = strings.objects.path,
	pos={10,32},
	dir="west",
    walk = curry(changeRoom, "forest7")
}
