require("rooms/village2/actions")

objects["citizen"] = {
	tag = "citizen",
	text = strings.objects.citizen,
	pos = {359, 27},
	dir = "west",
	color = {255, 85, 85, 255},
	offset = {0,60},
	look = lookCitizen,
	talk = talkCitizen
}
	
objects["lowmoralfiber"] = {
	text = strings.objects.lowmoralfiber,
	pos = {75,14},
	dir="west",
	talk = curry(talk, { character = "lowmoralfiber", node = 1}),
}

objects["lmf1"] = {
	tag="lmf1",
	color = {255, 85, 255, 255},
	offset = {0,60}
}
	
objects["lmf2"] = {
	tag="lmf2",
	color = {85, 255, 255, 255},
	offset = {0,60}
}

objects["lmf3"] = {
	tag="lmf3",
	color = {85, 255, 85, 255},
	offset = {0,60}
}

objects["rat"] = {
	tag="rat",
	color = {170, 170, 170, 255},
	offset = {0,60}
}

objects["door_village2_1"] = {
	text = strings.objects.door,
	tag="door1",
	pos = {387, 37},
	dir="west",
	open = curry (door_transport, {doorfrom = "door1", doorto = "door4", dest = {172, 72}, playerdest = {188, 62}, anim="idle_front", flip=false})
}

objects["door_village2_2"] = {
	text = strings.objects.door,
	tag="door2",
	pos = {208, 59},
	dir="east",
	open = curry (door_transport, {doorfrom = "door2", doorto = "door3", dest = {160, 72}, playerdest = {134, 62}, anim="idle_front", flip=false})
}

objects["door_village2_3"] = {
	text = strings.objects.door,
	tag="door3",
	pos = {134, 62},
	dir="north",
	open = curry (door_transport, {doorfrom = "door3", doorto = "door1", dest = {800,72}, playerdest = {387, 33}, anim="idle_right", flip=false})
}

objects["door_village2_4"] = {
	text = strings.objects.door,
	tag="door4",
	pos = {188, 62},
	dir="north",
	open = curry (door_transport, {doorfrom = "door4", doorto = "door2", dest = {172, 72}, playerdest = {208, 59}, anim="idle_right", flip=true})
}

objects["village2_archway"] = {
	text = strings.objects.archway,
	pos = {160,65},
	dir = "north",
	walk = curry(changeRoom, "village3")
}

objects["village2_archway2"] = {
	text = strings.objects.archway,
	pos = {436,36},
	dir = "north",
	walk = curry(changeRoom, "village1")
}