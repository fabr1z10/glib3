objects["forest2_1"] = {
	text = strings.objects.path,
    pos = {310, 32}, -- location where the player will go
	dir="east",
    walk = curry(changeRoom, "forest1")
}

objects["forest2_4"] = {
	text = strings.objects.path,
    pos = {257, 70}, -- location where the player will go
    walk = curry(changeRoom, "forest4")
}