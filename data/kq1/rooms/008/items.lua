engine.items["008.walkarea"] = scumm.factory.walkarea {
	shape = { 
		type = "poly", 
		holes = true,
		outline = {41,0,56,13,74,23,82,23,112,49,114,61,106,62,83,54,75,64,86,66,121,81,133,77,156,65,145,57,135,30,113,0}},
	priority = 0,
	depth = { type="linear_y", values= {0, 1, 144, 0} },
}

engine.items["008.egg"] = makeItem { 
	x = 140, y= 81,
	--x=0,y=0,
	--priority=2,
	outline = {0,0,0,17,26,17,26,0},
	msg = strings.room008[1],
	--gfx = "bg002.png",
	model = "008.egg"
}