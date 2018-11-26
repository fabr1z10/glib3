items.lookout = {}

-- the local objects
items.lookout.stairs = {
	text = strings.objects.stairs,
	pos = {230, 0, 0},
	walk_to = {250, 0}, 
	face = "south",
	size = {30, 10},			
	actions = {
		walk = curry(change_room, "village1")
	}
}

items.lookout.lookout = {
	tag = "lookout",
	text_offset = {0, 60},
    text_color = {170, 170, 170, 255},
	text = strings.objects.lookout,
	pos = {114, 36, 0},
	walk_to = {134, 36},
	size = {20, 47},
	offset = {-10,0},
	face = "west",
	model ="lookout",
	anim ="idle_right",
	flip = true,
	actions = {
		talk = curry(start_dialogue, {dialogue = "lookout"})
	}
}

items.lookout.fire = {
	pos = {126, 52, -1},
	model = "fire",
    anim = "default"
}