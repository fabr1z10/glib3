objects["lookout"] = {
	tag = "lookout",
    text = strings.objects.lookout,
    pos = {160, 36},
    dir ="west",
	offset = {0, 60},
    color = {170, 170, 170, 255},
    talk = curry(talk, { character = "lookout", node = 1}),
	look = curry(_say,{character ="guybrush", lines = {strings.dialogues.lookout.text[50]}})
}

objects["stairs"] = {
	text = strings.objects.stairs,
	pos = {250, 0}, -- location where the player will go
    walk = curry(changeRoom, "village1")
}

objects["path"] = {
	text = strings.objects.path,
	pos = {314, 52},
    walk = curry(changeRoom, "meleemap")  
}