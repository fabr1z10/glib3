


objects["forest4_2"] = {
	text = strings.objects.path,
    pos = {135, 70}, -- location where the player will go
	dir="north",
    walk = curry(changeRoom, "forest2")
}

objects["forest4_5"] = {
	text = strings.objects.path,
    pos = {310, 32}, -- location where the player will go
    walk = curry(changeRoom, "forest5")
}