-- generally, an item is a blueprint for an object
-- * it can have graphics attached. To do so, model needs to be specified
items2["village2.archway1"] = {
	hotspot = {
		text = strings.objects.archway,
		walk_to = {436, 35}, 
		face = "north",
		size = {40, 50},			
		actions = {
			walk = ms { {action.change_room, {id=1,room="village1"}}}
		}
	},
	pos = {416, 34, 0},
}

