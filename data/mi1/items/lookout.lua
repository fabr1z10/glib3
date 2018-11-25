-- the local objects
items.lookout.stairs = {
	text = strings.objects.stairs,
	pos = {250, 0, 0},
	walk_to = {250, 0}, 
	face = "south",
	size = {10, 10},			
	actions = {}
}

room.items.lookout = {
	tag = "lookout",
	text_offset = {0, 60},
    text_color = {170, 170, 170, 255},
	text = strings.objects.lookout,
	pos = {114, 36, 0},
	walk_to = {134, 36},
	size = {20, 47},
	face = "west",
	model ="lookout",
	anim ="idle_right",
	flip = true,
	actions = {
		talk = curry(start_dialogue, {dialogue = "lookout"})
	}
}
