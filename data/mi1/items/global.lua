items["guybrush"] = {
	tag = "player",
	text_color = {255, 255, 255, 255},
	text_offset = {0, 60}
}

items["pieces_of_eight"] = {
	text = strings.objects.pieceofeight,
	text_plural = strings.objects.piecesofeight,
	actions = {
		look = function () 
			print ("123")		
			local s = script:new()
			s.actions = {
				action.say {id=1, actor="guybrush", lines = {strings.pieces_of_eight()}}
			}
			return s
		end

	}
}


