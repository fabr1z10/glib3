print ("cazzo!!!")
-- generally, an item is a blueprint for an object
-- * it can have graphics attached. To do so, model needs to be specified
engine.items["dave"] = {
	tag = "player",
	model = "dave",
	character = {
		state = "idle",
		speed = 100
	},
	text_color = {255, 255, 255, 255},
	text_offset = {0, 60},
	applydepth = true

}

