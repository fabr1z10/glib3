engine.items["alley.walkarea"] = scumm.factory.walkarea {
	shape = { type = "poly", outline ={0,34,120,34,120,18,190,18,190,47,304,47,304,0,18,0,18,13,0,13}},
	priority = 0,
	depth = { type="linear_y", values= {0, 1, 144, 0} },

}

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
