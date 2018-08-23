objects["purple_clown"] = {
	tag = "purpleclown",
	offset = {0, 60},
    color = {255, 85, 255, 255}
}

objects["green_clown"] = {
	tag = "greenclown",
	offset = {0, 60},
    color = {85, 255, 85, 255}
}

objects["outside"] = {
	text = strings.objects.outside,
    pos = {279, 32}, -- location where the player will go
    walk = curry(changeRoom, "clearing")
}