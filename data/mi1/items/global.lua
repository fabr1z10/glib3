items.guybrush = {
	tag = "player",
	text_color = {255, 255, 255, 255},
	text_offset = {0, 60}
}


defaultActions = {
	look = curry (say, {actor=items.guybrush, lines = {strings.defaultactions[4]} }),

}

