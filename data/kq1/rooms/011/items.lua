local inventory = engine.state.scumm.inventory

engine.items["011.walkarea"] = scumm.factory.walkarea {
	shape = { 
		type = "poly", 
		holes = {},
		outline = {0,0,0,166,316,166,316,0}},
	priority = 0,
	depth = { type="linear_y", values= {0, 1, 144, 0} },

}
