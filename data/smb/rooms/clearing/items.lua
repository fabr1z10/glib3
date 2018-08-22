objects["clearing_path"] = {
	text = strings.objects.path,
	pos = {490, 24},
	dir = "east",
	walk = curry(changeRoom, "meleemap")
}

objects["circus_tent"] = {
	text = strings.objects.circustent,
	pos = {82, 69},
	dir = "north",
	walk = curry(changeRoom, "circus")
}

