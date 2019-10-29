local str = strings.leftyin

engine.items["leftyin.walkarea"] = scumm.factory.walkarea {
	shape = { 
		type = "poly", 
		--holes=true, 
		--outline = {0,0,0,166,316,166,316,0}
		outline = {0,0,0,200,320,200,320,0}
	},
	priority = 0,
	depth = { type="linear_y", values= {0, 1, 144, 0} },
}