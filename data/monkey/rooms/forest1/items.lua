objects["forest_exit"] = {
	text = strings.objects.path,
    pos = {310, 32}, -- location where the player will go
	dir="east",
    walk = curry(changeRoom, "meleemap")
}

objects["forest1_2"] = {
	text = strings.objects.path,
    pos = {242, 70}, -- location where the player will go
    walk = curry(changeRoom, "forest2")
}

objects["forest1_3"] = {
	text = strings.objects.path,
    pos = {154, 70}, -- location where the player will go
    walk = curry(changeRoom, "forest3")
}
