-- generally, an item is a blueprint for an object
-- * it can have graphics attached. To do so, model needs to be specified
items2["guybrush"] = {
	tag = "player",
	model = "guybrush",
	character = {
		state = "idle"
	},
	text_color = {255, 255, 255, 255},
	text_offset = {0, 60},
	applydepth = true

}

