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