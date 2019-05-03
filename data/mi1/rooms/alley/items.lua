engine.items["alley.exit"] = {
	pos = {753, 11, 0},
	hotspot = {
		text = strings.objects.archway,
		walk_to = {35, 18}, 
		face = "west",
		size = {23, 74}
	},			
	actions = {
		walk = { type=action.change_room, args = {room="village2"}}
	}
}
