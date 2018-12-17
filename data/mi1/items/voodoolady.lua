items.voodoolady = {}


items["voodoolady.door"] = factory.door.create {
	name = "voodoolady.door",
	pos = {87, 42, -1},
	size = {23, 58},
	walk_to = {105, 38},
	face = "west",
	door_ref = "door_voodoolady",
	model = "voodoolady.door",
	nextroom = "village2"
}

items["voodoolady.voodoolady"] = {
	pos = {346,46,0},
	tag="voodoolady",
	text_color = {0, 170, 0, 255},
	text_offset = {0,60},
	model = "voodoolady.voodoolady",
	anim="idle"	
}

items["voodoolady.voodoolady_body"] = {
	pos = {366,46,0},
	tag="voodoolady_body",
	model = "voodoolady.body",
	anim="idle"	
}

items["voodoolady.trunk"] = {
	text = strings.objects.trunk,
	pos = {230,0,1},
	size = {70,30},	
	walk_to = {265, 10},
	face="south",
	model = "voodoolady.trunk",
	anim="idle",
	actions ={}
}