--items.scummbar = {}

items["scummbar.door_out"] = factory.door.create {
	tag = "door_out",
	pos = {32, 24, -1},
	size = {38, 47},
	walk_to = {57, 20},
	face = "west",
	door_ref = "door_village_scummbar",
	model = "door_scummbar_village",
	nextroom = "village1"
}

items["scummbar.mancomb"] = {
	tag="mancomb",
	text = strings.objects.pirate,
	pos = {89, 24, -1},
	size = {30, 30},
	model = "mancomb",
	anim = "idle",
	walk_to = {125, 17},
	face = "north",
	actions = {
		look = curry(change_room, "mancomb"),
		talk = curry(change_room, "mancomb")
	}
}

items["scummbar.estevan"] = {
	tag="estevan",
	text = strings.objects.pirate,
	pos = {164, 21, 1},
	size = {30, 20},
	model = "estevan",
	anim = "idle",
	walk_to = {195, 11},
	face = "south",
	actions = {
		look = curry(change_room, "estevan"),
		talk = curry(change_room, "estevan")
	}
}

