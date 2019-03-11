items.alley = {}

items["alley.exit"] = {
	text = strings.objects.archway,
	pos = {753, 11, 0},
	walk_to = {35, 18}, 
	face = "west",
	size = {23, 74},			
	actions = {
		walk = ms { {action.change_room, {id=1,room="village2"}}}
	}
}
