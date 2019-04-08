-- generally, an item is a blueprint for an object
-- * it can have graphics attached. To do so, model needs to be specified
items["crispins_house"] = {
	pos={0,0,0},
	hotspot = {
		shape = { type ="poly", outline={17,78,17,101,59,115,111,175,243,175,255,147,252,107,219,87,188,90,174,81,149,86,142,91,100,92,74,71}}

	},
	actions = {
		look = box{ msg = strings[1] }
	}

}
