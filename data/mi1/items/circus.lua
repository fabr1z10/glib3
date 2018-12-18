items["circus.wayout"] = {
	text = strings.objects.path,
	pos = {280, 32, 0},
	size = {16, 144},			
	walk_to = {280, 32}, 
	face = "east",
	actions = {
		walk = ms { {action.change_room, {id=1,room="clearing"}}}
	}
}

items["circus.purpleclown"] = {
	tag = "circus.purpleclown",
	text = strings.objects.fettuccini,
	pos = {37,34,0},
	size = {18,30},
	offset ={-9,0},
    text_color = {255, 85, 255, 255},
	text_offset = {0,60},
	applydepth = true,
	model = "circus.purpleclown",
	anim="idle_right",

}

items["circus.greenclown"] = {
	tag = "circus.greenclown",
	text = strings.objects.fettuccini,
	pos = {51,34,0},
	size= {18,30},
	offset ={-9,0},
	text_color = {85, 255, 85, 255},
	text_offset={0,60},
	applydepth = true,
	model = "circus.greenclown",
	anim="idle_right",
	flip = true,
	
}